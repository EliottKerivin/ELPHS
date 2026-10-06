#ifndef ALGEA_TRIDIAGONAL_H
#define ALGEA_TRIDIAGONAL_H

// NEEDS WORK! INDEED, DOESN'T REALLY SUPPORT NON SQUARE MATRICES, WHICH SHOULD
// BE FIXED! Namely, consider 3x5 and 5x3 to notice the diagonal sizes!

/*!
  @file
  This file defines the necessary types and routines to use tridiagonal matrices
  Maybe make upper/middle/lower easier to access, e.g. with a macro UPPER(i) ->
  i, i+1?
  @addtogroup ALGEA
  @{
  @defgroup algea-tri Triadiagonal matrices
  @{
*/

#include "algea/element.h"
#include "algea/errors.h"
#include "algea/vector.h"

typedef struct ALGEA_VECTOR_STRUCT ALGEA_VECTOR;

#include <stddef.h>

typedef struct ALGEA_TRIDIAGONAL_STRUCT {
  size_t rows;
  size_t columns;
  ALGEA_ELEMENT *upper_;
  ALGEA_ELEMENT *middle_;
  ALGEA_ELEMENT *lower_;
  ALGEA_ELEMENT scratch_, constScratch_;
} ALGEA_TRIDIAGONAL;

/*!
  @defgroup algea-tri-management Lifetime management
  @{
*/

//! Allocated a new triadiagonal matrix
/*!
  @param[out] tri Pointer to point to the new matrix, must have been zeroed
  previously
  @param[in] rows Number of rows of the new matrix, must be greater or equal to
  1
  @param[in] columns Number of columns of the new matrix, must be greater or
  equal to 1

  @returns
  - ALGEA_OK if successful
  - ALGEA_ALLOC_FAILED if the allocation failed
  - ALGEA_INVALID_OUT if the output parameter does not satisfy the conditions
  - ALGEA_INVALID_ARGUMENT if the arguments aren't valid
*/
ALGEA_CODES ALGEAnewTridiagonal(ALGEA_TRIDIAGONAL **tri,
                                size_t rows,
                                size_t columns);

void ALGEAdeleteTridiagonal(ALGEA_TRIDIAGONAL *tri);

//! @} algea-tri-management

/*!
  @defgroup algea-tri-accessors Accessors
  @{
*/

static inline size_t ALGEAtrows(const ALGEA_TRIDIAGONAL *tri) {
  return tri->rows;
}
static inline size_t ALGEAtcolumns(const ALGEA_TRIDIAGONAL *tri) {
  return tri->columns;
}

//! Accesses the element at row @p i and column @p j
/*!
  Accesses the element at row @p i and column @p j (0-indexed). If
  ALGEA_NO_BOUNDS_CHECKING is not defined, then bounds checking is performed.
  @param[in] tri Matrix to be accessed
  @param[in] i Row number
  @param[in] j Column number

  @returns The requested element, or @p NaN in case of overflow
*/
static inline const ALGEA_ELEMENT *ALGEActat(const ALGEA_TRIDIAGONAL *tri,
                                             size_t i,
                                             size_t j) {
  ALGEA_CHECK_BOUNDS(tri->rows, tri->columns, i, j);
  if (j >= 1 && i == j - 1) return tri->upper_ + i;
  if (i == j) return tri->middle_ + i;
  if (i >= 1 && i - 1 == j) return tri->lower_ + j;
  // off diagonal
  return &(tri->constScratch_);
}

//! Returns a modifiable lvalue to the requested element
/*!
  Returns a modifiable lvalue. However, if the value is off of the three
  diagonals, assigning is a no-op.
  */
static inline ALGEA_ELEMENT *ALGEAtat(ALGEA_TRIDIAGONAL *tri,
                                      size_t i,
                                      size_t j) {
  ALGEA_CHECK_BOUNDS(tri->rows, tri->columns, i, j);
  if (j >= 1 && i == j - 1) return tri->upper_ + i;
  if (i == j) return tri->middle_ + i;
  if (i >= 1 && i - 1 == j) return tri->lower_ + j;
  // off diagonal
  return &(tri->scratch_);
}

//! @} algea-tri-accessors

/*!
  @defgroup Equation solving
  @{
*/

//! Solves a tridiagonal system using the Thomas algorithm
/*!
  Solves the tridiagonal system of equations  @f$ A\vec x = \vec b @f$ (@f$ A
  @f$ tridiagonal) using the Thomas algorithm. It does not check that the
  conditions for the algorithm hold [probably in another function in the future
  or something]
  @sa <a
  href="https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm">Thomas
  algorithm</a>

  @param[out] sol The vector which will contain the solution. It must have been
  allocated previously and be of the right size. It may not overlap with @p b
  @param[in] A The matrix representing the system to be solved
  @param[in] b The right hand side vector

  @returns
  - ALGEA_OK if successful
  - ALGEA_INVALID_ARGUMENT if any of the dimensions do not match
  - ALGEA_ALLOC_FAILED if an internal allocation fails
*/

ALGEA_CODES ALGEAtriThomas(ALGEA_VECTOR *x,
                           const ALGEA_TRIDIAGONAL *A,
                           const ALGEA_VECTOR *b);

//! @} algea-tri
//! @} algea

#endif // ALGEA_TRIDIAGONAL_H
