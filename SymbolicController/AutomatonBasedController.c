#include "AutomatonBasedController.h"


int_vec3_ms_bitmap create_bitmap_with_final_product_states() {
    int_vec3_ms_bitmap Qa = ms_bitmap_create_empty(&Nx, Q);

    for (int s = 0; s < F_size; s++) {
        ms_bitmap_set_stage_ons(&Qa, F[s]);
    }

    return Qa;
}

dynamic_symb_controller* construct_dynamic_symbolic_controller(symb_model* m) {
    dynamic_symb_controller* h = (dynamic_symb_controller*)malloc(sizeof(dynamic_symb_controller));

    h->h1 = malloc(sizeof(int***) * (NX_1 + 1));
    for (size_t p1 = 1; p1 <= Nx.v1; p1++) {
        h->h1[p1] = malloc(sizeof(int**) * (NX_2 + 1));
        for (size_t p2 = 1; p2 <= Nx.v2; p2++) {
            h->h1[p1][p2] = malloc(sizeof(int*) * (NX_3 + 1));
            for (size_t p3 = 1; p3 <= Nx.v3; p3++) {
                h->h1[p1][p2][p3] = (int*)malloc(sizeof(int) * Q);
                for (size_t psi = 0; psi < Q; psi++) {
                    h->h1[p1][p2][p3][psi] = l((int_vec3){p1, p2, p3});
                }
            }
        }
    }

    int_vec3_ms_bitmap Qa = create_bitmap_with_final_product_states();

    product_symb_controller* h_temp = construct_product_reachability_symbolic_controller(m, h->h1, &Qa);
    ms_bitmap_free(&Qa);

    h->h2 = h_temp->h;

    h->Q0.data = (int_vec3*)malloc(sizeof(int_vec3) * (NX_1 * NX_2 * NX_3+1));
    h->Q0.size = 0;
    int_vec3 ksi;
    for (size_t p1 = 1; p1 <= NX_1; p1++) {
        for (size_t p2 = 1; p2 <= NX_2; p2++) {
            for (size_t p3 = 1; p3 <= NX_3; p3++) {
        //printf("yypassed %llu, %llu, %llu\n", p1, p2, p3);
                ksi = (int_vec3){p1, p2, p3};
                if (ms_bitmap_contains(&h_temp->R_star, ksi, q0)) {
                    h->Q0.data[h->Q0.size++] = ksi;
                }
            }
        }
    }
    printf("hhhhhhhhhhh\n");

    ms_bitmap_free(&h_temp->R_star);
    free(h_temp);

    return h;
}

BOOL is_specification_achieved(int psi) {
    for (int s = 0; s < F_size; s++) {
        if (psi == F[s]) {
            return TRUE;
        }
    }

    return FALSE;
}

void dynamic_symb_controller_free(dynamic_symb_controller* h) {
    for (size_t p1 = 0; p1 <= Nx.v1; p1++) {
        for (size_t p2 = 0; p2 <= Nx.v2; p2++) {
            for (size_t p3 = 0; p3 <= Nx.v3; p3++) {
                free(h->h1[p1][p2][p3]);
                free(h->h2[p1][p2][p3]);
            }
            free(h->h1[p1][p2]);
            free(h->h2[p1][p2]);
        }
        free(h->h1[p1]);
        free(h->h2[p1]);
    }
    free(h->h1);
    free(h->h2);

    free(h->Q0.data);
    free(h);
}