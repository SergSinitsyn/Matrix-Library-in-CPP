#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(Mutator, Rows_throw) {
  S21Matrix A;
  ASSERT_THROW(A.SetCols(0), const char*);
}

TEST(Mutator, Cols_throw) {
  S21Matrix A;
  ASSERT_THROW(A.SetCols(-3), const char*);
}

TEST(Constructor, Parametrized_throw) {
  ASSERT_THROW(S21Matrix A(0, -1), const char*);
}

TEST(Operation, SumMatrix_throw) {
  S21Matrix A(2, 2);
  S21Matrix B(1, 1);

  ASSERT_THROW(A.SumMatrix(B), const char*);
}

TEST(Operation, MulMatrix_throw) {
  S21Matrix A(2, 5);
  S21Matrix B(4, 3);

  ASSERT_THROW(A.MulMatrix(B), const char*);
}

TEST(Operation, SubMatrix_throw) {
  S21Matrix A(2, 2);
  S21Matrix B(1, 1);

  ASSERT_THROW(A.SubMatrix(B), const char*);
}

TEST(Operation, Determinant_throw) {
  S21Matrix A(3, 9);
  ASSERT_THROW(A.Determinant(), const char*);
}

TEST(Operation, Complements_throw) {
  S21Matrix A(3, 9);

  ASSERT_THROW(A.CalcComplements(), const char*);
}

TEST(Operation, Inverse_throw) {
  S21Matrix A;
  ASSERT_THROW(A.InverseMatrix(), const char*);

  S21Matrix B(2, 4);
  ASSERT_THROW(B.InverseMatrix(), const char*);
}

TEST(Operator, Indexation_throw) {
  S21Matrix A;
  ASSERT_THROW(A(0, 0), const char*);
  ASSERT_THROW(A(1, 10), const char*);
  ASSERT_THROW(A(10, 1), const char*);
  ASSERT_THROW(A(1, -3), const char*);
  ASSERT_THROW(A(-1, 1), const char*);
}

TEST(Operator, Sum_throw) {
  S21Matrix A(2, 2);
  S21Matrix B(1, 1);

  ASSERT_THROW(A.SumMatrix(B), const char*);
}

TEST(Operator, Sub_throw) {
  S21Matrix A(2, 2);
  S21Matrix B(1, 1);

  ASSERT_THROW(A.SubMatrix(B), const char*);
}