#pragma once

#include "boolean.h"
#define PI 3.14159265358979323846

typedef struct {
    float v1, v2, v3;
} float_vec3;

typedef struct {
    int v1, v2, v3;
} int_vec3;

#define INT_VEC3_ZERO ((int_vec3){0, 0, 0})
#define FLOAT_VEC3_ZERO ((float_vec3){0.0f, 0.0f, 0.0f})

BOOL float_vec3_all_lte(const float_vec3* vect1, const float_vec3* vect2);
BOOL int_vec3_all_lte(const int_vec3* vect1, const int_vec3* vect2);

BOOL float_vec3_all_eq(const float_vec3* vect1, const float_vec3* vect2);
BOOL int_vec3_all_eq(const int_vec3* vect1, const int_vec3* vect2);

typedef struct {
    float v1, v2;
} float_vec2;

typedef struct {
    int v1, v2;
} int_vec2;

#define INT_VEC2_ZERO ((int_vec2){0, 0})
#define FLOAT_VEC2_ZERO ((float_vec2){0.0f, 0.0f})

BOOL float_vec2_all_lte(const float_vec2* vect1, const float_vec2* vect2);
BOOL int_vec2_all_lte(const int_vec2* vect1, const int_vec2* vect2);

BOOL float_vec2_all_eq(const float_vec2* vect1, const float_vec2* vect2);
BOOL int_vec2_all_eq(const int_vec2* vect1, const int_vec2* vect2);

typedef struct {
    float_vec3 vect1;
    float_vec3 vect2;
} float_vec3_pair;

typedef struct {
    int_vec3 vect1;
    int_vec3 vect2;
} int_vec3_pair;

#define NULL_FLOAT_VEC3_PAIR ((float_vec3_pair){{0, 0, 0}, {0, 0, 0}})
#define NULL_INT_VEC3_PAIR ((int_vec3_pair){{0, 0, 0}, {0, 0, 0}})

typedef struct {
    float a00, a01, a02, a10, a11, a12, a20, a21, a22;
} matrix3;

float_vec3 vec3_add(float_vec3 a, float_vec3 b);

float_vec3 vec3_sub(float_vec3 a, float_vec3 b);

float_vec3 scalar_vec3_mult(float b, float_vec3 a);

float_vec3 matrix3_vec3_mult(matrix3 M, float_vec3 v);

typedef matrix3 (*parametrized_matrix)(float_vec2);

BOOL increment_vec3(int_vec3* min_vec, int_vec3* max_vec, int_vec3 vector);