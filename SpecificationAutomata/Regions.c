#include "Regions.h"

regions* regions_create(const float rectangls[][2][3], const char** colors, size_t num_colors) {
    int rect_num = sizeof(rectangls) / sizeof(const float (*)[2][3]);
    if (rect_num != num_colors) return NULL;

    regions* R = malloc(sizeof(regions));

    R->colors = colors;
    R->Rectangls = (rect2*)malloc(num_colors * sizeof(rect2));
    float_vec2 r_min, r_max;
    for (size_t i = 0; i < num_colors; i++) {
        r_min = (float_vec2){rectangls[i][0][0],rectangls[i][0][1]};
        r_max = (float_vec2){rectangls[i][1][0],rectangls[i][1][1]};
        R->Rectangls[i] = (rect2){r_min, r_max};
    }
    
    R->size = num_colors;

    return R;
}