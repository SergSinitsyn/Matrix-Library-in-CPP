#include <gtest/gtest.h>

#include "../matrix.h"

TEST(Mutator, Rows_throw) {
  Matrix A;
  ASSERT_THROW(A.SetCols(0), const char*);
}

TEST(Mutator, Cols_throw) {
  Matrix A;
  ASSERT_THROW(A.SetCols(-3), const char*);
}

TEST(Constructor, Parametrized_throw) {
  ASSERT_THROW(Matrix A(0, -1), const char*);
}

TEST(Operation, SumMatrix_throw) {
  Matrix A(1, 1);
  Matrix B(2, 2);

  ASSERT_THROW(A.SumMatrix(B), const char*);
}

TEST(Operation, MulMatrix_throw) {
  Matrix A(2, 5);
  Matrix B(4, 3);

  ASSERT_THROW(A.MulMatrix(B), const char*);
}

TEST(Operation, SubMatrix_throw) {
  Matrix A(2, 2);
  Matrix B(1, 1);

  ASSERT_THROW(A.SubMatrix(B), const char*);
}

TEST(Operation, Determinant_throw) {
  Matrix A(3, 9);
  ASSERT_THROW(A.Determinant(), const char*);
}

TEST(Operation, Complements_throw) {
  Matrix A(3, 9);

  ASSERT_THROW(A.CalcComplements(), const char*);
}

TEST(Operation, Inverse_throw) {
  Matrix A;
  ASSERT_THROW(A.InverseMatrix(), const char*);

  Matrix B(2, 4);
  ASSERT_THROW(B.InverseMatrix(), const char*);
}

TEST(Operator, Indexation_throw) {
  Matrix A;
  ASSERT_THROW(A(1, 10), const char*);
  ASSERT_THROW(A(10, 1), const char*);
  ASSERT_THROW(A(1, -3), const char*);
  ASSERT_THROW(A(-1, 1), const char*);
}

TEST(Operator, Sum_throw) {
  Matrix A(2, 2);
  Matrix B(1, 1);

  ASSERT_THROW(A.SumMatrix(B), const char*);
}

TEST(Operator, Sub_throw) {
  Matrix A(2, 2);
  Matrix B(1, 1);

  ASSERT_THROW(A.SubMatrix(B), const char*);
}