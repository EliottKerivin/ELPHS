#include "algea/tridiagonal.h"
#include "algea/element.h"
#include "algea/errors.h"
#include "algea/generic.h"
#include "algea/vector.h"

#include <stdckdint.h>
#include <stddef.h>
#include <stdlib.h>

void ALGEAdeleteTridiagonal(ALGEA_TRIDIAGONAL *tri) {
  if (!tri) return;
  free(tri->upper_);
  free(tri->middle_);
  free(tri->lower_);
  free(tri);
}

ALGEA_CODES ALGEAnewTridiagonal(ALGEA_TRIDIAGONAL **tri,
                                size_t rows,
                                size_t columns) {
  // check arguments
  if (!tri || *tri) return ALGEA_INVALID_OUT;
  if (!rows || !columns) return ALGEA_INVALID_ARGUMENT;

  // compute array sizes
  size_t upperTerms;
  size_t middleTerms;
  size_t lowerTerms;
  if (rows < columns) {
    upperTerms = rows;
    middleTerms = rows;
    lowerTerms = rows - 1;
  } else if (rows > columns) {
    upperTerms = columns - 1;
    middleTerms = columns;
    lowerTerms = columns;
  } else {
    upperTerms = rows - 1;
    middleTerms = rows;
    lowerTerms = rows - 1;
  }

  size_t upperBytes;
  if (ckd_mul(&upperBytes, upperTerms, sizeof(ALGEA_ELEMENT))) {
    return ALGEA_OVERFLOW;
  }
  size_t middleBytes;
  if (ckd_mul(&middleBytes, middleTerms, sizeof(ALGEA_ELEMENT))) {
    return ALGEA_OVERFLOW;
  }
  size_t lowerBytes;
  if (ckd_mul(&lowerBytes, lowerTerms, sizeof(ALGEA_ELEMENT))) {
    return ALGEA_OVERFLOW;
  }

  // allocate memory
  ALGEA_TRIDIAGONAL *t;
  if (!(t = malloc(sizeof(ALGEA_TRIDIAGONAL)))) return ALGEA_ALLOC_FAILED;
  if (!(t->upper_ = malloc(upperBytes))) {
    ALGEAdeleteTridiagonal(t);
    return ALGEA_ALLOC_FAILED;
  }
  if (!(t->middle_ = malloc(middleBytes))) {
    ALGEAdeleteTridiagonal(t);
    return ALGEA_ALLOC_FAILED;
  }
  if (!(t->lower_ = malloc(lowerBytes))) {
    ALGEAdeleteTridiagonal(t);
    return ALGEA_ALLOC_FAILED;
  }
  // set things
  t->rows = rows;
  t->columns = columns;
  t->scratch_ = 0;
  t->constScratch_ = 0;
  *tri = t;
  return ALGEA_OK;
}

// two helper functions, names taken conforming to the wikipedia article
static ALGEA_ELEMENT ci(const ALGEA_TRIDIAGONAL *A,
                        ALGEA_ELEMENT cprev,
                        size_t i) {
  return aat(A, i, i + 1) / (aat(A, i, i) - aat(A, i, i - 1) * cprev);
}
static ALGEA_ELEMENT di(const ALGEA_TRIDIAGONAL *A,
                        const ALGEA_VECTOR *b,
                        ALGEA_ELEMENT cprev,
                        ALGEA_ELEMENT dprev,
                        size_t i) {
  ALGEA_ELEMENT num = aat(b, i) - aat(A, i, i - 1) * dprev;
  ALGEA_ELEMENT den = aat(A, i, i) - aat(A, i, i - 1) * cprev;
  return num / den;
}

ALGEA_CODES ALGEAtriThomas(ALGEA_VECTOR *x,
                           const ALGEA_TRIDIAGONAL *A,
                           const ALGEA_VECTOR *b) {
  // argument checking
  if (ALGEAvdim(x) != ALGEAvdim(b) || ALGEAvdim(x) != ALGEAtrows(A)) {
    return ALGEA_INVALID_ARGUMENT;
  }
  // helper variable initialization
  size_t n = ALGEAvdim(x);
  // vector to benefit from bounds checking, no other purpose
  ALGEA_VECTOR *c = nullptr;
  ALGEA_VECTOR *d = nullptr;
  ALGEA_CODES code;
  if (!(code = ALGEAnewVector(&c, n - 1)) || !(code = ALGEAnewVector(&d, n))) {
    ALGEAdeleteVector(c); // freeing nullptr vector is fine
    return ALGEA_ALLOC_FAILED;
  }
  // actual solving
  aat(c, 0) = aat(A, 0, 1) / aat(A, 0, 0);
  aat(d, 0) = aat(b, 0) / aat(A, 0, 0);

  for (size_t i = 1; i < n - 1; ++i) {
    aat(c, i) = ci(A, aat(c, i - 1), i);
    aat(d, i) = di(A, b, aat(c, i - 1), aat(d, i - 1), i);
  }
  aat(d, n - 1) = di(A, b, aat(c, n - 2), aat(d, n - 2), n - 1);
  // back substitution
  aat(x, n - 1) = aat(d, n - 1);
  // we loop up then substract to avoid integer wrap around
  for (size_t i = 0; i < n - 2; ++i) {
    size_t j = n - 2 - i;
    aat(x, j) = aat(d, j) - aat(c, j) * aat(x, j + 1);
  }
  ALGEAdeleteVector(c);
  ALGEAdeleteVector(d);
  return ALGEA_OK;
}
