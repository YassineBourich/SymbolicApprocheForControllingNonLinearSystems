#include "SafetyController.h"

int_vec3* getSafetyDomain(int_vec3_bitmap* Qs) {
    int_vec3_bitmap Rk = NULL_VEC3_BITMAP;
    int_vec3_bitmap pre = NULL_VEC3_BITMAP;
    int_vec3_bitmap Rkp1 = bitmap_clone(Qs);
    do {
        bitmap_free(&Rk);
        Rk = Rkp1;
        pre = Pre(&Rk);
        Rkp1 = bitmap_intersection(&Rk, &pre);
        bitmap_free(&pre);
    } while (!bitmap_equal(&Rk, &Rkp1));

    bitmap_free(&Rkp1);
    int_vec3* R_star = bitmap_to_array(&Rk);
    bitmap_free(&Rk);

    return R_star;
}

static_symb_controller construct_safety_symbolic_controller() {
    
}