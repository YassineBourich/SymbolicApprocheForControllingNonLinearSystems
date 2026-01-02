#pragma once
#include "../SymbolicModel/SymbolicModel.h"
#include "../VectorMath.h"
#include "../BitMap/BitMap.h"
#include "SymbolicController.h"
#include "../BitMap/BitMapList.h"
#include "../Discretization/KSI.h"

int_vec3_bitmap_list getReachabilityDomain(const symb_model* m, int_vec3_bitmap* Qa);
static_symb_controller* construct_reachability_symbolic_controller(const symb_model* m, int_vec3_bitmap* Qa);
BOOL is_reachability_achieved(int_vec3_bitmap* Qa, float_vec3 x);