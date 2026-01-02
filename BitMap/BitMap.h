#pragma once
#include "../VectorMath.h"
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "../Discretization/KSI.h"
#include <string.h>

struct int_vec3_bitmap {
    uint64_t* data;
    size_t nwords;
    size_t n_ons;
    const int_vec3* Nx;
};

typedef struct int_vec3_bitmap int_vec3_bitmap;

#define NULL_VEC3_BITMAP (int_vec3_bitmap){NULL, 0, 0, NULL}

/* Creation */
int_vec3_bitmap bitmap_create_uninitialized(const int_vec3* Nx);
int_vec3_bitmap bitmap_create_empty(const int_vec3* Nx);
int_vec3_bitmap bitmap_create_from_array_vec3(int_vec3 arr[], unsigned int arr_size, const int_vec3* Nx);
int_vec3_bitmap bitmap_clone(const int_vec3_bitmap* bitmap);

/* Deletion */
void bitmap_free(int_vec3_bitmap* bitmap);

/* Queries */
BOOL bitmap_is_empty(const int_vec3_bitmap* bitmap);
BOOL bitmap_contains(const int_vec3_bitmap* bitmap, int_vec3 e);

/* Modification */
BOOL bitmap_add(int_vec3_bitmap* bitmap, int_vec3 e);
BOOL bitmap_remove(int_vec3_bitmap* bitmap, int_vec3 e);

/* BitMap operations */
int_vec3_bitmap bitmap_intersection(const int_vec3_bitmap* a, const int_vec3_bitmap* b);

int_vec3_bitmap bitmap_union(const int_vec3_bitmap* a, const int_vec3_bitmap* b);

BOOL bitmap_equal(const int_vec3_bitmap* a, const int_vec3_bitmap* b);

BOOL hyperrectangle_is_subset_of_bitmap(int_vec3_pair* r_min_max, const int_vec3_bitmap* bitmap);

int_vec3_arr bitmap_to_array(int_vec3_bitmap* bitmap);

BOOL verify_vector_range(const int_vec3_bitmap* bitmap, size_t v);

static inline BOOL BITMAP_GET(const uint64_t* data, size_t i) {
    return (data[i >> 6] >> (i & 63)) & 1ULL;
}

static inline void BITMAP_SET1(uint64_t* data, size_t i) {
    data[i >> 6] |= 1ULL << (i & 63);
}

static inline void BITMAP_SET0(uint64_t* data, size_t i) {
    data[i >> 6] &= ~(1ULL << (i & 63));
}
