#include "MultiStageBitMap.h"

/* Creation */
int_vec3_ms_bitmap ms_bitmap_create_empty(const int_vec3* Nx, int nstages) {
    int bitmap_size = Nx->v1 * Nx->v2 * Nx->v3;

    int_vec3_ms_bitmap ms_bitmap;

    bitmap_size = (bitmap_size + 7) / 8;

    ms_bitmap.nbytes = bitmap_size;
    ms_bitmap.nstages = nstages;
    ms_bitmap.n_ons = 0;
    ms_bitmap.Nx = Nx;

    ms_bitmap.data = (uint8_t**)malloc(nstages * sizeof(uint8_t*));

    for (int i = 0; i < nstages; i++)
        ms_bitmap.data[i] = calloc(bitmap_size, sizeof(uint8_t));

    return ms_bitmap;
}

int_vec3_ms_bitmap ms_bitmap_clone(const int_vec3_ms_bitmap* ms_bitmap) {
    int_vec3_ms_bitmap clone;
    clone.nstages = ms_bitmap->nstages;
    clone.nbytes = ms_bitmap->nbytes;
    clone.n_ons = ms_bitmap->n_ons;
    clone.Nx = ms_bitmap->Nx;

    clone.data = (uint8_t**)malloc(clone.nstages * sizeof(uint8_t*));

    for (int i = 0; i < clone.nstages; i++) {
        clone.data[i] = (uint8_t*)malloc(clone.nbytes * sizeof(uint8_t));
        memcpy(clone.data[i], ms_bitmap->data[i], clone.nbytes);
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
    ms_bitmap->nbytes = 0;
    ms_bitmap->n_ons = 0;
}

/* Queries */
BOOL ms_bitmap_is_empty(const int_vec3_ms_bitmap* ms_bitmap) {
    return ms_bitmap->n_ons == 0;
}

BOOL ms_bitmap_contains(const int_vec3_ms_bitmap* ms_bitmap, int_vec3 e, size_t stage) {
    if (verify_stage_range(ms_bitmap, stage)) {
        return FALSE;
    }

    return MS_BITMAP_GET(ms_bitmap->data, stage, indexToInteger(&e, ms_bitmap->Nx));
}

BOOL ms_bitmap_is_subset(const int_vec3_ms_bitmap* a, const int_vec3_ms_bitmap* b) {
    
}

/* Modification */
BOOL ms_bitmap_add(int_vec3_ms_bitmap* ms_bitmap, int_vec3 e, size_t stage) {
    if (verify_stage_range(ms_bitmap, stage)) {
        return FALSE;
    }

    MS_BITMAP_SET1(ms_bitmap->data, stage, indexToInteger(&e, ms_bitmap->Nx));
    return TRUE;
}

BOOL ms_bitmap_remove(int_vec3_ms_bitmap* ms_bitmap, int_vec3 e, size_t stage) {
    if (verify_stage_range(ms_bitmap, stage)) {
        return FALSE;
    }

    MS_BITMAP_SET0(ms_bitmap->data, stage, indexToInteger(&e, ms_bitmap->Nx));
    return TRUE;
}

/* Set operations */
int_vec3_ms_bitmap ms_bitmap_intersection(
    const int_vec3_ms_bitmap* a,
    const int_vec3_ms_bitmap* b
) {
    int_vec3_ms_bitmap ms_bitmap;
}

int_vec3_ms_bitmap ms_bitmap_union(
    const int_vec3_ms_bitmap* a,
    const int_vec3_ms_bitmap* b
) {

}


BOOL verify_stage_range(int_vec3_ms_bitmap* ms_bitmap, size_t stage) {
    if (stage >= ms_bitmap->nstages) {
        printf("Stage out of range\n");
        return FALSE;
    }

    return TRUE;
}

BOOL verify_vector_range(int_vec3_ms_bitmap* ms_bitmap, size_t v) {
    if (v >= ms_bitmap->nbytes * 8) {
        printf("Vector out of range\n");
        return FALSE;
    }

    return TRUE;
}