#include "algea/tridiagonal.h"
#include "algea/errors.h"
#include "test.h"
#include <stdint.h>

int main() {
  ALGEA_TRIDIAGONAL *tri = (ALGEA_TRIDIAGONAL *)1;
  test(ALGEAnewTridiagonal(&tri, 7, 7), ALGEA_INVALID_OUT);
  tri = nullptr;
  test(ALGEAnewTridiagonal(&tri, 0, 7), ALGEA_INVALID_ARGUMENT);
  test(ALGEAnewTridiagonal(&tri, 7, 0), ALGEA_INVALID_ARGUMENT);
  test(ALGEAnewTridiagonal(&tri, SIZE_MAX, SIZE_MAX), ALGEA_OVERFLOW);
  test(ALGEAnewTridiagonal(&tri, 3, 7), ALGEA_OK);

  for (size_t i = 0; i < 2; ++i) {
    tri->upper_[i] = 1, tri->middle_[i] = 2, tri->lower_[i] = 3;
  }
  tri->middle_[2] = 2;

  test(ALGEAtat(tri, 0, 0) == 2, true);
  test(ALGEAtat(tri, 2, 2) == 2, true);
  test(ALGEAtat(tri, 0, 1) == 1, true);
  test(ALGEAtat(tri, 1, 0) == 3, true);
  test(ALGEAtat(tri, 2, 4) == 0, true);
  test(ALGEAtat(tri, 2, 6) == 0, true);

  ALGEAdeleteTridiagonal(tri);
  exit(EXIT_SUCCESS);
}
