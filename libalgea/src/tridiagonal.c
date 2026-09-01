#include "algea/tridiagonal.h"
#include "algea/element.h"
#include "algea/errors.h"

#include <stdckdint.h>
#include <stddef.h>
#include <stdlib.h>

ALGEA_CODES ALGEAnewTridiagonal(ALGEA_TRIDIAGONAL **tri,
                                size_t rows,
                                size_t columns) {
  // check arguments
  if (!tri || *tri) return ALGEA_INVALID_OUT;
  if (!rows || !columns) return ALGEA_INVALID_ARGUMENT;
  // compute number of terms on main diagonal
  size_t middleTerms = rows < columns ? rows : columns;
  size_t middleBytes;
  if (ckd_mul(&middleBytes, middleTerms, sizeof(ALGEA_ELEMENT))) {
    return ALGEA_OVERFLOW;
  }
  // allocate memory
  ALGEA_TRIDIAGONAL *t;
  if (!(t = malloc(sizeof(ALGEA_TRIDIAGONAL)))) return ALGEA_ALLOC_FAILED;
  if (!(t->upper_ = malloc(middleBytes - sizeof(ALGEA_ELEMENT)))) {
    free(t);
    return ALGEA_ALLOC_FAILED;
  }
  if (!(t->middle_ = malloc(middleBytes))) {
    free(t->upper_);
    free(t);
    return ALGEA_ALLOC_FAILED;
  }
  if (!(t->lower_ = malloc(middleBytes - sizeof(ALGEA_ELEMENT)))) {
    free(t->upper_);
    free(t->lower_);
    free(t);
    return ALGEA_ALLOC_FAILED;
  }
  // set things
  t->rows = rows;
  t->columns = columns;
  *tri = t;
  return ALGEA_OK;
}

void ALGEAdeleteTridiagonal(ALGEA_TRIDIAGONAL *tri) {
  if (!tri) return;
  free(tri->upper_);
  free(tri->middle_);
  free(tri->lower_);
  free(tri);
}
