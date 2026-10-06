#include "algea/vector.h"
#include "algea/element.h"
#include "algea/errors.h"

#include <stdckdint.h>
#include <stdlib.h>

ALGEA_CODES ALGEAnewVector(ALGEA_VECTOR **out, size_t dimension) {
  if (!out || *out) return ALGEA_INVALID_OUT;
  size_t bytes;
  if (ckd_mul(&bytes, dimension, sizeof(ALGEA_ELEMENT))) return ALGEA_OVERFLOW;
  ALGEA_VECTOR *v;
  if (!(v = malloc(sizeof(ALGEA_VECTOR)))) return ALGEA_ALLOC_FAILED;
  if (!(v->x_ = malloc(bytes))) {
    free(v);
    return ALGEA_ALLOC_FAILED;
  }
  v->dim = dimension;
  *out = v;
  return ALGEA_OK;
}

void ALGEAdeleteVector(ALGEA_VECTOR *vector) {
  if (!vector) return;
  free(vector->x_);
  free(vector);
}

bool ALGEAvequal(const ALGEA_VECTOR *u, const ALGEA_VECTOR *v) {
  if (ALGEAvdim(u) != ALGEAvdim(v)) return false;
  size_t n = ALGEAvdim(u);
  for (size_t i = 0; i < n; ++i) {
    if (u->x_[i] != v->x_[i]) return false;
  }
  return true;
}
