#ifndef NIMA_FDPROBLEM_STRUCT_H
#define NIMA_FDPROBLEM_STRUCT_H

#include "nima/FDProblem.h"

#include "abstractProblem_internal.h"
#include "nima/types.h"

typedef struct NIMA_FDPROBLEM_STRUCT {
  NIMA_ABSTRACT_PROBLEM *problem;
  NIMA_SPACE spaceStep;
  NIMA_TIME timeStep;
  NIMA_VALUES *initialConditions;
} NIMA_FDPROBLEM;

#endif // NIMA_FDPROBLEM_STRUCT_H
