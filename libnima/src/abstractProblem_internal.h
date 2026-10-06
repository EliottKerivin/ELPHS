#ifndef NIMA_ABSTRACT_PROBLEM_STRUCT_H
#define NIMA_ABSTRACT_PROBLEM_STRUCT_H

// So that internal implementation files can see the actual layout

#include "nima/abstractProblem.h"

#include "nima/types.h"

typedef struct NIMA_ABSTRACT_PROBLEM_STRUCT {
  NIMA_PDE_COEFFICIENT a; //!< First coefficent
  NIMA_PDE_COEFFICIENT b; //!<  Second coefficient
  NIMA_PDE_COEFFICIENT c; //!<  Third coefficent
  NIMA_PDE_COEFFICIENT d; //!<  Fourth coefficent
  NIMA_SPACE leftBound;   //!<  Left bound of the spatial interval
  NIMA_SPACE rightBound;  //!<  Right bound of the spatial interval
  NIMA_TIME startTime;    //!<  Beginning of the time interval
  NIMA_TIME endTime;      //!<  End time of the time interval
  NIMA_INITIAL_CONDITIONS
  initialFunction; //!< Initial conditions of the problem
} NIMA_ABSTRACT_PROBLEM;

// Accessors so that if I ever change the struct, it doesn't break everything.
// As they're inline it costs nothing and is future-proof

static inline NIMA_PDE_COEFFICIENT getA(const NIMA_ABSTRACT_PROBLEM *problem) {
  return problem->a;
}
static inline NIMA_PDE_COEFFICIENT getB(const NIMA_ABSTRACT_PROBLEM *problem) {
  return problem->b;
}
static inline NIMA_PDE_COEFFICIENT getC(const NIMA_ABSTRACT_PROBLEM *problem) {
  return problem->c;
}
static inline NIMA_PDE_COEFFICIENT getD(const NIMA_ABSTRACT_PROBLEM *problem) {
  return problem->d;
}

static inline NIMA_SPACE getLeftBound(const NIMA_ABSTRACT_PROBLEM *problem) {
  return problem->leftBound;
}
static inline NIMA_SPACE getRightBound(const NIMA_ABSTRACT_PROBLEM *problem) {

  return problem->rightBound;
}

static inline NIMA_TIME getStartTime(const NIMA_ABSTRACT_PROBLEM *problem) {
  return problem->startTime;
}
static inline NIMA_TIME getEndTime(const NIMA_ABSTRACT_PROBLEM *problem) {
  return problem->endTime;
}

static inline NIMA_INITIAL_CONDITIONS getInitialFunction(
    const NIMA_ABSTRACT_PROBLEM *problem) {
  return problem->initialFunction;
}

#endif // NIMA_ABSTRACT_PROBLEM_STRUCT_H
