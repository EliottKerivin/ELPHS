#include "algea/matrix.h"
#include "algea/element.h"
#include "algea/errors.h"
#include "test.h"

#include <complex.h>
#include <stdint.h>
#include <stdlib.h>

static int check = 0;
void handler(const char[], const char[], int) { check = 5; }

int main() {
  // Allocation
  ALGEA_MATRIX *A = ALGEAnewMatrix(SIZE_MAX, 2);
  test(A == nullptr, true);
  A = ALGEAnewMatrix(SIZE_MAX - 5, 1);
  test(A == nullptr, true);
  A = ALGEAnewMatrix(3, 2);
  test(A->rows == 3 && A->columns == 2, true);

  // Accessing
  ALGEA_MATRIX *B = ALGEAnewMatrix(2, 3);

  for (size_t i = 0; i < 6; ++i) {
    A->x_[i] = i;
    B->x_[i] = i;
  }
  printf("%f + i %f\n", creal(ALGEAat(A, 0, 0)), cimag(ALGEAat(A, 0, 0)));
  test(ALGEAat(A, 0, 0), 0);
  test(ALGEAat(A, 1, 1), 3);
  test(ALGEAat(B, 1, 0), 3);
  test(ALGEAat(B, 1, 1), 4);

  // Equality
  test(ALGEAmatrixEqual(A, B), false);
  ALGEA_MATRIX *C = ALGEAduplicateMatrix(A);
  test(ALGEAmatrixEqual(A, C), true);

  ALGEAsetMatrix(C, 29.63);
  for (size_t i = 0; i < C->rows * C->columns; ++i)
    if (C->x_[i] != 29.63) exit(EXIT_FAILURE);
  ALGEAsetMatrix(C, 0);
  for (size_t i = 0; i < C->rows * C->columns; ++i) test(C->x_[i], 0);
  ALGEA_MATRIX *D = ALGEAnewZeroedMatrix(C->rows, C->columns);
  test(ALGEAmatrixEqual(C, D), true);

  // Check error handler
  free(A->x_);
  A->x_ = malloc(15 * sizeof(ALGEA_ELEMENT));
  ALGEAsetBoundsOverflowHandler(handler);
  ALGEAat(A, 2, 2); // one past end (as we didn't update rows or columns)
  test(check, 5);

  ALGEAdeleteMatrix(A);
  ALGEAdeleteMatrix(B);
  ALGEAdeleteMatrix(C);
  ALGEAdeleteMatrix(D);
  exit(EXIT_SUCCESS);
}
