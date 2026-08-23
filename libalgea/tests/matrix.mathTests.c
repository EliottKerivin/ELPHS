#include "algea/matrix.h"
#include "test.h"

int main() {
  ALGEA_MATRIX *I = ALGEAnewZeroedMatrix(3, 3);
  ALGEA_MATRIX *O = ALGEAnewZeroedMatrix(3, 3);
  ALGEA_MATRIX *R1 = ALGEAnewMatrix(3, 3);
  ALGEA_MATRIX *R2 = ALGEAnewMatrix(2, 2);

  for (size_t i = 0; i < I->columns; ++i) *ALGEAat(I, i, i) = 1;
  ALGEA_ELEMENT x1[] = {3, 4, 5, 9, 14, 19, 15, 24, 33};
  for (size_t i = 0; i < R1->rows * R1->columns; ++i) R1->x[i] = x1[i];
  ALGEA_ELEMENT x2[] = {10, 13, 28, 40};
  for (size_t i = 0; i < R2->rows * R2->columns; ++i) R2->x[i] = x2[i];

  ALGEA_MATRIX *A = ALGEAnewMatrix(3, 2);
  ALGEA_MATRIX *B = ALGEAnewMatrix(2, 3);
  for (size_t i = 0; i < A->rows * A->columns; ++i) {
    A->x[i] = i;
    B->x[i] = i;
  }

  ALGEA_MATRIX *C = ALGEAnewMatrix(3, 3);
  ALGEA_MATRIX *D = ALGEAnewMatrix(2, 2);

  test(!ALGEAmatrixMultiply(C, A, B));
  test(ALGEAmatrixEqual(C, R1));
  test(!ALGEAmatrixMultiply(D, B, A));
  test(ALGEAmatrixEqual(D, R2));

  test(!ALGEAmatrixMultiply(C, R1, I));
  test(ALGEAmatrixEqual(C, R1));
  test(!ALGEAmatrixMultiply(C, I, R1));
  test(ALGEAmatrixEqual(R1, C));

  test(!ALGEAmatrixMultiply(C, R1, R1));
  test(!ALGEAmatrixMultiply(R1, R1, R1));
  test(ALGEAmatrixEqual(C, R1));

  test(!ALGEAmatrixMultiply(R1, O, R1));
  test(ALGEAmatrixEqual(R1, O));

  ALGEAdeleteMatrix(I);
  ALGEAdeleteMatrix(O);
  ALGEAdeleteMatrix(R1);
  ALGEAdeleteMatrix(R2);
  ALGEAdeleteMatrix(A);
  ALGEAdeleteMatrix(B);
  ALGEAdeleteMatrix(C);
  ALGEAdeleteMatrix(D);
}
