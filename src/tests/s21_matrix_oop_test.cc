#include "../s21_matrix_oop.h"

#include <gtest/gtest.h>

TEST(Accessor, Rows) {
  S21Matrix A;
  ASSERT_EQ(A.GetRows(), 3);
}

TEST(Accessor, Cols) {
  S21Matrix A;
  ASSERT_EQ(A.GetCols(), 3);
}

TEST(Mutator, Rows) {
  S21Matrix A;
  A.SetRows(10);
  ASSERT_EQ(A.GetRows(), 10);
  A.SetRows(2);
  ASSERT_EQ(A.GetRows(), 2);
}

TEST(Mutator, Cols) {
  S21Matrix A;
  A.SetCols(10);
  ASSERT_EQ(A.GetCols(), 10);
  A.SetCols(1);
  ASSERT_EQ(A.GetCols(), 1);
}

TEST(Constructor, Default) {
  S21Matrix A;
  ASSERT_EQ(A.GetRows(), 3);
  ASSERT_EQ(A.GetCols(), 3);
}

TEST(Constructor, Parametrized) {
  S21Matrix A(5, 7);
  ASSERT_EQ(A.GetRows(), 5);
  ASSERT_EQ(A.GetCols(), 7);
}

TEST(Constructor, Copy) {
  S21Matrix A(7, 8);
  S21Matrix B(A);
  ASSERT_EQ(B.GetRows(), 7);
  ASSERT_EQ(B.GetCols(), 8);
}

TEST(Constructor, Move) {
  S21Matrix A(1, 1);
  A(1, 1) = 5;
  S21Matrix B(std::move(A));
  ASSERT_TRUE(B(1, 1) == 5);
  ASSERT_TRUE(B.GetCols() == 1);
  ASSERT_TRUE(B.GetRows() == 1);

  ASSERT_TRUE(A.GetCols() == 0);
  ASSERT_TRUE(A.GetRows() == 0);
}

TEST(Operation, EqMatrix_True) {
  S21Matrix A;
  S21Matrix B;
  ASSERT_EQ(A.EqMatrix(B), true);
}

TEST(Operation, EqMatrix_False) {
  S21Matrix A(2, 2);
  S21Matrix B;
  ASSERT_EQ(A.EqMatrix(B), false);
}

TEST(Operation, EqMatrix_False2) {
  S21Matrix A;
  S21Matrix B;
  A(1, 1) = 2;
  B(1, 1) = 3;
  ASSERT_EQ(A.EqMatrix(B), false);
}

TEST(Operation, SumMatrix) {
  S21Matrix A(2, 2);
  A(1, 1) = 1;
  A(1, 2) = 2;
  A(2, 1) = 3;
  A(2, 2) = 4;

  S21Matrix B(2, 2);
  B(1, 1) = 5;
  B(1, 2) = 6;
  B(2, 1) = 7;
  B(2, 2) = 8;

  S21Matrix C(2, 2);
  C(1, 1) = 6;
  C(1, 2) = 8;
  C(2, 1) = 10;
  C(2, 2) = 12;

  A.SumMatrix(B);
  ASSERT_TRUE(A == C);
}

TEST(Operation, SubMatrix) {
  S21Matrix A(2, 2);
  A(1, 1) = 1;
  A(1, 2) = 2;
  A(2, 1) = 3;
  A(2, 2) = 4;

  S21Matrix B(2, 2);
  B(1, 1) = 5;
  B(1, 2) = 6;
  B(2, 1) = 7;
  B(2, 2) = 8;

  S21Matrix C(2, 2);
  C(1, 1) = 6;
  C(1, 2) = 8;
  C(2, 1) = 10;
  C(2, 2) = 12;

  C.SubMatrix(B);
  ASSERT_TRUE(A == C);
}

TEST(Operation, MulMatrix) {
  S21Matrix A(3, 2);
  A(1, 1) = 1;
  A(1, 2) = 2;
  A(2, 1) = 3;
  A(2, 2) = 4;
  A(3, 1) = 5;
  A(3, 2) = 6;

  S21Matrix B(2, 4);
  B(1, 1) = 1;
  B(1, 2) = 2;
  B(1, 3) = 3;
  B(1, 4) = 4;
  B(2, 1) = 5;
  B(2, 2) = 6;
  B(2, 3) = 7;
  B(2, 4) = 8;

  S21Matrix C(3, 4);
  C(1, 1) = 11;
  C(1, 2) = 14;
  C(1, 3) = 17;
  C(1, 4) = 20;
  C(2, 1) = 23;
  C(2, 2) = 30;
  C(2, 3) = 37;
  C(2, 4) = 44;
  C(3, 1) = 35;
  C(3, 2) = 46;
  C(3, 3) = 57;
  C(3, 4) = 68;

  A.MulMatrix(B);
  ASSERT_TRUE(A == C);
}

TEST(Operation, MulMatrix2) {
  S21Matrix A(2, 4);
  S21Matrix B(4, 3);

  S21Matrix C(2, 3);
  A.MulMatrix(B);
  ASSERT_TRUE(A == C);
}

TEST(Operation, MulNumber) {
  S21Matrix A(2, 2);
  A(1, 1) = 1;
  A(1, 2) = 2;
  A(2, 1) = 3;
  A(2, 2) = 4;

  S21Matrix B(2, 2);
  B(1, 1) = 2.5;
  B(1, 2) = 5;
  B(2, 1) = 7.5;
  B(2, 2) = 10;

  A.MulNumber(2.5);
  ASSERT_TRUE(A == B);
}

TEST(Operation, Determinant) {
  S21Matrix A(5, 5);

  A(1, 1) = 0;
  A(1, 2) = 12;
  A(1, 3) = -12;
  A(1, 4) = 12;
  A(1, 5) = 6;

  A(2, 1) = -3;
  A(2, 2) = -9;
  A(2, 3) = 9;
  A(2, 4) = 9;
  A(2, 5) = -6;

  A(3, 1) = 0;
  A(3, 2) = 0;
  A(3, 3) = -2;
  A(3, 4) = 4;
  A(3, 5) = -2;

  A(4, 1) = -3;
  A(4, 2) = -17;
  A(4, 3) = 13;
  A(4, 4) = 3;
  A(4, 5) = -8;

  A(5, 1) = 0;
  A(5, 2) = 0;
  A(5, 3) = 4;
  A(5, 4) = -8;
  A(5, 5) = 0;

  ASSERT_DOUBLE_EQ(A.Determinant(), -1728);
}

TEST(Operation, Determinant2) {
  S21Matrix A(2, 2);
  A(1, 1) = 12;
  A(1, 2) = 1;
  A(2, 1) = 1;
  A(2, 2) = 1;
  ASSERT_DOUBLE_EQ(A.Determinant(), 11);
}

TEST(Operation, Determinant3) {
  S21Matrix A(1, 1);
  A(1, 1) = 12;
  ASSERT_DOUBLE_EQ(A.Determinant(), 12);
}

TEST(Operation, Traspose) {
  S21Matrix A(2, 2);
  A(1, 1) = 1;
  A(1, 2) = 2;
  A(2, 1) = 3;
  A(2, 2) = 4;

  S21Matrix B(2, 2);
  B(1, 1) = 1;
  B(1, 2) = 3;
  B(2, 1) = 2;
  B(2, 2) = 4;

  ASSERT_TRUE(A.Transpose() == B);
}

TEST(Operation, Complements) {
  S21Matrix A;
  A(1, 1) = 1;
  A(1, 2) = 2;
  A(1, 3) = 3;
  A(2, 1) = 0;
  A(2, 2) = 4;
  A(2, 3) = 2;
  A(3, 1) = 5;
  A(3, 2) = 2;
  A(3, 3) = 1;

  S21Matrix B;
  B(1, 1) = 0;
  B(1, 2) = 10;
  B(1, 3) = -20;
  B(2, 1) = 4;
  B(2, 2) = -14;
  B(2, 3) = 8;
  B(3, 1) = -8;
  B(3, 2) = -2;
  B(3, 3) = 4;

  ASSERT_TRUE(B == A.CalcComplements());
}

TEST(Operation, Complements2) {
  S21Matrix A(1, 1);
  A(1, 1) = 10;
  S21Matrix B(1, 1);
  B(1, 1) = 1;
  ASSERT_TRUE(B == A.CalcComplements());
}

TEST(Operation, Inverse) {
  S21Matrix A;
  A(1, 1) = 2;
  A(1, 2) = 5;
  A(1, 3) = 7;
  A(2, 1) = 6;
  A(2, 2) = 3;
  A(2, 3) = 4;
  A(3, 1) = 5;
  A(3, 2) = -2;
  A(3, 3) = -3;

  S21Matrix B;
  B(1, 1) = 1;
  B(1, 2) = -1;
  B(1, 3) = 1;
  B(2, 1) = -38;
  B(2, 2) = 41;
  B(2, 3) = -34;
  B(3, 1) = 27;
  B(3, 2) = -29;
  B(3, 3) = 24;

  ASSERT_TRUE(B == A.InverseMatrix());
}

TEST(Operator, Eq_true) {
  S21Matrix A;
  S21Matrix B;
  ASSERT_EQ(A == B, true);
}

TEST(Operator, Eq_false) {
  S21Matrix A(2, 2);
  S21Matrix B;
  ASSERT_EQ(A == B, false);
}

TEST(Operator, Indexation) {
  S21Matrix A;
  A(1, 1) = 19.94;
  ASSERT_DOUBLE_EQ(A(1, 1), 19.94);
}

TEST(Operator, Sum) {
  S21Matrix A(2, 2);
  A(1, 1) = 1;
  A(1, 2) = 2;
  A(2, 1) = 3;
  A(2, 2) = 4;

  S21Matrix B(2, 2);
  B(1, 1) = 5;
  B(1, 2) = 6;
  B(2, 1) = 7;
  B(2, 2) = 8;

  S21Matrix C(2, 2);
  C(1, 1) = 6;
  C(1, 2) = 8;
  C(2, 1) = 10;
  C(2, 2) = 12;

  S21Matrix D(A + B);
  ASSERT_TRUE(C == D);

  A += B;
  ASSERT_TRUE(A == C);
}

TEST(Operator, Sub) {
  S21Matrix A(2, 2);
  A(1, 1) = 1;
  A(1, 2) = 2;
  A(2, 1) = 3;
  A(2, 2) = 4;

  S21Matrix B(2, 2);
  B(1, 1) = 5;
  B(1, 2) = 6;
  B(2, 1) = 7;
  B(2, 2) = 8;

  S21Matrix C(2, 2);
  C(1, 1) = 6;
  C(1, 2) = 8;
  C(2, 1) = 10;
  C(2, 2) = 12;

  S21Matrix D(C - B);
  ASSERT_TRUE(D == A);

  C -= B;
  ASSERT_TRUE(A == C);
}

TEST(Operator, MulNumber) {
  S21Matrix A(2, 2);
  A(1, 1) = 1;
  A(2, 1) = 2;
  A(1, 2) = 3;
  A(2, 2) = 4;
  S21Matrix B(2, 2);
  B(1, 1) = 2;
  B(2, 1) = 4;
  B(1, 2) = 6;
  B(2, 2) = 8;

  S21Matrix C(A * 2);
  ASSERT_TRUE(C == B);
  S21Matrix D(2 * A);
  ASSERT_TRUE(D == B);
  A *= 2;
  ASSERT_TRUE(A == B);
}

TEST(Operator, MulMatrix) {
  S21Matrix A(1, 2);
  A(1, 1) = 3;
  A(1, 2) = 4;

  S21Matrix B(2, 1);
  B(1, 1) = 3;
  B(2, 1) = 4;

  S21Matrix C(1, 1);
  C(1, 1) = 25;
  ASSERT_TRUE((A * B) == C);

  S21Matrix A2(A);
  S21Matrix B2(B);
  A *= B;
  ASSERT_TRUE(A == C);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}