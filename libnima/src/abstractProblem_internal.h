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
  initialConditions; //!< Initial conditions of the problem
} NIMA_ABSTRACT_PROBLEM;

#endif // NIMA_ABSTRACT_PROBLEM_STRUCT_H
