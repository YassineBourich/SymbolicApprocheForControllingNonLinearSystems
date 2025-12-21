#pragma once

#include "../VectorMath.h"
#include <math.h>

extern int dim_x;
extern int dim_u;
extern int dim_w;

extern float tau;

float_vec3 f(float_vec3* x, float_vec2* u, float_vec3* w);