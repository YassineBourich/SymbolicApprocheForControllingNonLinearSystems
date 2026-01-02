#include "ProductReachabilityController.h"

int_vec3_ms_bitmap_list getProductReachabilityDomain(const symb_model* m, int**** h1, int_vec3_ms_bitmap* Qa) {
    int_vec3_ms_bitmap_list R_list = ms_bitmap_list_create_empty();
    int_vec3_ms_bitmap Rk = NULL_VEC3_MS_BITMAP;
    int_vec3_ms_bitmap pre = NULL_VEC3_MS_BITMAP;
    int_vec3_ms_bitmap Rkp1 = ms_bitmap_clone(Qa);
    int k = 0;
    do {
        printf("\rCalculating R%d\n", k);
        fflush(stdout);
        k++;
        //bitmap_free(&Rk);
        Rk = Rkp1;
        ms_bitmap_list_add_bitmap(&R_list, Rk);
        printf("calculating pre\n");
        pre = ProductPre(m, h1, &Rk);
        //print_bitmap(&pre);
        Rkp1 = ms_bitmap_union(&Rk, &pre);
        ms_bitmap_free(&pre);
    } while (!ms_bitmap_equal(&Rk, &Rkp1));

    ms_bitmap_free(&Rkp1);
    printf("Done\n");

    return R_list;
}

void print_bitmap(int_vec3_ms_bitmap* a) {
    for (int s = 0; s < a->nstages; s++) {
        printf("stage: %d\n", s);
        for (size_t i = 0; i < a->nwords; i++) {
            printf("\tword %llu\n", a->data[s][i]);
        }
    }
}

product_symb_controller* construct_product_reachability_symbolic_controller(const symb_model* m, int**** h1, int_vec3_ms_bitmap* Qa) {
    product_symb_controller* h = malloc(sizeof(product_symb_controller));
    printf("size of static symb controller: %lld\n", sizeof(product_symb_controller));

    h->h = malloc(sizeof(int_vec2***) * (NX_1 + 1));
    for (size_t p1 = 0; p1 <= Nx.v1; p1++) {
        h->h[p1] = malloc(sizeof(int_vec2**) * (NX_2 + 1));
        for (size_t p2 = 0; p2 <= Nx.v2; p2++) {
            h->h[p1][p2] = malloc(sizeof(int_vec2*) * (NX_3 + 1));
            for (size_t p3 = 0; p3 <= Nx.v3; p3++) {
                h->h[p1][p2][p3] = (int_vec2*)malloc(sizeof(int_vec2) * Q);
                for (size_t psi = 0; psi < Q; psi++) {
                    h->h[p1][p2][p3][psi] = INT_VEC2_ZERO;
                }
            }
        }
    }

    int_vec3_ms_bitmap_list MS_R_grids = getProductReachabilityDomain(m, h1, Qa);
    int_vec3_stage_arr R_k;

    int_vec2 sigma;

    for (size_t k = MS_R_grids.size - 1; k > 0; k--) {
        R_k = ms_bitmap_to_array(&MS_R_grids.list[k]);
        for (size_t i = 0; i < R_k.size; i++) {
            sigma = sigma_st_g_ksi_psi_sigma_is_pre(m, h1, R_k.data[i], R_k.stages[i], &MS_R_grids.list[k - 1]);
            h->h[R_k.data[i].v1][R_k.data[i].v2][R_k.data[i].v3][R_k.stages[i]] = sigma;
            //printf("h((%d, %d, %d), %d) = (%d, %d)\n", R_k.data[i].v1, R_k.data[i].v2, R_k.data[i].v3, R_k.stages[i], sigma.v1, sigma.v2);
        }
        free(R_k.data);
        free(R_k.stages);
    }

    h->R_star = ms_bitmap_clone(&MS_R_grids.list[MS_R_grids.size - 1]);

    ms_bitmap_list_free_with_content(&MS_R_grids);

    return h;
}