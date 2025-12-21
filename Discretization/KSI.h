#pragma once

#include "ContinuousSystem/Model_3D.h"
#include <stdio.h>

int_vec3 q(const float_vec3* x, 
            const int_vec3* Nx, 
            const float_vec3* x_min, 
            const float_vec3* x_max);

float_vec3_pair getPartitionMinAndMax(const int_vec3* ksi, 
                                        const int_vec3* Nx, 
                                        const float_vec3* x_min, 
                                        const float_vec3* x_max);

unsigned int indexToInteger(const int_vec3* ksi, const int_vec3* Nx);
unsigned int indexToInteger_integers(const size_t p1, const size_t p2, const size_t p3, const int_vec3* Nx);