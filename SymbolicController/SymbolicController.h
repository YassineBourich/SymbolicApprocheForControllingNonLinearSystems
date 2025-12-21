#include "VectorMath.h"
#include "SymbolicModel/SymbolicModel.h"

struct static_symb_controller {
    int_vec2 h[NX_1][NX_2][NX_3];
};

typedef struct static_symb_controller static_symb_controller;


struct dynamic_symb_controller {
    int_vec2* h1[NX_1][NX_2][NX_3];
    int_vec2* h2[NX_1][NX_2][NX_3];
};

typedef struct dynamic_symb_controller dynamic_symb_controller;