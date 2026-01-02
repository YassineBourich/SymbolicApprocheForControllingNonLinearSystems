#include "MultiStageBitMap.h"

/* Creation */
int_vec3_ms_bitmap ms_bitmap_create_uninitialized(const int_vec3* Nx, int nstages) {
    int bitmap_size = Nx->v1 * Nx->v2 * Nx->v3;

    int_vec3_ms_bitmap ms_bitmap;

    bitmap_size = (bitmap_size + 63) / 64;

    ms_bitmap.nwords = bitmap_size;
    ms_bitmap.nstages = nstages;
    ms_bitmap.n_ons = 0;
    ms_bitmap.Nx = Nx;

    ms_bitmap.data = (uint64_t**)malloc(nstages * sizeof(uint64_t*));

    for (int i = 0; i < nstages; i++)
        ms_bitmap.data[i] = (uint64_t*)malloc(bitmap_size * sizeof(uint64_t));

    return ms_bitmap;
}

int_vec3_ms_bitmap ms_bitmap_create_empty(const int_vec3* Nx, int nstages) {
    int bitmap_size = Nx->v1 * Nx->v2 * Nx->v3;

    int_vec3_ms_bitmap ms_bitmap;

    bitmap_size = (bitmap_size + 63) / 64;

    ms_bitmap.nwords = bitmap_size;
    ms_bitmap.nstages = nstages;
    ms_bitmap.n_ons = 0;
    ms_bitmap.Nx = Nx;

    ms_bitmap.data = (uint64_t**)malloc(nstages * sizeof(uint64_t*));

    for (int i = 0; i < nstages; i++)
        ms_bitmap.data[i] = calloc(bitmap_size, sizeof(uint64_t));

    return ms_bitmap;
}

int_vec3_ms_bitmap ms_bitmap_clone(const int_vec3_ms_bitmap* ms_bitmap) {
    int_vec3_ms_bitmap clone;
    clone.nstages = ms_bitmap->nstages;
    clone.nwords = ms_bitmap->nwords;
    clone.n_ons = ms_bitmap->n_ons;
    clone.Nx = ms_bitmap->Nx;

    clone.data = (uint64_t**)malloc(clone.nstages * sizeof(uint64_t*));

    for (int i = 0; i < clone.nstages; i++) {
        clone.data[i] = (uint64_t*)malloc(clone.nwords * sizeof(uint64_t));
        memcpy(clone.data[i], ms_bitmap->data[i], clone.nwords * sizeof(uint64_t));
    }

    return clone;
}

/* Deletion */
void ms_bitmap_free(int_vec3_ms_bitmap* ms_bitmap) {
    for (int i = 0; i < ms_bitmap->nstages; i++)
        free(ms_bitmap->data[i]);
    free(ms_bitmap->data);

    ms_bitmap->data = NULL;
    ms_bitmap->nstages = 0;
    ms_bitmap->nwords = 0;
    ms_bitmap->n_ons = 0;
}

/* Queries */
BOOL ms_bitmap_is_empty(const int_vec3_ms_bitmap* ms_bitmap) {
    return ms_bitmap->n_ons == 0;
}

BOOL ms_bitmap_contains(const int_vec3_ms_bitmap* ms_bitmap, int_vec3 e, size_t stage) {
    if (!ms_verify_stage_range(ms_bitmap, stage)) {
        return FALSE;
    }
    size_t v = indexToInteger(&e, ms_bitmap->Nx);
    if (!ms_verify_vector_range(ms_bitmap, v)) {
        return FALSE;
    }

    return MS_BITMAP_GET(ms_bitmap->data, stage, indexToInteger(&e, ms_bitmap->Nx));
}

/* Modification */
BOOL ms_bitmap_add(int_vec3_ms_bitmap* ms_bitmap, int_vec3 e, size_t stage) {
    if (!ms_verify_stage_range(ms_bitmap, stage)) {
        return FALSE;
    }
    size_t v = indexToInteger(&e, ms_bitmap->Nx);
    if (!ms_verify_vector_range(ms_bitmap, v)) {
        return FALSE;
    }

    MS_BITMAP_SET1(ms_bitmap->data, stage, indexToInteger(&e, ms_bitmap->Nx));
    return TRUE;
}

BOOL ms_bitmap_remove(int_vec3_ms_bitmap* ms_bitmap, int_vec3 e, size_t stage) {
    if (!ms_verify_stage_range(ms_bitmap, stage)) {
        return FALSE;
    }
    size_t v = indexToInteger(&e, ms_bitmap->Nx);
    if (!ms_verify_vector_range(ms_bitmap, v)) {
        return FALSE;
    }

    MS_BITMAP_SET0(ms_bitmap->data, stage, indexToInteger(&e, ms_bitmap->Nx));
    return TRUE;
}

/* Set operations */
int_vec3_ms_bitmap ms_bitmap_intersection(const int_vec3_ms_bitmap* a, const int_vec3_ms_bitmap* b) {
    if (a->nstages != b->nstages || !int_vec3_all_eq(a->Nx, b->Nx) || a->nwords != b->nwords) {
        return NULL_VEC3_MS_BITMAP;
    }
    
    int_vec3_ms_bitmap ms_bitmap = ms_bitmap_create_uninitialized(a->Nx, a->nstages);

    uint64_t w;
    size_t ones = 0;
    for (size_t s = 0; s < b ->nstages; s++) {
        for (size_t i = 0; i < b->nwords; i++) {
            w = a->data[s][i] & b->data[s][i];
            ms_bitmap.data[s][i] = w;
            ones += __builtin_popcountll(w);
        }
    }
    ms_bitmap.n_ons = ones;

    return ms_bitmap;
}

int_vec3_ms_bitmap ms_bitmap_union(const int_vec3_ms_bitmap* a, const int_vec3_ms_bitmap* b) {
    if (a->nstages != b->nstages || !int_vec3_all_eq(a->Nx, b->Nx) || a->nwords != b->nwords) {
        return NULL_VEC3_MS_BITMAP;
    }
    
    int_vec3_ms_bitmap ms_bitmap = ms_bitmap_create_uninitialized(a->Nx, a->nstages);

    uint64_t w;
    size_t ones = 0;
    for (size_t s = 0; s < b ->nstages; s++) {
        for (size_t i = 0; i < b->nwords; i++) {
            w = a->data[s][i] | b->data[s][i];
            ms_bitmap.data[s][i] = w;
            ones += __builtin_popcountll(w);
        }
    }
    ms_bitmap.n_ons = ones;

    return ms_bitmap;
}

BOOL ms_bitmap_equal(const int_vec3_ms_bitmap* a, const int_vec3_ms_bitmap* b) {
    if (a->nstages != b->nstages || !int_vec3_all_eq(a->Nx, b->Nx) || a->nwords != b->nwords || a->n_ons != b->n_ons) {
        return FALSE;
    }

    for (size_t s = 0; s < b ->nstages; s++) {
        for (size_t i = 0; i < b->nwords; i++) {
            if(a->data[s][i] != b->data[s][i]) {
                return FALSE;
            }
        }
    }

    return TRUE;
}

void ms_bitmap_set_stage_ons(int_vec3_ms_bitmap* a, size_t stage) {
    for (size_t i = 0; i < a->nwords; i++) {
        a->data[stage][i] = UINT64_MAX;
    }

    a->n_ons += a->nwords * 64;
}

int_vec3_stage_arr ms_bitmap_to_array(int_vec3_ms_bitmap* bitmap) {
    int_vec3_stage_arr arr;
    arr.data = (int_vec3*)malloc(sizeof(int_vec3) * bitmap->n_ons);
    arr.stages = (int*)malloc(sizeof(int) * bitmap->n_ons);
    arr.size = bitmap->n_ons;

    if (arr.data == NULL || arr.stages == NULL) {
        return NULL_INT_VEC3_STAGE_ARR;
    }

    size_t vec_idx = 0;
    for (size_t p1 = 1; p1 <= bitmap->Nx->v1; p1++) {
        printf("%llu/%llu\n", vec_idx+1, bitmap->n_ons);
        for (size_t p2 = 1; p2 <= bitmap->Nx->v2; p2++) {
            for (size_t p3 = 1; p3 <= bitmap->Nx->v3; p3++) {
                for (int s = 0; s < bitmap->nstages; s++) {
                    //printf("%llu: %llu\n", p1, vec_idx);
                    if (MS_BITMAP_GET(bitmap->data, s, indexToInteger_integers(p1, p2, p3, bitmap->Nx))) {
                        //printf("%llu/%llu passed for %llu, %llu, %llu, %d\n", vec_idx+1, bitmap->n_ons, p1, p2, p3, s);
                        if (p1 == 0) {
                            arr.data[vec_idx] = INT_VEC3_ZERO;
                        } else {
                            arr.data[vec_idx] = (int_vec3){p1, p2, p3};
                        }
                        arr.stages[vec_idx] = s;
                        vec_idx++;
                    }
                }
            }
        }
    }
    printf("tttt\n");

    return arr;
}

BOOL ms_verify_stage_range(const int_vec3_ms_bitmap* ms_bitmap, size_t stage) {
    if (stage >= ms_bitmap->nstages) {
        printf("Stage out of range\n");
        return FALSE;
    }

    return TRUE;
}

BOOL ms_verify_vector_range(const int_vec3_ms_bitmap* ms_bitmap, size_t v) {
    if (v > ms_bitmap->Nx->v1 * ms_bitmap->Nx->v2 * ms_bitmap->Nx->v3) {
        printf("Vector out of range\n");
        return FALSE;
    }

    return TRUE;
}