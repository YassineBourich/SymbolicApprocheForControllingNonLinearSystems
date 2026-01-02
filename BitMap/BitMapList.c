#include "BitMapList.h"

int_vec3_bitmap_list bitmap_list_create_empty() {
    int_vec3_bitmap_list bitmap_list;
    bitmap_list.capacity = 10;
    bitmap_list.size = 0;
    bitmap_list.list = (int_vec3_bitmap*)malloc(bitmap_list.capacity * sizeof(int_vec3_bitmap));

    return bitmap_list;
}

BOOL bitmap_list_add_bitmap(int_vec3_bitmap_list* bitmap_list, int_vec3_bitmap bitmap) {
    if (bitmap_list == NULL) return FALSE;

    if (bitmap_list->size >= bitmap_list->capacity) {
        if (!bitmap_increase_capacity(bitmap_list)) {
            return FALSE;
        }
    }

    bitmap_list->list[bitmap_list->size++] = bitmap;
    return TRUE;
}

BOOL bitmap_list_remove_bitmap(int_vec3_bitmap_list* bitmap_list, int_vec3_bitmap bitmap) {

}

BOOL bitmap_list_remove_idx_bitmap(int_vec3_bitmap_list* bitmap_list, size_t i) {
    if (i < 0 || i >= bitmap_list->size) {
        printf("Index out of range\n");
        return FALSE;
    }

    for (size_t j = i; j < bitmap_list->size - 1; j++) {
        bitmap_list->list[j] = bitmap_list->list[j + 1];
    }

    bitmap_list->size--;
    return TRUE;
}

BOOL bitmap_list_is_empty(int_vec3_bitmap_list* bitmap_list) {
    return bitmap_list->size == 0;
}

BOOL bitmap_list_contains_bitmap(int_vec3_bitmap_list* bitmap_list, int_vec3_bitmap* bitmap) {
    return bitmap_list_index_of_bitmap(bitmap_list, bitmap) >= 0;
}

long long bitmap_list_index_of_bitmap(int_vec3_bitmap_list* bitmap_list, int_vec3_bitmap* bitmap) {
    for (size_t i = 0; i < bitmap_list->size; i++) {
        if (bitmap_equal(&bitmap_list->list[i], bitmap)) {
            return i;
        }
    }

    return -1;
}

BOOL bitmap_increase_capacity(int_vec3_bitmap_list* bitmap_list) {
    int new_capacity = bitmap_list->capacity * 1.5;

    int_vec3_bitmap* new_list = (int_vec3_bitmap*)malloc(sizeof(int_vec3_bitmap) * new_capacity);
    if (new_list == NULL) {
        return FALSE;
    }

    for (size_t i = 0; i < bitmap_list->size; i++) {
        new_list[i] = bitmap_list->list[i];
    }

    free(bitmap_list->list);

    bitmap_list->capacity = new_capacity;
    bitmap_list->list = new_list;
    return TRUE;
}

void bitmap_list_free(int_vec3_bitmap_list* bitmap_list) {
    free(bitmap_list->list);
}

void bitmap_list_free_with_content(int_vec3_bitmap_list* bitmap_list) {
    for (size_t i = 0; i < bitmap_list->size; i++) {
        bitmap_free(&bitmap_list->list[i]);
    }

    bitmap_list_free(bitmap_list);
}
