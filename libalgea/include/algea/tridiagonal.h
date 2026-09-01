#ifndef ALGEA_TRIDIAGONAL_H
#define ALGEA_TRIDIAGONAL_H

/*!
  @file
  This file defines the necessary types and routines to use tridiagonal matrices
  @addtogroup ALGEA
  @{
  @defgroup algea-tri Triadiagonal matrices
  @{
*/

#include "algea/element.h"
#include "algea/errors.h"

#include <stddef.h>

typedef struct ALGEA_TRIDIAGONAL_STRUCT {
  size_t rows;
  size_t columns;
  ALGEA_ELEMENT *upper_;
  ALGEA_ELEMENT *middle_;
  ALGEA_ELEMENT *lower_;
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

//! Accesses the element at row @p i and column @p j
/*!
  Accesses the element at row @p i and column @p j (0-indexed). If
  ALGEA_NO_BOUNDS_CHECKING is not defined, then bounds checking is performed.
  @param[in] tri Matrix to be accessed
  @param[in] i Row number
  @param[in] j Column number

  @returns The requested element, or @p NaN in case of overflow
*/
static inline ALGEA_ELEMENT ALGEAtat(ALGEA_TRIDIAGONAL *tri,
                                     size_t i,
                                     size_t j) {
  ALGEA_CHECK_BOUNDS(tri->rows, tri->columns, i, j);
  if (i + 1 == j) return tri->upper_[j];
  if (i == j) return tri->middle_[i];
  if (i == j + 1) return tri->lower_[j];
  // off diagonal
  return 0;
}

//! @} algea-tri-accessors

//! @} algea-tri
//! @} algea

#endif // ALGEA_TRIDIAGONAL_H
