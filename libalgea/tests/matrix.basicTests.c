#include "algea/matrix.h"
#include "test.h"

#include <stdint.h>
#include <stdlib.h>

int main() {
  // Allocation
  ALGEA_MATRIX *A = ALGEAnewMatrix(SIZE_MAX, 2);
  test(A == nullptr);
  A = ALGEAnewMatrix(SIZE_MAX - 5, 1);
  test(A == nullptr);
  A = ALGEAnewMatrix(3, 2);
  test(A->rows == 3 && A->columns == 2);

  // Accessing
  ALGEA_MATRIX *B = ALGEAnewMatrix(2, 3);
  for (size_t i = 0; i < 6; ++i) {
    A->x_[i] = i;
    B->x_[i] = i;
  }
  test(ALGEAat(A, 0, 0) == 0);
  test(ALGEAat(A, 1, 1) == 3);
  test(ALGEAat(B, 1, 0) == 3);
  test(ALGEAat(B, 1, 1) == 4);

  // Equality
  test(!ALGEAmatrixEqual(A, B));
  ALGEA_MATRIX *C = ALGEAduplicateMatrix(A);
  test(ALGEAmatrixEqual(A, C));

  ALGEAsetMatrix(C, 29.63);
  for (size_t i = 0; i < C->rows * C->columns; ++i) test(C->x_[i] == 29.63);
  ALGEAsetMatrix(C, 0);
  for (size_t i = 0; i < C->rows * C->columns; ++i) test(C->x_[i] == 0);
  ALGEA_MATRIX *D = ALGEAnewZeroedMatrix(C->rows, C->columns);
  test(ALGEAmatrixEqual(C, D));

  (void)ALGEAdeleteMatrix(A);
  (void)ALGEAdeleteMatrix(B);
  (void)ALGEAdeleteMatrix(C);
  (void)ALGEAdeleteMatrix(D);
  exit(EXIT_SUCCESS);
}
