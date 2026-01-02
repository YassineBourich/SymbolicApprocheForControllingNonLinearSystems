#pragma once
#include "../SymbolicModel/SymbolicModel.h"
#include "../VectorMath.h"
#include "../BitMap/BitMap.h"
#include "SymbolicController.h"

int_vec3_bitmap getSafetyDomain(const symb_model* m, int_vec3_bitmap* Qs);
static_symb_controller* construct_safety_symbolic_controller(const symb_model* m, int_vec3_bitmap* Qs);