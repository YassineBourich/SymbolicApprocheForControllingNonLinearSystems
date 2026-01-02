#include "SIGMA.h"

float_vec2 p(const int_vec2* sigma, 
            const int_vec2* Nu, 
            const float_vec2* u_min, 
            const float_vec2* u_max) {
    if (int_vec2_all_eq(sigma, &INT_VEC2_ZERO)) {
        printf("Cannot find command of (0, 0)\n");
        return FLOAT_VEC2_ZERO;
    }

    float_vec2 u;

    float command_width = (u_min->v1 - u_max->v1) / Nu->v1;
    u.v1 = u_min->v1 + (sigma->v1 - 0.5) * command_width;

    command_width = (u_max->v2 - u_min->v2) / Nu->v2;
    u.v2 = u_min->v2 + (sigma->v2 - 0.5) * command_width;

    return u;
}