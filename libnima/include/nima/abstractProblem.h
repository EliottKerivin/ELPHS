#ifndef NIMA_ABSTRACT_PROBLEM_H
#define NIMA_ABSTRACT_PROBLEM_H

/*!
  @file
  This file contains the mathematical formulation of a problem to be solved
  using this library
  @addtogroup nima
  @{
  @defgroup mathematical-formulation Mathematical formulation
  @{
*/

#include "nima/errors.h"
#include "nima/types.h"

//! Contains the mathematical formulation of a problem to be solved
/*!
  Contains the mathematical formulation of the problem
  @f[ \frac{\partial u}{\partial t}(x, t) = a(x, t) + b(x, t) u(x, t) + c(x, t)
  \frac{\partial u}{\partial x}(x, t) + d(x, t)
  \frac{\partial^2 u}{\partial x^2}. @f]
  @f[ u(x, 0) = f(x) @f]
  The domain must be a box, i.e. the space and time domains must both be closed
  intervals.
*/
typedef struct NIMA_ABSTRACT_PROBLEM_STRUCT NIMA_ABSTRACT_PROBLEM;

/*!
  @defgroup abstract-problem-management Lifetime management
  @{
*/

//! Constructs a new problem
/*! Constructs (allocates and populates) a new abstract problem, and points @p
  *problem to it (@p *problem must be a nullptr). The coefficents may be @p
  nullptr, in which case they will be taken to be equal to zero. The validity of
  the arguments is also checked. @p *problem will need to be freed using
  NIMAdeleteAbstractProblem().

  @param[out] problem Output pointer which will point to the newly allocated
  problem. The destination pointer must be zeroed prior.
  @param[in] a,b,c,d Coefficients of the differential equation. If @p nullptr,
  then the coefficent is taken to be zero.
  @param[in] leftBound,rightBound Spatial bounds of the problem.
  @param[in] startTime,endTime Temporal bounds of the problem
  @param[in] initialConditions Initial conditions of the problem. If @p nullptr,
  then it is taken to be equal to zero.

  @returns
  - NIMA_OK if successful
  - NIMA_INVALID_OUT if the output pointer is not valid
  - NIMA_INVALID_ARGUMENT if one of the arguments is invalid
  - NIMA_ALLOC_FAILED if the memory allocation failed
 */
NIMA_CODES NIMAnewAbstractProblem(NIMA_ABSTRACT_PROBLEM **problem,
                                  NIMA_PDE_COEFFICIENT a,
                                  NIMA_PDE_COEFFICIENT b,
                                  NIMA_PDE_COEFFICIENT c,
                                  NIMA_PDE_COEFFICIENT d,
                                  NIMA_SPACE leftBound,
                                  NIMA_SPACE rightBound,
                                  NIMA_TIME startTime,
                                  NIMA_TIME endTime,
                                  NIMA_INITIAL_CONDITIONS initialConditions);

//! Deletes an abstract problem allocated using NIMAnewAbstractProblem()
void NIMAdeleteAbstractProblem(NIMA_ABSTRACT_PROBLEM *problem);

//! @} abstract-problem-management

//! @} mathematical-formulation
//! @} nima

#endif
