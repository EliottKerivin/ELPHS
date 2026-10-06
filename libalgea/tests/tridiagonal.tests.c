#include "algea/tridiagonal.h"
#include "algea/errors.h"
#include "algea/generic.h"
#include "test.h"
#include <complex.h>
#include <stdint.h>

int main() {
  ALGEA_TRIDIAGONAL *tri = (ALGEA_TRIDIAGONAL *)1;
  test(ALGEAnewTridiagonal(&tri, 7, 7), ALGEA_INVALID_OUT);
  tri = nullptr;
  test(ALGEAnewTridiagonal(&tri, 0, 7), ALGEA_INVALID_ARGUMENT);
  test(ALGEAnewTridiagonal(&tri, 7, 0), ALGEA_INVALID_ARGUMENT);
  test(ALGEAnewTridiagonal(&tri, SIZE_MAX, SIZE_MAX), ALGEA_OVERFLOW);
  test(ALGEAnewTridiagonal(&tri, 3, 7), ALGEA_OK);

  for (int i = 0; i < 3; ++i) {
    tri->upper_[i] = i + 1;
    tri->middle_[i] = (i + 1) * I;
  }
  for (int i = 0; i < 2; ++i) tri->lower_[i] = -(i + 1);

  test(aat(tri, 0, 0) == I, true);
  test(aat(tri, 2, 2) == 3 * I, true);
  test(aat(tri, 0, 1) == 1, true);
  test(aat(tri, 1, 0) == -1, true);
  test(aat(tri, 1, 2) == 2, true);
  test(aat(tri, 2, 1) == -2, true);
  test(aat(tri, 2, 4) == 0, true);
  test(aat(tri, 2, 6) == 0, true);

  ALGEAdeleteTridiagonal(tri);
  exit(EXIT_SUCCESS);
}
