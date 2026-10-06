#include "test.h"

#include "algea/generic.h"
#include "algea/operations.h"
#include "algea/tridiagonal.h"
#include "algea/vector.h"

#include <complex.h>

#define conv(z) creal((z)), cimag((z))

int main() {
  // 1x1 matrix
  ALGEA_TRIDIAGONAL *A = nullptr;
  ALGEAnewTridiagonal(&A, 1, 1);
  aat(A, 0, 0) = 7;
  ALGEA_VECTOR *v = nullptr;
  ALGEAnewVector(&v, 1);
  aat(v, 0) = 3;
  ALGEA_VECTOR *res = nullptr;
  ALGEAnewVector(&res, 1);

  ALGEAmultiplyTV(res, A, v);

  test(aat(res, 0), 21);

  ALGEAdeleteTridiagonal(A);
  ALGEAdeleteVector(v);
  ALGEAdeleteVector(res);
  A = nullptr;
  v = res = nullptr;

  /*
   * Square matrix: 3x3
   */
  ALGEAnewTridiagonal(&A, 3, 3);

  ALGEA_ELEMENT refA[][3] = {{2, -1, 0}, {3, 4, 2}, {0, -2, 1}};

  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      aat(A, i, j) = refA[i][j];
    }
  }

  ALGEAnewVector(&v, 3);

  ALGEA_ELEMENT refv[] = {1, 2, -1};
  for (size_t i = 0; i < 3; ++i) aat(v, i) = refv[i];

  ALGEAnewVector(&res, 3);

  ALGEA_VECTOR *ref = nullptr;
  ALGEAnewVector(&ref, 3);
  aat(ref, 0) = 0;
  aat(ref, 1) = 9;
  aat(ref, 2) = -5;

  ALGEAmultiplyTV(res, A, v);

  test(ALGEAvequal(res, ref), true);

  ALGEAdeleteTridiagonal(A);
  ALGEAdeleteVector(v);
  ALGEAdeleteVector(res);
  ALGEAdeleteVector(ref);
  A = nullptr;
  v = res = ref = nullptr;

  /*
   * Tall matrix: 5x3
   */
  ALGEAnewTridiagonal(&A, 5, 3);

  ALGEA_ELEMENT refTallA[][3] = {
      {2, -1, 0}, {3, 4, 2}, {0, -2, 1}, {0, 0, 5}, {0, 0, 0}};

  for (size_t i = 0; i < 5; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      aat(A, i, j) = refTallA[i][j];
    }
  }

  ALGEAnewVector(&v, 3);
  aat(v, 0) = 8, aat(v, 1) = 5, aat(v, 2) = -3;

  ALGEAnewVector(&res, 5);

  ALGEAnewVector(&ref, 5);
  aat(ref, 0) = 11;
  aat(ref, 1) = 38;
  aat(ref, 2) = -13;
  aat(ref, 3) = -15;
  aat(ref, 4) = 0;

  ALGEAmultiplyTV(res, A, v);

  for (size_t i = 0; i < res->dim; ++i) {
    printf("%f + i%f | %f + i%f\n", conv(aat(res, i)), conv(aat(ref, i)));
  }
  test(ALGEAvequal(res, ref), true);

  ALGEAdeleteTridiagonal(A);
  ALGEAdeleteVector(v);
  ALGEAdeleteVector(res);
  ALGEAdeleteVector(ref);
  A = nullptr;
  v = res = ref = nullptr;

  /*
   * Flat / wide matrix: 3x5
   */
  ALGEAnewTridiagonal(&A, 3, 5);

  ALGEA_ELEMENT refFlatA[][5] = {
      {2, -1, 0, 0, 0}, {3, 4, 2, 0, 0}, {0, -2, 1, 5, 0}};

  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 5; ++j) {
      aat(A, i, j) = refFlatA[i][j];
    }
  }

  ALGEAnewVector(&ref, 3);
  aat(ref, 0) = 13, aat(ref, 1) = 42, aat(ref, 2) = -28;

  ALGEAnewVector(&v, 5);

  ALGEAnewVector(&v, 5);
  aat(v, 0) = 8;
  aat(v, 1) = 3;
  aat(v, 2) = 3;
  aat(v, 3) = -5;
  aat(v, 4) = 0;

  ALGEAnewVector(&res, 3);

  ALGEAmultiplyTV(res, A, v);

  test(ALGEAvequal(res, ref), true);

  ALGEAdeleteTridiagonal(A);
  ALGEAdeleteVector(v);
  ALGEAdeleteVector(res);
  ALGEAdeleteVector(ref);

  exit(EXIT_SUCCESS);
}
