#include <gtest/gtest.h>

#include "../matrix.h"

TEST(Mutator, Rows_throw) {
  Matrix A;
  ASSERT_ANY_THROW(A.SetCols(0));
}

TEST(Mutator, Cols_throw) {
  Matrix A;
  ASSERT_ANY_THROW(A.SetCols(-3));
}

TEST(Constructor, Parametrized_throw) { ASSERT_ANY_THROW(Matrix A(0, -1)); }

TEST(Operation, SumMatrix_throw) {
  Matrix A(1, 1);
  Matrix B(2, 2);

  ASSERT_ANY_THROW(A.SumMatrix(B));
}

TEST(Operation, MulMatrix_throw) {
  Matrix A(2, 5);
  Matrix B(4, 3);

  ASSERT_ANY_THROW(A.MulMatrix(B));
}

TEST(Operation, SubMatrix_throw) {
  Matrix A(2, 2);
  Matrix B(1, 1);

  ASSERT_ANY_THROW(A.SubMatrix(B));
}

TEST(Operation, Determinant_throw) {
  Matrix A(3, 9);
  ASSERT_ANY_THROW(A.Determinant());
}

TEST(Operation, Complements_throw) {
  Matrix A(3, 9);

  ASSERT_ANY_THROW(A.CalcComplements());
}

TEST(Operation, Inverse_throw) {
  Matrix A;
  ASSERT_ANY_THROW(A.InverseMatrix());

  Matrix B(2, 4);
  ASSERT_ANY_THROW(B.InverseMatrix());
}

TEST(Operator, Indexation_throw) {
  Matrix A;
  ASSERT_ANY_THROW(A(1, 10));
  ASSERT_ANY_THROW(A(10, 1));
  ASSERT_ANY_THROW(A(1, -3));
  ASSERT_ANY_THROW(A(-1, 1));
}

TEST(Operator, Sum_throw) {
  Matrix A(2, 2);
  Matrix B(1, 1);

  ASSERT_ANY_THROW(A.SumMatrix(B));
}

TEST(Operator, Sub_throw) {
  Matrix A(2, 2);
  Matrix B(1, 1);

  ASSERT_ANY_THROW(A.SubMatrix(B));
}