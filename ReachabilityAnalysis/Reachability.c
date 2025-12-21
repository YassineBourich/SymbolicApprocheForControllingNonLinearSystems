#include "Reachability.h"

float_vec3_pair monotony_based_reachability(float_vec3* x_min, float_vec3* x_max, float_vec2* u, float_vec3* w_min, float_vec3* w_max) {
    float_vec3_pair f_min_max;
    f_min_max.vect1 = f(x_min, u, w_min);
    f_min_max.vect2 = f(x_max, u, w_max);

    return f_min_max;
}

float_vec3_pair bounded_jacobian_reachability(float_vec3* x_min, float_vec3* x_max, float_vec2* u, float_vec3* w_min, float_vec3* w_max, parametrized_matrix Dx, parametrized_matrix Dw) {
    if (Dx == NULL && Dw == NULL) {
        printf("Bounded jacobian reachability must have Dx and Dw defined\n");
        return NULL_FLOAT_VEC3_PAIR;
    }

    float_vec3 x_star = scalar_vec3_mult(0.5, vec3_add(*x_max, *x_min));        // x* = (x_max + x_min) / 2
    float_vec3 delta_x = scalar_vec3_mult(0.5, vec3_sub(*x_max, *x_min));       // dx = (x_max - x_min) / 2

    
    float_vec3 w_star = scalar_vec3_mult(0.5, vec3_add(*w_max, *w_min));        // w* = (w_max + w_min) / 2
    float_vec3 delta_w = scalar_vec3_mult(0.5, vec3_sub(*w_max, *w_min));       // dw = (w_max - w_min) / 2

    float_vec3 f_star = f(&x_star, u, &w_star);                                 // f(x*, u, w*)

    float_vec3_pair f_min_max;

    float_vec3 Dxdx = matrix3_vec3_mult(Dx(*u), delta_x);                       // Dx(u)*delta_x
    float_vec3 Dwdw = matrix3_vec3_mult(Dw(*u), delta_w);                       // Dw(u)*delta_w
    float_vec3 DxdxpDwdw = vec3_add(Dxdx, Dwdw);

    f_min_max.vect1 = vec3_sub(f_star, DxdxpDwdw);                              // f_min = f* - Dxdx - Dwdw
    f_min_max.vect2 = vec3_add(f_star, DxdxpDwdw);                              // f_max = f* + Dxdx + Dwdw

    return f_min_max;
}

float_vec3_pair get_reachable_region(float_vec3* x_min, float_vec3* x_max, float_vec2* u, float_vec3* w_min, float_vec3* w_max, REACHABILITY_METHOD reachability_method, parametrized_matrix Dx, parametrized_matrix Dw) {
    if (reachability_method == MONOTONY_BASED_REACHABILITY && Dx == NULL && Dw == NULL) {
        return monotony_based_reachability(x_min, x_max, u, w_min, w_max);
    } else if (reachability_method == BOUNDED_JACOBIAN_REACHABILITY && Dx != NULL && Dw != NULL) {
        return bounded_jacobian_reachability(x_min, x_max, u, w_min, w_max, Dx, Dw);
    }

    printf("Unsupported reachability method\n");
    return NULL_FLOAT_VEC3_PAIR;
}