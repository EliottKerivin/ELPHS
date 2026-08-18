#include "algea/matrix.h"

#include <stdckdint.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
   NOTE: Everything here assumes that there can be no buffer overlap, i.e. no
   views, slices, etc. !!!
*/

ALGEA_MATRIX *ALGEAnewMatrix(size_t rows, size_t columns) {
  // compute the necessary memory for the array of coordinates, being careful of
  // overflow
  size_t size, width;
  if (ckd_mul(&size, rows, columns)) return nullptr;
  if (ckd_mul(&width, size, sizeof(ALGEA_ELEMENT))) return nullptr;
  // allocate memory for the matrix
  ALGEA_MATRIX *m;
  if (!(m = malloc(sizeof(ALGEA_MATRIX)))) return nullptr;
  m->rows = rows;
  m->columns = columns;
  // allocate memory for the array of coordinates
  if (!(m->x = malloc(width))) {
    // memory allocation failed, free previously allocated memory as well
    free(m);
    return nullptr;
  }
  return m;
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
  memset(m->x, val, m->rows * m->columns * sizeof(ALGEA_ELEMENT));
  return ALGEA_OK;
}

bool ALGEAmatrixEqual(const ALGEA_MATRIX *A, const ALGEA_MATRIX *B) {
  if (A->rows != B->rows || A->columns != B->columns) return false;
  size_t len = A->rows * A->columns;
  for (size_t i = 0; i < len; ++i)
    if (A->x[i] != B->x[i]) return false;
  return true;
}

ALGEA_CODES ALGEAmatrixMultiplyDistinctResult(ALGEA_MATRIX *restrict result,
                                              const ALGEA_MATRIX *restrict A,
                                              const ALGEA_MATRIX *restrict B) {
  // checks are done in the public function
  for (size_t i = 0; i < result->rows; ++i) {
    for (size_t j = 0; j < result->columns; ++j) {
      for (size_t k = 0; k < A->rows; ++k) {
        *ALGEAat(result, i, j) = *ALGEAat(A, i, k) * *ALGEAat(B, k, j);
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
  // all of its memory, so pointer checks are sufficient to very no overlap
  if (result != A && result != B) {
    ALGEAmatrixMultiplyDistinctResult(result, A, B);
    return ALGEA_OK;
  }
  // result overlaps with one of the inputs, a copy must be made
  ALGEA_MATRIX *tmp;
  ALGEA_CODES code;
  if (A == B) {
    if (!(tmp = ALGEAduplicateMatrix(A))) return ALGEA_ALLOC_FAILED;
    code = ALGEAmatrixMultiplyDistinctResult(result, tmp, tmp);
  } else if (result == A) {
    if (!(tmp = ALGEAduplicateMatrix(A))) return ALGEA_ALLOC_FAILED;
    code = ALGEAmatrixMultiplyDistinctResult(result, tmp, B);
  } else {
    if (!(tmp = ALGEAduplicateMatrix(B))) return ALGEA_ALLOC_FAILED;
    code = ALGEAmatrixMultiplyDistinctResult(result, A, tmp);
  }

  ALGEAdeleteMatrix(tmp);
  return code;
}
