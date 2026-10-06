#ifndef NIMA_FDPROBLEM_STRUCT_H
#define NIMA_FDPROBLEM_STRUCT_H

#include "nima/FDProblem.h"

#include "abstractProblem_internal.h"
#include "nima/abstractProblem.h"
#include "nima/types.h"

typedef struct NIMA_FDPROBLEM_STRUCT {
  NIMA_ABSTRACT_PROBLEM *problem;
  NIMA_SPACE spaceStep;
  NIMA_TIME timeStep;
  NIMA_VALUES *initialConditions;
} NIMA_FDPROBLEM;

// Accessors so that if I ever change the struct, it doesn't break everything.
// As they're inline it costs nothing and is future-proof

static inline NIMA_ABSTRACT_PROBLEM *getAbstractProblem(
    const NIMA_FDPROBLEM *fdProblem) {
  return fdProblem->problem;
}

static inline NIMA_SPACE getSpaceStep(const NIMA_FDPROBLEM *fdProblem) {
  return fdProblem->spaceStep;
}
static inline NIMA_TIME getTimeStep(const NIMA_FDPROBLEM *fdProblem) {
  return fdProblem->timeStep;
}

static inline NIMA_VALUES *getInitialConditions(
    const NIMA_FDPROBLEM *fdProblem) {
  return fdProblem->initialConditions;
}

#endif // NIMA_FDPROBLEM_STRUCT_H
