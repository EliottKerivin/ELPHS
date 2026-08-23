#include "algea/matrix.h"

#include <stdckdint.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
   NOTE: Everything here assumes that there can be no buffer overlap, i.e. no
   views, slices, etc. !!!
*/

/*! Allocates a new matrix using allocator(), checking for size overflow.
  Only works with allocators that use free(). Otherwise, it'd become
  necessary to store the appropriate memory freeing function in ALGEA_MATRIX */
static ALGEA_MATRIX *allocateMatrix(size_t rows,
                                    size_t columns,
                                    void *(*allocator)(size_t)) {
  if (rows == 0 || columns == 0) return nullptr;
  // compute the necessary memory for the array of coordinates, being careful of
  // overflow
  size_t numberElements, bytes;
  if (ckd_mul(&numberElements, rows, columns)) return nullptr;
  if (ckd_mul(&bytes, numberElements, sizeof(ALGEA_ELEMENT))) return nullptr;
  // allocate memory for the matrix
  ALGEA_MATRIX *m;
  if (!(m = allocator(sizeof(ALGEA_MATRIX)))) return nullptr;
  m->rows = rows;
  m->columns = columns;
  // allocate memory for the array of coordinates
  if (!(m->x = allocator(bytes))) {
    // memory allocation failed, free previously allocated memory as well
    free(m);
    return nullptr;
  }
  return m;
}

ALGEA_MATRIX *ALGEAnewMatrix(size_t rows, size_t columns) {
  return allocateMatrix(rows, columns, malloc);
}

// makes calloc()'s signature compatible with ALGEAallocateMatrix()
static inline void *singleArgumentCalloc(size_t size) {
  return calloc(1, size);
}

ALGEA_MATRIX *ALGEAnewZeroedMatrix(size_t rows, size_t columns) {
  return allocateMatrix(rows, columns, singleArgumentCalloc);
}

ALGEA_CODES ALGEAcopyMatrix(ALGEA_MATRIX *dest, const ALGEA_MATRIX *src) {
  if (dest->rows != src->rows || dest->columns != src->columns)
    return ALGEA_DIM_MISMATCH;
  memcpy(dest->x, src->x, src->rows * src->columns * sizeof(ALGEA_ELEMENT));
  return ALGEA_OK;
}

ALGEA_MATRIX *ALGEAduplicateMatrix(const ALGEA_MATRIX *src) {
  ALGEA_MATRIX *new;
  if (!(new = ALGEAnewMatrix(src->rows, src->columns))) return nullptr;
  // Can't fail as dimensions are guaranteed to be the same
  (void)ALGEAcopyMatrix(new, src);
  return new;
}

void ALGEAdeleteMatrix(ALGEA_MATRIX *m) {
  free(m->x);
  free(m);
}

ALGEA_CODES ALGEAsetMatrix(ALGEA_MATRIX *m, ALGEA_ELEMENT val) {
  // As memset() takes an unsigned char as an argument, it only works in the
  // case where val is zero, else we simply manually set each element. In any
  // case, zeroing is probably the most common operation, so that's good
  // (assuming IEEE 754, see header comment)
  if (val == 0) {
    memset(m->x, 0, m->rows * m->columns * sizeof(ALGEA_ELEMENT));
  } else {
    size_t len = m->rows * m->columns;
    for (size_t i = 0; i < len; ++i) m->x[i] = val;
  }
  return ALGEA_OK;
}

bool ALGEAmatrixEqual(const ALGEA_MATRIX *A, const ALGEA_MATRIX *B) {
  if (A->rows != B->rows || A->columns != B->columns) return false;
  size_t len = A->rows * A->columns;
  for (size_t i = 0; i < len; ++i)
    if (A->x[i] != B->x[i]) return false;
  return true;
}

static ALGEA_CODES matrixMultiplyDistinctResult(
    ALGEA_MATRIX *restrict result,
    const ALGEA_MATRIX *restrict A,
    const ALGEA_MATRIX *restrict B) {
  // checks are done in the public function, however zeroing result is done here
  // to guarantee accumulation is correct due to the loop order
  ALGEA_CODES code;
  if ((code = ALGEAsetMatrix(result, 0))) return code;
  for (size_t i = 0; i < result->rows; ++i) {
    for (size_t k = 0; k < A->columns; ++k) {
      for (size_t j = 0; j < result->columns; ++j) {
        *ALGEAat(result, i, j) += *ALGEAat(A, i, k) * *ALGEAat(B, k, j);
      }
    }
  }
  return ALGEA_OK;
}

ALGEA_CODES ALGEAmatrixMultiply(ALGEA_MATRIX *result,
                                const ALGEA_MATRIX *A,
                                const ALGEA_MATRIX *B) {
  if (result->rows != A->rows || result->columns != B->columns ||
      A->columns != B->rows)
    return ALGEA_DIM_MISMATCH;

  // We assume that there can be no memory overlap, i.e. each ALGEAMatrix owns
  // all of its memory, so pointer checks are sufficient to verify no overlap
  if (result != A && result != B) {
    matrixMultiplyDistinctResult(result, A, B);
    return ALGEA_OK;
  }
  // result overlaps with one of the inputs, a copy must be made
  ALGEA_MATRIX *tmp;
  ALGEA_CODES code;
  if (A == B) {
    if (!(tmp = ALGEAduplicateMatrix(A))) return ALGEA_ALLOC_FAILED;
    code = matrixMultiplyDistinctResult(result, tmp, tmp);
  } else if (result == A) {
    if (!(tmp = ALGEAduplicateMatrix(A))) return ALGEA_ALLOC_FAILED;
    code = matrixMultiplyDistinctResult(result, tmp, B);
  } else {
    if (!(tmp = ALGEAduplicateMatrix(B))) return ALGEA_ALLOC_FAILED;
    code = matrixMultiplyDistinctResult(result, A, tmp);
  }

  ALGEAdeleteMatrix(tmp);
  return code;
}
