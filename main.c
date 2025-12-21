#include "ContinuousSystem/Model_3D.h"
#include <stdio.h>

int main() {
    float_vec3 x = {1, 2, 1};
    float_vec2 u = {1, 2};
    float_vec3 w = {1, 1, 1};

    float_vec3 xtp1 = f(&x, &u, &w);

    printf("x0 %f", xtp1.v1);
    printf("x1 %f", xtp1.v2);
    printf("x2 %f", xtp1.v3);
    return 0;
}