#pragma once
#include "../VectorMath.h"
#include <stdint.h>
#include "../ContinuousSystem/Model_3D.h"
#include "../SymbolicController/SymbolicController.h"
#include "../SymbolicModel/SymbolicModel.h"
#include "../SymbolicController/SafetyController.h"
#include "../SymbolicController/ReachabilityController.h"
#include "../SymbolicController/AutomatonBasedController.h"

struct trajectory {
    float_vec3* points;
    size_t traj_size;
};

typedef struct trajectory trajectory;

trajectory* construct_trajectory_for_safety_controller(cont_sys f, static_symb_controller* h, float_vec3* w, float_vec3* x0, int s);

trajectory* construct_trajectory_for_reachability_controller(cont_sys f, static_symb_controller* h, float_vec3* w, float_vec3* x0, int_vec3_bitmap* Qa, int s);

trajectory* construct_trajectory_for_dynamic_controller(cont_sys f, dynamic_symb_controller* h, float_vec3* w, float_vec3* x0, int s);