#pragma once
#include "../VectorMath.h"
#include "../Discretization/KSI.h"
#include "../SymbolicModel/SymbolicModel.h"
#include "Regions.h"

extern int Q;      // Number of states
extern int SIGMA;
extern int q0;
extern int F_size;
extern int F[];
extern regions Regions;

extern const char* colors[];
extern float rectangls[][2][3];

int delta(int q, int s);

int l(int_vec3 ksi);