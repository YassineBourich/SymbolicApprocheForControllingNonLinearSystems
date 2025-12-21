#include "SymbolicModel.h"

float_vec3 x_min = {0, 0, -PI};
float_vec3 x_max = {10, 10, PI};
float_vec2 u_min = {0.25, -1};
float_vec2 u_max = {1, 1};
float_vec3 w_min = {-0.05, -0.05, -0.05};
float_vec3 w_max = {0.05, 0.05, 0.05};

int_vec3 Nx = {NX_1, NX_2, NX_3};
int_vec2 Nu = {NU_1, NU_2};

symb_model* m;

matrix3 Jacx(float_vec2 u) {
    return (matrix3){1, 0, tau * fabsf(u.v1), 0, 1, tau * fabsf(u.v1), 0, 0, 1};
}

matrix3 Jacw(float_vec2 u) {
    return (matrix3){tau, 0, 0, 0, tau, 0, 0, 0, tau};
}

symb_model* construct_symbolic_model(short reachability_method) {
    parametrized_matrix Dx = NULL;
    parametrized_matrix Dw = NULL;
    if (reachability_method == BOUNDED_JACOBIAN_REACHABILITY) {
        Dx = Jacx;
        Dw = Jacw;
    }

    symb_model* m = (symb_model*)malloc(sizeof(symb_model));

    model_node node;

    for (int c1 = 0; c1 < NU_1; c1++) {
        for (int c2 = 0; c2 < NU_2; c2++) {
            node.q_min_max = NULL_INT_VEC3_PAIR;
            node.includes_0 = 1;
            m->model[0][0][0][c1][c2] = node;
        }
    }

    float_vec3_pair p_x_min_max;
    float_vec2 u_sigma;
    float_vec3_pair f_min_max;
    int_vec3 q_min;
    int_vec3 q_max;
    for (int p1 = 0; p1 < NX_1; p1++) {
        for (int p2 = 0; p2 < NX_2; p2++) {
            for (int p3 = 0; p3 < NX_3; p3++) {
                for (int c1 = 0; c1 < NU_1; c1++) {
                    for (int c2 = 0; c2 < NU_2; c2++) {
                        p_x_min_max = getPartitionMinAndMax(&(int_vec3){p1, p2, p3}, &Nx, &x_min, &x_max);
                        u_sigma = p(&(int_vec2){c1, c2}, &Nx, &u_min, &u_max);

                        f_min_max = get_reachable_region(&p_x_min_max.vect1, &p_x_min_max.vect2, &u_sigma, &w_min, &w_max, reachability_method, Dx, Dw);

                        if (is_totaly_out_of_grid(f_min_max)) {
                            node.q_min_max = NULL_INT_VEC3_PAIR;
                            node.includes_0 = 1;
                        } else {
                            node.includes_0 = crop_reachable_region(&f_min_max);
                            if (node.includes_0) {
                                node.q_min_max = NULL_INT_VEC3_PAIR;
                            } else {
                                q_min = q(&f_min_max.vect1, &Nx, &x_min, &x_max);
                                q_max = q(&f_min_max.vect2, &Nx, &x_min, &x_max);
                                node.q_min_max = (int_vec3_pair){q_min, q_max};
                            }
                        }

                        m->model[p1][p2][p3][c1][c2] = node;
                    }
                }
            }
        }
    }

    return m;
}

model_node g(const int_vec3 ksi, const int_vec2 sigma) {
    return m->model[ksi.v1][ksi.v2][ksi.v3][sigma.v1][sigma.v2];
}

BOOL is_totaly_out_of_grid(float_vec3_pair f_min_max) {
    return !float_vec3_all_lte(&f_min_max.vect1, &x_max) || !float_vec3_all_lte(&x_min, &f_min_max.vect2);
}

BOOL crop_reachable_region(float_vec3_pair* f_min_max) {
    BOOL is_croped = FALSE;
    float partition_width;

    if (f_min_max->vect1.v1 < x_min.v1) {
        f_min_max->vect1.v1 = x_min.v1;
        is_croped = TRUE;
    }
    if (f_min_max->vect2.v1 > x_max.v1) {
        partition_width = (x_max.v1 - x_min.v1) / Nx.v1;
        f_min_max->vect2.v1 = x_max.v1 - partition_width * 0.25;
        is_croped = TRUE;
    }

    if (f_min_max->vect1.v2 < x_min.v2) {
        f_min_max->vect1.v2 = x_min.v2;
        is_croped = TRUE;
    }
    if (f_min_max->vect2.v2 > x_max.v2) {
        partition_width = (x_max.v2 - x_min.v2) / Nx.v2;
        f_min_max->vect2.v2 = x_max.v2 - partition_width * 0.25;
        is_croped = TRUE;
    }

    if (f_min_max->vect1.v3 < x_min.v3) {
        f_min_max->vect1.v3 = x_min.v3;
        is_croped = TRUE;
    }
    if (f_min_max->vect2.v3 > x_max.v3) {
        partition_width = (x_max.v3 - x_min.v3) / Nx.v3;
        f_min_max->vect2.v3 = x_max.v3 - partition_width * 0.25;
        is_croped = TRUE;
    }

    return is_croped;
}


int_vec3_bitmap Pre(int_vec3_bitmap* R) {
    int_vec3_bitmap predecessors = bitmap_create_empty(&Nx);

    int_vec3 ksi;
    for (size_t p1 = 1; p1 < Nx.v1; p1++) {
        for (size_t p2 = 1; p2 < Nx.v2; p2++) {
            for (size_t p3 = 1; p3 < Nx.v3; p3++) {
                ksi = (int_vec3){p1, p2, p3};
                if (exists_sigma_st_g_ksi_sigma_is_pre(ksi, R)) {
                    bitmap_add(&predecessors, ksi);
                }
            }
        }
    }

    return predecessors;
}

BOOL exists_sigma_st_g_ksi_sigma_is_pre(int_vec3 ksi, int_vec3_bitmap* R) {
    for (size_t c1 = 1; c1 < Nu.v1; c1++) {
        for (size_t c2 = 1; c2 < Nu.v2; c2++) {
            model_node node = g(ksi, (int_vec2){c1, c2});
            if (node.includes_0) {
                continue;
            }

            if (hyperrectangle_is_subset_of_bitmap(&node.q_min_max, R)) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int_vec2 exists_sigma_st_g_ksi_sigma_is_pre(int_vec3 ksi, int_vec3_bitmap* R) {
    int_vec2 sigma;
    for (size_t c1 = 1; c1 < Nu.v1; c1++) {
        for (size_t c2 = 1; c2 < Nu.v2; c2++) {
            sigma = (int_vec2){c1, c2};
            model_node node = g(ksi, sigma);
            if (node.includes_0) {
                continue;
            }

            if (hyperrectangle_is_subset_of_bitmap(&node.q_min_max, R)) {
                return sigma;
            }
        }
    }
    return INT_VEC2_ZERO;
}