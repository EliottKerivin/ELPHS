#include "nima/CrankNicolson.h"
#include "FDProblem_internal.h"
#include "nima/errors.h"
#include "nima/types.h"

#include <stdlib.h>

struct NIMA_CRANK_NICOLSON_STRUCT {
  const NIMA_FDPROBLEM *problem;
  NIMA_SPACE inverseSpaceStep;
  NIMA_SPACE inverseSpaceStepSquared;
  NIMA_TIME inverseTimeStep;
};

NIMA_CODES NIMAnewCrankNicolsonSolver(NIMA_CRANK_NICOLSON **solver,
                                      const NIMA_FDPROBLEM *fdProblem) {
  // check parameters
  if (!solver || *solver) return NIMA_INVALID_OUT;
  if (!fdProblem) return NIMA_INVALID_ARGUMENT;
  NIMA_CRANK_NICOLSON *s;
  if (!(s = malloc(sizeof(NIMA_CRANK_NICOLSON)))) return NIMA_ALLOC_FAILED;
  s->problem = fdProblem;
  s->inverseSpaceStep = 1 / getSpaceStep(fdProblem);
  s->inverseSpaceStepSquared = s->inverseSpaceStep * s->inverseSpaceStep;
  s->inverseTimeStep = fdProblem->timeStep;
  *solver = s;
  return NIMA_OK;
}

void NIMAdeleteCrankNicolsonSolver(NIMA_CRANK_NICOLSON *solver) {
  free(solver);
}
