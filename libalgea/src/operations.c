#include "algea/operations.h"
#include "algea/generic.h"
#include "algea/tridiagonal.h"
#include "algea/vector.h"

// For tridiagonal/vector multiplication, the two cases where the matrix is
// really "tall" or really "flat" need to be treated separately out smaller than
// v. Needs to be strict
static void ALGEAmultiplyFlatTV(ALGEA_VECTOR *out,
                                const struct ALGEA_TRIDIAGONAL_STRUCT *A,
                                const struct ALGEA_VECTOR_STRUCT *v) {
  size_t n = ALGEAvdim(out);
  // we know that it's at least 2x1, else it'd be square
  aat(out, 0) = aat(A, 0, 0) * aat(v, 0) + aat(A, 0, 1) * aat(v, 1);
  for (size_t i = 1; i < n; ++i) {
    aat(out, i) = aat(A, i, i - 1) * aat(v, i - 1) + aat(A, i, i) * aat(v, i) +
                  aat(A, i, i + 1) * aat(v, i + 1);
  }
}

static void ALGEAmultiplySquareTV(ALGEA_VECTOR *out,
                                  const struct ALGEA_TRIDIAGONAL_STRUCT *A,
                                  const struct ALGEA_VECTOR_STRUCT *v) {
  size_t n = ALGEAvdim(out);
  if (n == 1) {
    aat(out, 0) = aat(A, 0, 0) * aat(v, 0);
    return;
  }
  // n >= 2
  aat(out, 0) = aat(A, 0, 0) * aat(v, 0) + aat(A, 0, 1) * aat(v, 1);
  for (size_t i = 1; i < n - 1; ++i) {
    aat(out, i) = aat(A, i, i - 1) * aat(v, i - 1) + aat(A, i, i) * aat(v, i) +
                  aat(A, i, i + 1) * aat(v, i + 1);
  }
  aat(out, n - 1) = aat(A, n - 1, n - 2) * aat(v, n - 2) +
                    aat(A, n - 1, n - 1) * aat(v, n - 1);
}

static void ALGEAmultiplyTallTV(ALGEA_VECTOR *out,
                                const struct ALGEA_TRIDIAGONAL_STRUCT *A,
                                const struct ALGEA_VECTOR_STRUCT *v) {
  // we first set to zero as some, if not most, of the entries of out will be
  // zero
  ALGEAvset(out, 0);
  size_t m = ALGEAvdim(v);
  if (m == 1) {
    aat(out, 0) = aat(A, 0, 0) * aat(v, 0);
    return;
  }
  aat(out, 0) = aat(A, 0, 0) * aat(v, 0) + aat(A, 0, 1) * aat(v, 1);
  for (size_t i = 1; i < m - 1; ++i) {
    aat(out, i) = aat(A, i, i - 1) * aat(v, i - 1) + aat(A, i, i) * aat(v, i) +
                  aat(A, i, i + 1) * aat(v, i + 1);
  }
  aat(out, m - 1) = aat(A, m - 1, m - 2) * aat(v, m - 2) +
                    aat(A, m - 1, m - 1) * aat(v, m - 1);
  aat(out, m) = aat(A, m, m - 1) * aat(v, m - 1);
}

ALGEA_CODES ALGEAmultiplyTV(ALGEA_VECTOR *out,
                            const ALGEA_TRIDIAGONAL *A,
                            const ALGEA_VECTOR *v) {
  if (ALGEAvdim(out) != ALGEAtrows(A) || ALGEAtcolumns(A) != ALGEAvdim(v)) {
    return ALGEA_DIM_MISMATCH;
  }
  if (ALGEAvdim(out) < ALGEAvdim(v)) {
    ALGEAmultiplyFlatTV(out, A, v);
  } else if (ALGEAvdim(out) > ALGEAvdim(v)) {
    ALGEAmultiplyTallTV(out, A, v);
  } else {
    ALGEAmultiplySquareTV(out, A, v);
  }
  return ALGEA_OK;
}
