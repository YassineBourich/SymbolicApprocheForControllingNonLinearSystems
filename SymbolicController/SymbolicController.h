#pragma once

#include "../VectorMath.h"
#include "../SymbolicModel/SymbolicModel.h"
#include "../BitMap/MultiStageBitMap.h"

struct static_symb_controller {
    int_vec2 h[NX_1+1][NX_2+1][NX_3+1];
    int_vec3_arr R_star;
};

typedef struct static_symb_controller static_symb_controller;


struct product_symb_controller {
    int_vec2**** h;
    int_vec3_ms_bitmap R_star;
};

typedef struct product_symb_controller product_symb_controller;


struct dynamic_symb_controller {
    int**** h1;
    int_vec2**** h2;
    int_vec3_arr Q0;
};

typedef struct dynamic_symb_controller dynamic_symb_controller;