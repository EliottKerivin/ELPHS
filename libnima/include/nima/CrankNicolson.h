#ifndef NIMA_CRANK_NICOLSON_H
#define NIMA_CRANK_NICOLSON_H

/*!
  @file
  This file defines everything needed to use the Crank-Nicolson solver. The
  problem must have been created and discretized previously.
  @addtogroup nima
  @{
  @defgroup crank-nicolson Crank-Nicolson
  @{
*/

#include "nima/FDProblem.h"
#include "nima/errors.h"

typedef struct NIMA_CRANK_NICOLSON_STRUCT NIMA_CRANK_NICOLSON;

//! Allocates a new Crank-Nicolson solver
/*!
  @pre The problem must have already been discretized into a NIMA_FDPROBLEM, and
  this must outlive the solver as it only holds a constant reference to said
  discretized problem

  @param[out] solver Pointer which will point to the new solver, it must have
  been zeroed previously (<tt>*solver == nullptr</tt>)
  @param[in] fdProblem Pointer to the discretized problem to solve

  @returns
  - NIMA_OK if everything works
  - NIMA_INVALID_OUT if the output pointer doesn't satisfy the conditions
  - NIMA_INVALID_ARGUMENT if the problem isn't valid
*/
NIMA_CODES NIMAnewCrankNicolsonSolver(NIMA_CRANK_NICOLSON **solver,
                                      const NIMA_FDPROBLEM *fdProblem);

//! Deletes a solver allocated using NIMAnewCrankNicolsonSolver()
void NIMAdeleteCrankNicolsonSolver(NIMA_CRANK_NICOLSON *solver);

// @} crank-nicolson
// @} nima

#endif // NIMA_CRANK_NICOLSON_H
