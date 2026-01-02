#pragma once

#include <stdio.h>
#include "../ContinuousSystem/Model_3D.h"
#include "../VectorMath.h"

float_vec2 p(const int_vec2* sigma, 
            const int_vec2* Nu, 
            const float_vec2* u_min, 
            const float_vec2* u_max);