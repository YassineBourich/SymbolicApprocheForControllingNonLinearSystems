#include "BitMap.h"

/* Creation */
int_vec3_bitmap bitmap_create_uninitialized(const int_vec3* Nx) {
    size_t nbits = Nx->v1 * Nx->v2 * Nx->v3;

    int_vec3_bitmap bitmap;

    size_t nwords = (nbits + 63) / 64;

    bitmap.nwords = nwords;
    bitmap.n_ons = 0;
    bitmap.Nx = Nx;

    bitmap.data = (uint64_t*)malloc(nwords * sizeof(uint64_t));

    return bitmap;
}

int_vec3_bitmap bitmap_create_empty(const int_vec3* Nx) {
    size_t nbits = Nx->v1 * Nx->v2 * Nx->v3;

    int_vec3_bitmap bitmap;

    size_t nwords = (nbits + 63) / 64;

    bitmap.nwords = nwords;
    bitmap.n_ons = 0;
    bitmap.Nx = Nx;

    bitmap.data = calloc(nwords, sizeof(uint64_t));

    return bitmap;
}

int_vec3_bitmap bitmap_create_from_array_vec3(int_vec3 arr[], unsigned int arr_size, const int_vec3* Nx) {
    int_vec3_bitmap bitmap = bitmap_create_empty(Nx);

    for (int i = 0; i < arr_size; i++) {
        BITMAP_SET1(bitmap.data, indexToInteger(arr + i, Nx));
        bitmap.n_ons++;
    }

    return bitmap;
}

int_vec3_bitmap bitmap_clone(const int_vec3_bitmap* bitmap) {
    int_vec3_bitmap clone;
    clone.nwords = bitmap->nwords;
    clone.n_ons = bitmap->n_ons;
    clone.Nx = bitmap->Nx;

    clone.data = (uint64_t*)malloc(clone.nwords * sizeof(uint64_t));
    memcpy(clone.data, bitmap->data, clone.nwords * sizeof(uint64_t));

    return clone;
}

/* Deleting */
void bitmap_free(int_vec3_bitmap* bitmap) {
    if (bitmap->data == NULL) return;

    free(bitmap->data);

    bitmap->data = NULL;
    bitmap->nwords = 0;
    bitmap->n_ons = 0;
}


/* Queries */
BOOL bitmap_is_empty(const int_vec3_bitmap* bitmap) {
    return bitmap->n_ons == 0;
}

BOOL bitmap_contains(const int_vec3_bitmap* bitmap, int_vec3 e) {
    size_t v = indexToInteger(&e, bitmap->Nx);
    if (!verify_vector_range(bitmap, v)) {
        return FALSE;
    }


    return BITMAP_GET(bitmap->data, v);
}


/* Modification */
BOOL bitmap_add(int_vec3_bitmap* bitmap, int_vec3 e) {
    size_t v = indexToInteger(&e, bitmap->Nx);
    if (!verify_vector_range(bitmap, v)) {
        return FALSE;
    }

    if (!BITMAP_GET(bitmap->data, v)) bitmap->n_ons++;

    BITMAP_SET1(bitmap->data, v);
    return TRUE;
}

BOOL bitmap_remove(int_vec3_bitmap* bitmap, int_vec3 e) {
    size_t v = indexToInteger(&e, bitmap->Nx);
    if (!verify_vector_range(bitmap, v)) {
        return FALSE;
    }
    
    if (BITMAP_GET(bitmap->data, v)) bitmap->n_ons--;

    BITMAP_SET0(bitmap->data, v);
    return TRUE;
}


/* BitSet operations */
int_vec3_bitmap bitmap_intersection(const int_vec3_bitmap* a, const int_vec3_bitmap* b) {
    if (!int_vec3_all_eq(a->Nx, b->Nx) || a->nwords != b->nwords) {
        return NULL_VEC3_BITMAP;
    }
    
    int_vec3_bitmap bitmap = bitmap_create_uninitialized(a->Nx);

    uint64_t w;
    size_t ones = 0;
    for (size_t i = 0; i < b->nwords; i++) {
        w = a->data[i] & b->data[i];
        bitmap.data[i] = w;
        ones += __builtin_popcountll(w);
    }
    bitmap.n_ons = ones;

    return bitmap;
}

int_vec3_bitmap bitmap_union(const int_vec3_bitmap* a, const int_vec3_bitmap* b) {
    if (!int_vec3_all_eq(a->Nx, b->Nx) || a->nwords != b->nwords) {
        return NULL_VEC3_BITMAP;
    }
    
    int_vec3_bitmap bitmap = bitmap_create_uninitialized(a->Nx);

    uint64_t w;
    size_t ones = 0;
    for (size_t i = 0; i < b->nwords; i++) {
        w = a->data[i] | b->data[i];
        bitmap.data[i] = w;
        ones += __builtin_popcountll(w);
    }
    bitmap.n_ons = ones;

    return bitmap;
}

BOOL bitmap_equal(const int_vec3_bitmap* a, const int_vec3_bitmap* b) {
    if (!int_vec3_all_eq(a->Nx, b->Nx) || a->nwords != b->nwords || a->n_ons != b->n_ons) {
        return FALSE;
    }

    for (size_t i = 0; i < b->nwords; i++) {
        if(a->data[i] != b->data[i]) {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL hyperrectangle_is_subset_of_bitmap(int_vec3_pair* r_min_max, int_vec3_bitmap* bitmap) {
    if (!verify_vector_range(bitmap, indexToInteger(&r_min_max->vect2, bitmap->Nx))) {
        return FALSE;
    }

    for (size_t p1 = r_min_max->vect1.v1; p1 <= r_min_max->vect2.v1; p1++) {
        for (size_t p2 = r_min_max->vect1.v2; p2 <= r_min_max->vect2.v2; p2++) {
            for (size_t p3 = r_min_max->vect1.v3; p3 <= r_min_max->vect2.v3; p3++) {
                if (!BITMAP_GET(bitmap->data, indexToInteger_integers(p1, p2, p3, bitmap->Nx))) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

int_vec3* bitmap_to_array(int_vec3_bitmap* bitmap) {
    int_vec3* vec3_arr = (int_vec3*)malloc(sizeof(int_vec3) * bitmap->n_ons);

    if (vec3_arr == NULL) {
        return NULL;
    }

    size_t vec_idx = 0;
    for (size_t p1 = 0; p1 < bitmap->Nx->v1; p1++) {
        for (size_t p2 = 1; p2 < bitmap->Nx->v2; p2++) {
            for (size_t p3 = 1; p3 < bitmap->Nx->v3; p3++) {
                if (BITMAP_GET(bitmap->data, indexToInteger_integers(p1, p2, p3, bitmap->Nx))) {
                    if (p1 == 0) {
                        vec3_arr[vec_idx] = INT_VEC3_ZERO;
                    } else {
                        vec3_arr[vec_idx] = (int_vec3){p1, p2, p3};
                    }
                    vec_idx++;
                }
            }
        }
    }

    return vec3_arr;
}

BOOL verify_vector_range(int_vec3_bitmap* bitmap, size_t v) {
    if (v >= bitmap->Nx->v1 * bitmap->Nx->v2 * bitmap->Nx->v3) {
        printf("Vector out of range\n");
        return FALSE;
    }

    return TRUE;
}

static inline BOOL BITMAP_GET(const uint64_t* data, size_t i) {
    return (data[i >> 6] >> (i & 63)) & 1ULL;
}

static inline void BITMAP_SET1(uint64_t* data, size_t i) {
    data[i >> 6] |= 1ULL << (i & 63);
}

static inline void BITMAP_SET0(uint64_t* data, size_t i) {
    data[i >> 6] &= ~(1ULL << (i & 63));
}
