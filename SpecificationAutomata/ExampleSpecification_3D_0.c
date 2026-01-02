#include "ExampleSpecification_3D_0.h"

int Q = 5;      // Number of states
int SIGMA = 5;  // Number of symbols
int q0 = 0;
int F_size = 1;
int F[] = {3};

int d[5][5] = {
    {0, 1, 2, 0, 4},
    {1, 1, 4, 3, 4},
    {2, 4, 2, 3, 4},
    {3, 3, 3, 3, 3},
    {4, 4, 4, 4, 4},
};

const char* colors[] = {"blue", "green", "yellow","red"};
float rectangls[][2][3] = {
    {{4, 8.5, -PI}, {5, 9.5, PI}},
    {{8.5, 2, -PI}, {9.5, 3, PI}},
    {{2, 0.5, -PI}, {3, 1.5, PI}},
    {{3, 3, -PI}, {7, 7, PI}},
};

int delta(int q, int s) {
    return d[q][s];
}

int l(int_vec3 ksi) {
    //if (float_vec3_all_eq(&ksi, &FLOAT_VEC3_ZERO)) return 4;

    float_vec3_pair x_min_max = getPartitionMinAndMax(&ksi, &Nx, &x_min, &x_max);
    
    float_vec3 r_min, r_max;
    for (size_t c = 1; c < SIGMA; c++) {
        r_min = (float_vec3){rectangls[c][0][0],rectangls[c][0][1],rectangls[c][0][2]};
        r_max = (float_vec3){rectangls[c][1][0],rectangls[c][1][1],rectangls[c][1][2]};
        if (float_vec3_all_lte(&r_min, &x_min_max.vect1) && float_vec3_all_lte(&x_min_max.vect2, &r_max)) {
            return c;
        }
    }

    return 0;
}