#pragma once
#include "../VectorMath.h"
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "../Discretization/KSI.h"
#include <string.h>

typedef struct {
    uint64_t** data;
    size_t nwords;
    size_t nstages;
    size_t n_ons;
    const int_vec3* Nx;
} int_vec3_ms_bitmap;

#define NULL_VEC3_MS_BITMAP (int_vec3_ms_bitmap){NULL, 0, 0, 0, NULL}

/* Creation */
int_vec3_ms_bitmap ms_bitmap_create_uninitialized(const int_vec3* Nx, int nstages);
int_vec3_ms_bitmap ms_bitmap_create_empty(const int_vec3* Nx, int nstages);
int_vec3_ms_bitmap ms_bitmap_clone(const int_vec3_ms_bitmap* ms_bitmap);

/* Deletion */
void ms_bitmap_free(int_vec3_ms_bitmap* ms_bitmap);

/* Queries */
BOOL ms_bitmap_is_empty(const int_vec3_ms_bitmap* ms_bitmap);
BOOL ms_bitmap_contains(const int_vec3_ms_bitmap* ms_bitmap, int_vec3 e, size_t stage);

/* Modification */
BOOL ms_bitmap_add(int_vec3_ms_bitmap* ms_bitmap, int_vec3 e, size_t stage);
BOOL ms_bitmap_remove(int_vec3_ms_bitmap* ms_bitmap, int_vec3 e, size_t stage);

/* MS BitMap operations */
int_vec3_ms_bitmap ms_bitmap_intersection(const int_vec3_ms_bitmap* a, const int_vec3_ms_bitmap* b);

int_vec3_ms_bitmap ms_bitmap_union(const int_vec3_ms_bitmap* a, const int_vec3_ms_bitmap* b);

BOOL ms_bitmap_equal(const int_vec3_ms_bitmap* a, const int_vec3_ms_bitmap* b);

void ms_bitmap_set_stage_ons(int_vec3_ms_bitmap* a, size_t stage);

int_vec3_stage_arr ms_bitmap_to_array(int_vec3_ms_bitmap* bitmap);

BOOL ms_verify_stage_range(const int_vec3_ms_bitmap* ms_bitmap, size_t stage);

BOOL ms_verify_vector_range(const int_vec3_ms_bitmap* bitmap, size_t v);

static inline BOOL MS_BITMAP_GET(uint64_t** data, int stage, size_t i) {
    return (data[stage][i >> 6] >> (i & 63)) & 1ULL;
}

static inline void MS_BITMAP_SET1(uint64_t** data, int stage, size_t i) {
    data[stage][i >> 6] |= 1ULL << (i & 63);
}

static inline void MS_BITMAP_SET0(uint64_t** data, int stage, size_t i) {
    data[stage][i >> 6] &= ~(1ULL << (i & 63));
}