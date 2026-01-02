#include "ProductSymbolicModel.h"


int_vec3_ms_bitmap ProductPre(const symb_model* m, int**** h1, const int_vec3_ms_bitmap* R) {
    int_vec3_ms_bitmap predecessors = ms_bitmap_create_empty(&Nx, Q);

    int_vec3 ksi;
    for (size_t p1 = 1; p1 <= Nx.v1; p1++) {
        //printf("passed for %lld\n", p1);
        for (size_t p2 = 1; p2 <= Nx.v2; p2++) {
            for (size_t p3 = 1; p3 <= Nx.v3; p3++) {
                for (size_t psi = 0; psi < Q; psi++){
                    //printf("passed for %lld, %lld, %lld, %lld\n", p1, p2, p3, psi);
                    ksi = (int_vec3){p1, p2, p3};
                    if (exists_sigma_st_g_ksi_psi_sigma_is_pre(m, h1, ksi, psi, R)) {
                        ms_bitmap_add(&predecessors, ksi, psi);
                    }
                }
            }
        }
    }

    return predecessors;
}

BOOL exists_sigma_st_g_ksi_psi_sigma_is_pre(const symb_model* m, int**** h1, int_vec3 ksi, int psi, const int_vec3_ms_bitmap* R) {
    for (size_t c1 = 1; c1 <= Nu.v1; c1++) {
        for (size_t c2 = 1; c2 <= Nu.v2; c2++) {
            model_node node = g(m, ksi, (int_vec2){c1, c2});
            if (node.includes_0) {
                continue;
            }
            // TODO: Correct this!!!!
            for (size_t s1 = node.q_min_max.vect1.v1; s1 <= node.q_min_max.vect2.v1; s1++) {
                for (size_t s2 = node.q_min_max.vect1.v2; s2 <= node.q_min_max.vect2.v2; s2++) {
                    for (size_t s3 = node.q_min_max.vect1.v3; s3 <= node.q_min_max.vect2.v3; s3++) {
                        if (!MS_BITMAP_GET(R->data, h1[s1][s2][s3][psi], indexToInteger_integers(s1, s2, s3, R->Nx))) {
                            return FALSE;
                        }
                    }
                }
            }
            //printf("choosen %llu, %llu for %d, %d, %d, %d\n", c1, c2, ksi.v1, ksi.v2, ksi.v3, psi);
            return TRUE;
        }
    }
    return FALSE;
}


int_vec2 sigma_st_g_ksi_psi_sigma_is_pre(const symb_model* m, int**** h1, int_vec3 ksi, int psi, const int_vec3_ms_bitmap* R) {
    int_vec2 sigma;
    for (size_t c1 = 1; c1 <= Nu.v1; c1++) {
        for (size_t c2 = 1; c2 <= Nu.v2; c2++) {
            model_node node = g(m, ksi, (int_vec2){c1, c2});
            if (node.includes_0) {
                continue;
            }
            // TODO: Correct this!!!!
            for (size_t s1 = node.q_min_max.vect1.v1; s1 <= node.q_min_max.vect2.v1; s1++) {
                for (size_t s2 = node.q_min_max.vect1.v2; s2 <= node.q_min_max.vect2.v2; s2++) {
                    for (size_t s3 = node.q_min_max.vect1.v3; s3 <= node.q_min_max.vect2.v3; s3++) {
                        if (!MS_BITMAP_GET(R->data, h1[s1][s2][s3][psi], indexToInteger_integers(s1, s2, s3, R->Nx))) {
                            return INT_VEC2_ZERO;
                        }
                    }
                }
            }
            //printf("choosen %llu, %llu\n", c1, c2);
            sigma = (int_vec2){c1, c2};
            return sigma;
        }
    }
    return INT_VEC2_ZERO;
}