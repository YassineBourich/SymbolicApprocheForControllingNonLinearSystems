#pragma once
#include "../VectorMath.h"
#include <stdlib.h>

struct rectangle2 {
    float_vec2 vec_min;
    float_vec2 vec_max;
};

typedef struct rectangle2 rect2;


struct rectangle3 {
    float_vec3 vec_min;
    float_vec3 vec_max;
};

typedef struct rectangle3 rect3;

struct regions {
    rect2* Rectangls;
    const char** colors;
    size_t size;
};

typedef struct regions regions;

regions* regions_create(const float rectangls[][2][3], const char** colors, size_t num_colors);