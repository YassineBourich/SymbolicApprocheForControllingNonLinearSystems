#pragma once

#include "SymbolicModel.h"
#include "../VectorMath.h"
#include "../ContinuousSystem/Model_3D.h"
#include "../ReachabilityAnalysis/Reachability.h"
#include <math.h>
#include <stdlib.h>
#include "../Discretization/KSI.h"
#include "../Discretization/SIGMA.h"
#include "../boolean.h"
#include "../BitMap/MultiStageBitMap.h"
#include "../SpecificationAutomata/ExampleSpecification_3D_0.h"

int_vec3_ms_bitmap ProductPre(const symb_model* m, int**** h1, const int_vec3_ms_bitmap* R);

BOOL exists_sigma_st_g_ksi_psi_sigma_is_pre(const symb_model* m, int**** h1, int_vec3 ksi, int psi, const int_vec3_ms_bitmap* R);

int_vec2 sigma_st_g_ksi_psi_sigma_is_pre(const symb_model* m, int**** h1, int_vec3 ksi, int psi, const int_vec3_ms_bitmap* R);