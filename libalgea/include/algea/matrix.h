/*!
  @file
  This file defines the ALGEA_MATRIX type and assorted methods.
  @addtogroup ALGEA
  @{
*/

#ifndef ALGEA_MATRIX_H
#define ALGEA_MATRIX_H

#include "algea/element.h"
#include "algea/errors.h"

#include <stddef.h>

//! Matrix type containing size and coordinates
/*!
  Stores the matrix's size, as well as a one dimensional array of all its
  coordinates. They are stored in row-major order, matching C's convention.
  */
typedef struct {
  size_t rows;       /*!< Number of rows */
  size_t columns;    /*!< Number of columns */
  ALGEA_ELEMENT *x_; /*!< @private Array of elements */
} ALGEA_MATRIX;

//! Returns a newly allocated ALGEA_MATRIX
/*!
  Returns a dynamically allocated matrix which must be freed using
  ALGEAdeleteMatrix(). The coordinates are not zero initialized. Both dimensions
  must be greater than zero

  @p rows * @p columns * @p sizeof(ALGEA_ELEMENT) must be less than @p SIZE_MAX,
  else the allocation fails.

  @returns A pointer to a new ALGEA_MATRIX if successful, @p nullptr otherwise
*/
ALGEA_MATRIX *ALGEAnewMatrix(size_t rows, size_t columns);

//! Retuns a newly allocated matrix, where each element is zeroed
/*!
  It has the same behavior as ALGEAnewMatrix(), except that each element of the
  array is set to zero.
  @note Note that as it simply sets all the bytes of @p x to zero, the standard
  does not guarantee that it is zero (this however is true on all commonly used
  platforms, see <a
  href="https://en.cppreference.com/c/memory/calloc">calloc()</a>, Notes
  section).
*/
ALGEA_MATRIX *ALGEAnewZeroedMatrix(size_t rows, size_t columns);

//! Copies @p src into @p dest
/*!
  Copies @p src into @p dest, overwriting the contents of @p dest->x (but  not
  @p dest->rows or @p dest->columns).

  @returns
  - ALGEA_OK if successful
  - ALGEA_DIM_MISMATCH if @p dest is not the same shape as @p src
*/
ALGEA_CODES ALGEAcopyMatrix(ALGEA_MATRIX *dest, const ALGEA_MATRIX *src);
//! Duplicates the argument
/*!
  Duplicates @p m by allocating a new ALGEA_MATRIX which will need to be
  freed using ALGEAdeleteMatrix()

  @returns A pointer to a new ALGEA_MATRIX if successful, @p nullptr otherwise
*/
ALGEA_MATRIX *ALGEAduplicateMatrix(const ALGEA_MATRIX *src);

//! Deletes an ALGEA_MATRIX allocated with ALGEAnewMatrix()
void ALGEAdeleteMatrix(ALGEA_MATRIX *m);

//! Sets all the value of @p m to @p val
/*!
  @note Note that as it simply sets all the bytes of @p x to zero, the standard
  does not guarantee that it is zero (this however is true on all commonly used
  platforms, see <a
  href="https://en.cppreference.com/c/memory/calloc">calloc()</a>, Notes
  section).

  @returns ALGEA_OK
*/
ALGEA_CODES ALGEAsetMatrix(ALGEA_MATRIX *m, ALGEA_ELEMENT val);

//! Retrieves a value from an ALGEA_MATRIX
/*!
  This function is only used to access a value. To change it, use ALGEAset()
  @returns The element requested
*/
static inline ALGEA_ELEMENT ALGEAat(
    const ALGEA_MATRIX *m /*!< ALGEA_MATRIX to be accessed */,
    size_t i /*!< Row number */,
    size_t j /*!< Column number */) {
  return m->x_[m->columns * i + j];
}

//! Changes the value of the element to @p val
/*!
  @return ALGEA_OK
*/
static inline ALGEA_CODES ALGEAset(
    ALGEA_MATRIX *m /*!< ALGEA_MATRIX to be accessed */,
    size_t i /*!< Row number */,
    size_t j /*! Column number */,
    ALGEA_ELEMENT val /*!< New value */) {
  m->x_[m->columns * i + j] = val;
  return ALGEA_OK;
}

//! Verifies if two ALGEA_MATRIX are numerically equal
/*!
  Compares the two matrices two check if they have the same dimensions and the
  same coefficients

  @returns @p true if the two are equal, @p false otherwise
  */
bool ALGEAmatrixEqual(const ALGEA_MATRIX *A, const ALGEA_MATRIX *B);

//! Performs ALGEA_MATRIX multiplication
/*!
  Performs ALGEA_MATRIX multiplication, overwriting the contents of @p result
  (but not its shape). @p result may point to the same matrix as @p A or @p B.

  @returns
  - ALGEA_OK if the multiplication is successful
  - ALGEA_DIM_MISMATCH if the operands or result aren't compatible
  - ALGEA_ALLOC_FAILED if internal memory allocations failed
*/
ALGEA_CODES ALGEAmatrixMultiply(
    ALGEA_MATRIX *result /*!< ALGEA_MATRIX to store the result */,
    const ALGEA_MATRIX *A /*!< Left hand ALGEA_MATRIX */,
    const ALGEA_MATRIX *B /*!< Right hand ALGEA_MATRIX */);

#endif
/*! @} */
