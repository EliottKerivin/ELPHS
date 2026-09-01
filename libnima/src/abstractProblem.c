#include "abstractProblem_internal.h"

#include "nima/errors.h"
#include "nima/types.h"

#include <stdlib.h>

// Two helper functions to avoid having to check for nullptr all the time
// Comments to make clang-tidy happy
static NIMA_VALUES zeroInitialCondition(NIMA_SPACE /* x */) { return 0; }
static NIMA_VALUES zeroCoefficient(NIMA_SPACE /* x */, NIMA_TIME /* t */) {
  return 0;
}

NIMA_CODES NIMAnewAbstractProblem(NIMA_ABSTRACT_PROBLEM **problem,
                                  NIMA_PDE_COEFFICIENT a,
                                  NIMA_PDE_COEFFICIENT b,
                                  NIMA_PDE_COEFFICIENT c,
                                  NIMA_PDE_COEFFICIENT d,
                                  NIMA_SPACE leftBound,
                                  NIMA_SPACE rightBound,
                                  NIMA_TIME startTime,
                                  NIMA_TIME endTime,
                                  NIMA_INITIAL_CONDITIONS initialConditions) {
  // check arguments (not worth a full function here)
  if (!problem || *problem) return NIMA_INVALID_OUT;
  if (leftBound >= rightBound || startTime >= endTime) {
    return NIMA_INVALID_ARGUMENT;
  }
  // Allocate problem
  NIMA_ABSTRACT_PROBLEM *p;
  if (!(p = malloc(sizeof(NIMA_ABSTRACT_PROBLEM)))) return NIMA_ALLOC_FAILED;
  // Populate problem
  p->a = a ? a : zeroCoefficient;
  p->b = b ? b : zeroCoefficient;
  p->c = c ? c : zeroCoefficient;
  p->d = d ? d : zeroCoefficient;
  p->leftBound = leftBound, p->rightBound = rightBound;
  p->startTime = startTime, p->endTime = endTime;
  p->initialConditions =
      initialConditions ? initialConditions : zeroInitialCondition;
  // Set out parameter
  *problem = p;
  return NIMA_OK;
}

void NIMAdeleteAbstractProblem(NIMA_ABSTRACT_PROBLEM *problem) {
  free(problem);
}
