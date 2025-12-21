#pragma once
#include "SymbolicModel/SymbolicModel.h"
#include "VectorMath.h"
#include "BitMap/BitMap.h"
#include "SymbolicController.h"

int_vec3* getSafetyDomain(int_vec3_bitmap* Qs);
static_symb_controller construct_safety_symbolic_controller();