#include "ReachabilityController.h"

int_vec3_bitmap_list getReachabilityDomain(const symb_model* m, int_vec3_bitmap* Qa) {
    int_vec3_bitmap_list R_list = bitmap_list_create_empty();
    int_vec3_bitmap Rk = NULL_VEC3_BITMAP;
    int_vec3_bitmap pre = NULL_VEC3_BITMAP;
    int_vec3_bitmap Rkp1 = bitmap_clone(Qa);
    int k = 0;
    do {
        printf("\rCalculating R%d\n", k);
        fflush(stdout);
        k++;
        //bitmap_free(&Rk);
        Rk = Rkp1;
        bitmap_list_add_bitmap(&R_list, Rk);
        pre = Pre(m, &Rk);
        Rkp1 = bitmap_union(&Rk, &pre);
        bitmap_free(&pre);
    } while (!bitmap_equal(&Rk, &Rkp1));

    bitmap_free(&Rkp1);
    printf("\n");

    return R_list;
}

static_symb_controller* construct_reachability_symbolic_controller(const symb_model* m, int_vec3_bitmap* Qa) {
    static_symb_controller* h = malloc(sizeof(static_symb_controller));
    printf("size of static symb controller: %lld\n", sizeof(static_symb_controller));

    for (size_t p1 = 0; p1 <= Nx.v1; p1++) {
        for (size_t p2 = 0; p2 <= Nx.v2; p2++) {
            for (size_t p3 = 0; p3 <= Nx.v3; p3++) {
                h->h[p1][p2][p3] = INT_VEC2_ZERO;
            }
        }
    }

    int_vec3_bitmap_list R_grids = getReachabilityDomain(m, Qa);
    int_vec3_arr R_star;

    int_vec2 sigma;

    for (size_t k = R_grids.size - 1; k > 0; k--) {
        R_star = bitmap_to_array(&R_grids.list[k]);
        for (size_t i = 0; i < R_star.size; i++) {
            sigma = sigma_st_g_ksi_sigma_is_pre(m, R_star.data[i], &R_grids.list[k - 1]);
            h->h[R_star.data[i].v1][R_star.data[i].v2][R_star.data[i].v3] = sigma;
            //printf("h((%d, %d, %d)) = (%d, %d)\n", R_star.data[i].v1, R_star.data[i].v2, R_star.data[i].v3, sigma.v1, sigma.v2);
        }
        free(R_star.data);
    }

    h->R_star = bitmap_to_array(&R_grids.list[R_grids.size - 1]);

    bitmap_list_free_with_content(&R_grids);

    return h;
}

BOOL is_reachability_achieved(int_vec3_bitmap* Qa, float_vec3 x) {
    int_vec3 ksi = q(&x, &Nx, &x_min, &x_max);
    return bitmap_contains(Qa, ksi);
}