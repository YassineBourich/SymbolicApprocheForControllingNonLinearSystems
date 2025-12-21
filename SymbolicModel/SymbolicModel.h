#pragma once
#include "VectorMath.h"
#include "ContinuousSystem/Model_3D.h"
#include "ReachabilityAnalysis/Reachability.h"
#include <math.h>
#include <stdlib.h>
#include "Discretization/KSI.h"
#include "Discretization/SIGMA.h"
#include "boolean.h"
#include "BitMap/BitMap.h"

#define NX_1 100
#define NX_2 100
#define NX_3 30
#define NU_1 3
#define NU_2 5

extern float_vec3 x_min;
extern float_vec3 x_max;
extern float_vec2 u_min;
extern float_vec2 u_max;
extern float_vec3 w_min;
extern float_vec3 w_max;

extern int_vec3 Nx;
extern int_vec2 Nu;

matrix3 Jacx(float_vec2 u);
matrix3 Jacw(float_vec2 u);

typedef struct {
    int_vec3_pair q_min_max;
    short includes_0;
} model_node;


typedef struct {
    model_node model[NX_1][NX_2][NX_3][NU_1][NU_2];
} symb_model;

symb_model* construct_symbolic_model(short reachability_method);

model_node g(const int_vec3 ksi, const int_vec2 sigma);

int_vec3_bitmap Pre(int_vec3_bitmap* R);