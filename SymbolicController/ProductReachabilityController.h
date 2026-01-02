#pragma once
#include "../SymbolicModel/SymbolicModel.h"
#include "../SymbolicModel/ProductSymbolicModel.h"
#include "../VectorMath.h"
#include "../BitMap/MultiStageBitMap.h"
#include "SymbolicController.h"
#include "../BitMap/MSBitMapList.h"
#include "../Discretization/KSI.h"

int_vec3_ms_bitmap_list getProductReachabilityDomain(const symb_model* m, int**** h1, int_vec3_ms_bitmap* Qa);
void print_bitmap(int_vec3_ms_bitmap* a);
product_symb_controller* construct_product_reachability_symbolic_controller(const symb_model* m, int**** h1, int_vec3_ms_bitmap* Qa);