#pragma once
#include "VectorMath.h"
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "KSI.h"

#define MS_BITMAP_GET(ms_bitmap_data, stage, i) ((ms_bitmap_data[stage][i >> 3]) >> (i & 7)) & 1U
#define MS_BITMAP_SET1(ms_bitmap_data, stage, i) (ms_bitmap_data[stage][i >> 3]) |= (1U << (i & 7))
#define MS_BITMAP_SET0(ms_bitmap_data, stage, i) (ms_bitmap_data[stage][i >> 3]) &= ~(1U << (i & 7))

typedef struct {
    uint8_t** data;
    size_t nbytes;
    size_t nstages;
    size_t n_ons;
    int_vec3* Nx;
} int_vec3_ms_bitmap;

/* Creation */
int_vec3_ms_bitmap ms_bitmap_create_empty(const int_vec3* Nx, int nstages);
int_vec3_ms_bitmap ms_bitmap_clone(const int_vec3_ms_bitmap* ms_bitmap);

/* Deletion */
void ms_bitmap_free(int_vec3_ms_bitmap* ms_bitmap);

/* Queries */
BOOL ms_bitmap_is_empty(const int_vec3_ms_bitmap* ms_bitmap);
BOOL ms_bitmap_contains(const int_vec3_ms_bitmap* ms_bitmap, int_vec3 e, size_t stage);
BOOL ms_bitmap_is_subset(const int_vec3_ms_bitmap* a, const int_vec3_ms_bitmap* b);

/* Modification */
BOOL ms_bitmap_add(int_vec3_ms_bitmap* ms_bitmap, int_vec3 e);
BOOL ms_bitmap_remove(int_vec3_ms_bitmap* ms_bitmap, int_vec3 e);

/* Set operations */
int_vec3_ms_bitmap ms_bitmap_intersection(
    const int_vec3_ms_bitmap* a,
    const int_vec3_ms_bitmap* b
);

int_vec3_ms_bitmap ms_bitmap_union(
    const int_vec3_ms_bitmap* a,
    const int_vec3_ms_bitmap* b
);
