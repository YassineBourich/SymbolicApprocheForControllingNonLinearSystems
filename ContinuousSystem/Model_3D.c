#include "Model_3D.h"

int dim_x = 3;
int dim_u = 2;
int dim_w = 3;

float tau = 1;

float_vec3 f(float_vec3* x, float_vec2* u, float_vec3* w) {
    float_vec3 xtp1;

    xtp1.v1 = x->v1 + tau * (cos(x->v3) * u->v1 + w->v1);
    xtp1.v2 = x->v2 + tau * (sin(x->v3) * u->v1 + w->v2);
    xtp1.v3 = fmod(x->v3 + tau * (u->v2 + w->v3), 2 * PI) - PI;

    return xtp1;
}