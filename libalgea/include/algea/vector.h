#ifndef ALGEA_VECTOR_H
#define ALGEA_VECTOR_H

/*!
  @file
  Definition and methods for vectors
*/
// (could strictly speaking be 1D matrices but whatever this will do)

#include "algea/element.h"
#include "algea/errors.h"
#include <stddef.h>
#include <string.h>

typedef struct ALGEA_VECTOR_STRUCT {
  size_t dim;
  ALGEA_ELEMENT *x_;
} ALGEA_VECTOR;

ALGEA_CODES ALGEAnewVector(ALGEA_VECTOR **out, size_t dimension);
void ALGEAdeleteVector(ALGEA_VECTOR *vector);

static inline size_t ALGEAvdim(const ALGEA_VECTOR *vector) {
  return vector->dim;
}

static inline const ALGEA_ELEMENT *ALGEAcvat(const ALGEA_VECTOR *vector,
                                             size_t i) {
  ALGEA_CHECK_BOUNDS(vector->dim, 1, i, 0); // 1 and 0 are just placeholders
  return vector->x_ + i;
}

static inline ALGEA_ELEMENT *ALGEAvat(ALGEA_VECTOR *vector, size_t i) {
  ALGEA_CHECK_BOUNDS(vector->dim, 1, i, 0);
  return vector->x_ + i;
}

static inline void ALGEAvset(ALGEA_VECTOR *vector, ALGEA_ELEMENT val) {
  if (val == 0) {
    memset(vector->x_, 0, vector->dim * sizeof(ALGEA_ELEMENT));
    return;
  }
  for (size_t i = 0; i < vector->dim; ++i) vector->x_[i] = val;
}

bool ALGEAvequal(const ALGEA_VECTOR *u, const ALGEA_VECTOR *v);

#endif // ALGEA_VECTOR_H
