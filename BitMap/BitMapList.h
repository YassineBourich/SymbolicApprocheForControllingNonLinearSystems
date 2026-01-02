#pragma once

#include "BitMap.h"
#include "../boolean.h"
#include <stdint.h>
#include <stdlib.h>

struct int_vec3_bitmap_list {
    int_vec3_bitmap* list;
    size_t capacity;
    size_t size;
};

typedef struct int_vec3_bitmap_list int_vec3_bitmap_list;

int_vec3_bitmap_list bitmap_list_create_empty();

BOOL bitmap_list_add_bitmap(int_vec3_bitmap_list* bitmap_list, int_vec3_bitmap bitmap);
BOOL bitmap_list_remove_bitmap(int_vec3_bitmap_list* bitmap_list, int_vec3_bitmap bitmap);
BOOL bitmap_list_remove_idx_bitmap(int_vec3_bitmap_list* bitmap_list, size_t i);
BOOL bitmap_list_is_empty(int_vec3_bitmap_list* bitmap_list);
BOOL bitmap_list_contains_bitmap(int_vec3_bitmap_list* bitmap_list, int_vec3_bitmap* bitmap);
long long bitmap_list_index_of_bitmap(int_vec3_bitmap_list* bitmap_list, int_vec3_bitmap* bitmap);

BOOL bitmap_increase_capacity(int_vec3_bitmap_list* bitmap_list);

void bitmap_list_free(int_vec3_bitmap_list* bitmap_list);
void bitmap_list_free_with_content(int_vec3_bitmap_list* bitmap_list);