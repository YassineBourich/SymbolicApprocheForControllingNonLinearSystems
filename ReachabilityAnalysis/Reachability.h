#pragma once

#include "VectorMath.h"
#include "ContinuousSystem/Model_3D.h"
#include <stdio.h>

#define MONOTONY_BASED_REACHABILITY 0
#define BOUNDED_JACOBIAN_REACHABILITY 1

typedef short REACHABILITY_METHOD;

float_vec3_pair monotony_based_reachability(float_vec3* x_min, float_vec3* x_max, float_vec2* u, float_vec3* w_min, float_vec3* w_max);

float_vec3_pair bounded_jacobian_reachability(float_vec3* x_min, float_vec3* x_max, float_vec2* u, float_vec3* w_min, float_vec3* w_max, parametrized_matrix Dx, parametrized_matrix Dw);

float_vec3_pair get_reachable_region(float_vec3* x_min, float_vec3* x_max, float_vec2* u, float_vec3* w_min, float_vec3* w_max, REACHABILITY_METHOD reachability_method, parametrized_matrix Dx, parametrized_matrix Dw);