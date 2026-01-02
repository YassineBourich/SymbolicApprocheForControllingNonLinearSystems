#pragma once

#include "ProductReachabilityController.h"
#include "../SymbolicModel/SymbolicModel.h"
#include "../SymbolicModel/ProductSymbolicModel.h"
#include "SymbolicController.h"
#include "../SpecificationAutomata/ExampleSpecification_3D_0.h"

int_vec3_ms_bitmap create_bitmap_with_final_product_states();
dynamic_symb_controller* construct_dynamic_symbolic_controller(symb_model* m);
BOOL is_specification_achieved(int psi);
void dynamic_symb_controller_free(dynamic_symb_controller* h);