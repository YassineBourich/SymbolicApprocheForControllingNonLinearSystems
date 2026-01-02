#include "KSI.h"

int_vec3 q(const float_vec3* x, 
            const int_vec3* Nx, 
            const float_vec3* x_min, 
            const float_vec3* x_max) {
    if(!float_vec3_all_lte(x_min, x) || !float_vec3_all_lte(x, x_max)) {
        return INT_VEC3_ZERO;
    }

    int_vec3 r;

    r.v1 = (int) ((x->v1 - x_min->v1) * Nx->v1 / (x_max->v1 - x_min->v1)) + 1;
    r.v2 = (int) ((x->v2 - x_min->v2) * Nx->v2 / (x_max->v2 - x_min->v2)) + 1;
    r.v3 = (int) ((x->v3 - x_min->v3) * Nx->v3 / (x_max->v3 - x_min->v3)) + 1;

    return r;
}

float_vec3_pair getPartitionMinAndMax(const int_vec3* ksi, 
                                        const int_vec3* Nx, 
                                        const float_vec3* x_min, 
                                        const float_vec3* x_max) {
    if (int_vec3_all_eq(ksi, &INT_VEC3_ZERO)) {
        printf("Cannot find partition borders of (0, 0, 0)\n");
        return NULL_FLOAT_VEC3_PAIR;
    }

    float_vec3_pair partition_x_min_max;

    float partition_width = (x_max->v1 - x_min->v1) / Nx->v1;
    partition_x_min_max.vect1.v1 = x_min->v1 + (ksi->v1 - 1) * partition_width;
    partition_x_min_max.vect2.v1 = partition_x_min_max.vect1.v1 + partition_width;

    partition_width = (x_max->v2 - x_min->v2) / Nx->v2;
    partition_x_min_max.vect1.v2 = x_min->v2 + (ksi->v2 - 1) * partition_width;
    partition_x_min_max.vect2.v2 = partition_x_min_max.vect1.v2 + partition_width;

    partition_width = (x_max->v3 - x_min->v3) / Nx->v3;
    partition_x_min_max.vect1.v3 = x_min->v3 + (ksi->v3 - 1) * partition_width;
    partition_x_min_max.vect2.v3 = partition_x_min_max.vect1.v3 + partition_width;

    return partition_x_min_max;
}


unsigned int indexToInteger(const int_vec3* ksi, const int_vec3* Nx) {
    if (int_vec3_all_eq(ksi, &INT_VEC3_ZERO)) return 0;

    unsigned int v = 1;

    v = ksi->v1 + Nx->v1 * ((ksi->v2 - 1) + Nx->v2 * (ksi->v3 - 1));

    return v;
}


unsigned int indexToInteger_integers(const size_t p1, const size_t p2, const size_t p3, const int_vec3* Nx) {
    if (p1 <= 0 || p2 <= 0|| p3 <= 0) return 0;
    
    return p1 + Nx->v1 * ((p2 - 1) + Nx->v2 * (p3 - 1));
}