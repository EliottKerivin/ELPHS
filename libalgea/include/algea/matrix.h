/*!
  @file
  This file defines the ALGEA_MATRIX type and assorted methods.
  @addtogroup ALGEA
  @{
*/
/*! @defgroup matrices Matrix algebra
  @{
*/

#ifndef ALGEA_MATRIX_H
#define ALGEA_MATRIX_H

#include <stddef.h>

//! All possible return codes from non-allocating functions
/*!
  All functions that do not return a newly allocated object return a code. If
  the return value is a newly allocated object, than an error is indicated with
  a return value of @p nullptr
*/
typedef enum {
  ALGEA_OK,           //!< Everything worked
  ALGEA_ERROR,        //!< A generic error has occured
  ALGEA_DIM_MISMATCH, //!< Some of the arguments had mismatched dimensions
  ALGEA_ALLOC_FAILED, //!< Couldn't allocate memory in the function
} ALGEA_CODES;

//! Type of an element of an ALGEA_MATRIX
typedef double ALGEA_ELEMENT;

//! Matrix type containing size and coordinates
/*!
  Stores the matrix's size, as well as a one dimensional array of all its
  coordinates. They are stored in row-major order, matching C's convention.
  */
typedef struct {
  size_t rows;      /*!< Number of rows */
  size_t columns;   /*!< Number of columns */
  ALGEA_ELEMENT *x; /*!< Array of elements */
} ALGEA_MATRIX;

//! Returns a newly allocated ALGEA_MATRIX
/*!
  Returns a dynamically allocated matrix which must be freed using
  ALGEAdeleteMatrix(). The coordinates are not zero initialized.

  @p rows * @p columns * @p sizeof(ALGEA_ELEMENT) must be less than @p SIZE_MAX,
  else the allocation fails.

  @returns A pointer to a new ALGEA_MATRIX if successful, @p nullptr otherwise
*/
ALGEA_MATRIX *ALGEAnewMatrix(size_t rows, size_t columns);

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
  @returns ALGEA_OK
*/
ALGEA_CODES ALGEAsetMatrix(ALGEA_MATRIX *m, ALGEA_ELEMENT val);

//! Retrieves a pointer to an ALGEA_ELEMENT from an ALGEA_MATRIX
/*!
  @returns Pointer to the element of @p m, i.e. of type ALGEA_ELEMENT *
*/
static inline ALGEA_ELEMENT *ALGEAat(
    const ALGEA_MATRIX *m /*!< ALGEA_MATRIX to be accessed */,
    size_t i /*!< Row number */,
    size_t j /*!< Column number */) {
  return m->x + m->columns * i + j;
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
  Performs ALGEA_MATRIX multiplication. @p result may point to the same
  matrix as @p A or @p B.

  @returns
  - ALGEA_OK if the multiplication is successful
  - ALGEA_DIM_MISMATCH if the operands aren't compatible
  -ALGEA_ALLOC_FAILED if internal memory allocations failed
*/
ALGEA_CODES ALGEAmatrixMultiply(
    ALGEA_MATRIX *result /*!< ALGEA_MATRIX to store the result */,
    const ALGEA_MATRIX *A /*!< Left hand ALGEA_MATRIX */,
    const ALGEA_MATRIX *B /*!< Right hand ALGEA_MATRIX */);

/*! @} */
/*! @} */

#endif
