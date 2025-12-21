#include "VectorMath.h"

// Vector3
int_vec3* INT_VEC3_ZERO_PTR() {
    static int_vec3 zero = {0, 0, 0};
    return &zero;
}

BOOL float_vec3_all_lte(const float_vec3* vect1, const float_vec3* vect2) {
    return (vect1->v1 <= vect2->v1) && (vect1->v2 <= vect2->v2) && (vect1->v3 <= vect2->v3);
}

BOOL int_vec3_all_lte(const int_vec3* vect1, const int_vec3* vect2) {
    return (vect1->v1 <= vect2->v1) && (vect1->v2 <= vect2->v2) && (vect1->v3 <= vect2->v3);
}

BOOL float_vec3_all_eq(const float_vec3* vect1, const float_vec3* vect2) {
    return (vect1->v1 == vect2->v1) && (vect1->v2 == vect2->v2) && (vect1->v3 == vect2->v3);
}

BOOL int_vec3_all_eq(const int_vec3* vect1, const int_vec3* vect2) {
    return (vect1->v1 == vect2->v1) && (vect1->v2 == vect2->v2) && (vect1->v3 == vect2->v3);
}

// Vector2
int_vec2* INT_VEC2_ZERO_PTR() {
    static float_vec2 zero = {0.0f, 0.0f};
    return &zero;
}

BOOL float_vec2_all_lte(const float_vec2* vect1, const float_vec2* vect2) {
    return (vect1->v1 <= vect2->v1) && (vect1->v2 <= vect2->v2);
}

BOOL int_vec2_all_lte(const int_vec2* vect1, const int_vec2* vect2) {
    return (vect1->v1 <= vect2->v1) && (vect1->v2 <= vect2->v2);
}

BOOL float_vec2_all_eq(const float_vec2* vect1, const float_vec2* vect2) {
    return (vect1->v1 == vect2->v1) && (vect1->v2 == vect2->v2);
}

BOOL int_vec2_all_eq(const int_vec2* vect1, const int_vec2* vect2) {
    return (vect1->v1 == vect2->v1) && (vect1->v2 == vect2->v2);
}

// Matrix3
float_vec3 vec3_add(float_vec3 a, float_vec3 b) {
    return (float_vec3){a.v1 + b.v1, a.v2 + b.v2, a.v3 + b.v3};
}

float_vec3 vec3_sub(float_vec3 a, float_vec3 b) {
    return (float_vec3){a.v1 - b.v1, a.v2 - b.v2, a.v3 - b.v3};
}

float_vec3 scalar_vec3_mult(float b, float_vec3 a) {
    return (float_vec3){b * a.v1, b * a.v2, b * a.v3};
}

float_vec3 matrix3_vec3_mult(matrix3 M, float_vec3 v) {
    float_vec3 Mv;

    Mv.v1 = M.a00 * v.v1 + M.a01 * v.v2 + M.a02 * v.v3;
    Mv.v2 = M.a10 * v.v1 + M.a11 * v.v2 + M.a12 * v.v3;
    Mv.v3 = M.a20 * v.v1 + M.a21 * v.v2 + M.a22 * v.v3;

    return Mv;
}

BOOL increment_vec3(int_vec3* min_vec, int_vec3* max_vec, int_vec3 vector) {

}