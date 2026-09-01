#ifndef NIMA_FDPROBLEM_H
#define NIMA_FDPROBLEM_H

/*! @file
  This file defines the necessary infrastructure to create a problem suitable to
  various finite difference methods (Euler, Crank-Nicolson, etc.).
  @addtogroup nima NIMA
  @{
  @defgroup fd Finite differences
  @{
*/

#include "nima/abstractProblem.h"
#include "nima/errors.h"

#include <stddef.h>

//! Structure holding the problem to be solved
/*!
  This structure holds the various parameters of the problem to be solved using
  a finite difference method: the coefficients of the problem, the boundary
  conditions, the grid size, etc.
*/
typedef struct NIMA_FDPROBLEM_STRUCT NIMA_FDPROBLEM;

/*!
  @defgroup nima-fd-management Lifetime management
  @{
*/

//! Allocates and populates a problem
/*!
  Allocates a new discretized problem, which will need to be freed using
  NIMAdeleteFDProblem.

  @pre @p abstractFormulation must both outlive the discretization, and be
  unmodified as no copy is made and a reference is simply stored

  @param[out] problem The new problem will be pointed to by @p *problem, which
  must have been zeroed previously
  @param[in] abstractFormulation Pointer to the abstract formulation of the
  problem. It must have been allocated previously and may not change for the
  lifetime of this discretization, as no copy is made
  @param[in] gridPoints Number of grid points, including the ends. Must be
  greater or equal to two
  @param[in] timeSteps Number of time steps to be taken, must be greater or
  equal to one

  @returns
  - NIMA_OK if successful
  - NIMA_INVALID_OUT if the output pointer is invalid
  - NIMA_TOO_FINE if the requested spatial resolution causes an integer overflow
  - NIMA_INVALID_ARGUMENT if one of the arguments is invalid
*/
NIMA_CODES NIMAnewFDProblem(NIMA_FDPROBLEM **problem,
                            NIMA_ABSTRACT_PROBLEM *abstractFormulation,
                            size_t gridPoints,
                            size_t timeSteps);

//! Deletes a problem
void NIMAdeleteFDProblem(NIMA_FDPROBLEM *problem);

//! @} nima-fd-management
//! @} finite difference
//! @} nima

#endif // NIMA_FDPROBLEM_H
