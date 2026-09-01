#include "FDProblem_internal.h"
#include "abstractProblem_internal.h"

#include "nima/errors.h"
#include "nima/types.h"

#include <stdckdint.h>
#include <stdlib.h>

NIMA_CODES NIMAnewFDProblem(NIMA_FDPROBLEM **problem,
                            NIMA_ABSTRACT_PROBLEM *abstractFormulation,
                            size_t gridPoints,
                            size_t timeSteps) {
  // check arguments
  if (!problem || *problem) return NIMA_INVALID_OUT;
  if (!abstractFormulation) return NIMA_INVALID_ARGUMENT;
  if (gridPoints < 2 || timeSteps < 1) return NIMA_INVALID_ARGUMENT;
  size_t gridBytes;
  if (ckd_mul(&gridBytes, gridPoints, sizeof(NIMA_VALUES))) {
    return NIMA_TOO_FINE;
  }
  // Make discretized problem
  // Allocate memory
  NIMA_FDPROBLEM *fdp;
  if (!(fdp = malloc(sizeof(NIMA_FDPROBLEM)))) return NIMA_ALLOC_FAILED;
  if (!(fdp->initialConditions = malloc(gridBytes))) {
    free(fdp);
    return NIMA_ALLOC_FAILED;
  }
  // Initialize everything
  fdp->problem = abstractFormulation;
  // -1 because of "théorème de la fourchette"
  fdp->spaceStep =
      (abstractFormulation->rightBound - abstractFormulation->leftBound) /
      (NIMA_SPACE)(gridPoints - 1);
  fdp->timeStep =
      (abstractFormulation->endTime - abstractFormulation->startTime) /
      (NIMA_TIME)timeSteps;
  NIMA_SPACE x = abstractFormulation->leftBound;
  for (size_t i = 0; i < gridPoints; ++i) {
    fdp->initialConditions[i] = abstractFormulation->initialConditions(x);
    x += fdp->spaceStep;
  }
  *problem = fdp;
  return NIMA_OK;
}

void NIMAdeleteFDProblem(NIMA_FDPROBLEM *problem) {
  free(problem->initialConditions);
  free(problem);
}
