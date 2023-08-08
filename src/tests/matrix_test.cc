#include "../matrix.h"

#include <gtest/gtest.h>

TEST(Accessor, Rows) {
  Matrix A;
  ASSERT_EQ(A.GetRows(), 3);
}

TEST(Accessor, Cols) {
  Matrix A;
  ASSERT_EQ(A.GetCols(), 3);
}

TEST(Mutator, Rows) {
  Matrix A;
  A.SetRows(10);
  ASSERT_EQ(A.GetRows(), 10);
  A.SetRows(2);
  ASSERT_EQ(A.GetRows(), 2);
}

TEST(Mutator, Cols) {
  Matrix A;
  A.SetCols(10);
  ASSERT_EQ(A.GetCols(), 10);
  A.SetCols(1);
  ASSERT_EQ(A.GetCols(), 1);
}

TEST(Constructor, Default) {
  Matrix A;
  ASSERT_EQ(A.GetRows(), 3);
  ASSERT_EQ(A.GetCols(), 3);
}

TEST(Constructor, Parametrized) {
  Matrix A(5, 7);
  ASSERT_EQ(A.GetRows(), 5);
  ASSERT_EQ(A.GetCols(), 7);
}

TEST(Constructor, Copy) {
  Matrix A(7, 8);
  Matrix B(A);
  ASSERT_EQ(B.GetRows(), 7);
  ASSERT_EQ(B.GetCols(), 8);
}

TEST(Constructor, Move) {
  Matrix A(1, 1);
  A(0, 0) = 5;
  Matrix B(std::move(A));
  ASSERT_TRUE(B(0, 0) == 5);
  ASSERT_TRUE(B.GetCols() == 1);
  ASSERT_TRUE(B.GetRows() == 1);

  ASSERT_TRUE(A.GetCols() == 0);
  ASSERT_TRUE(A.GetRows() == 0);
}

TEST(Operation, EqMatrix_True) {
  Matrix A;
  Matrix B;
  ASSERT_EQ(A.EqMatrix(B), true);
}

TEST(Operation, EqMatrix_False) {
  Matrix A(2, 2);
  Matrix B;
  ASSERT_EQ(A.EqMatrix(B), false);
}

TEST(Operation, EqMatrix_False2) {
  Matrix A;
  Matrix B;
  A(0, 0) = 2;
  B(0, 0) = 3;
  ASSERT_EQ(A.EqMatrix(B), false);
}

TEST(Operation, SumMatrix) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  Matrix C(2, 2);
  C(0, 0) = 6;
  C(0, 1) = 8;
  C(1, 0) = 10;
  C(1, 1) = 12;

  A.SumMatrix(B);
  ASSERT_TRUE(A == C);
}

TEST(Operation, SubMatrix) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  Matrix C(2, 2);
  C(0, 0) = 6;
  C(0, 1) = 8;
  C(1, 0) = 10;
  C(1, 1) = 12;

  C.SubMatrix(B);
  ASSERT_TRUE(A == C);
}

TEST(Operation, MulMatrix) {
  Matrix A(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(2, 0) = 5;
  A(2, 1) = 6;

  Matrix B(2, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;

  Matrix C(3, 4);
  C(0, 0) = 11;
  C(0, 1) = 14;
  C(0, 2) = 17;
  C(0, 3) = 20;
  C(1, 0) = 23;
  C(1, 1) = 30;
  C(1, 2) = 37;
  C(1, 3) = 44;
  C(2, 0) = 35;
  C(2, 1) = 46;
  C(2, 2) = 57;
  C(2, 3) = 68;

  A.MulMatrix(B);
  ASSERT_TRUE(A == C);
}

TEST(Operation, MulMatrix2) {
  Matrix A(2, 4);
  Matrix B(4, 3);

  Matrix C(2, 3);
  A.MulMatrix(B);
  ASSERT_TRUE(A == C);
}

TEST(Operation, MulNumber) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  Matrix B(2, 2);
  B(0, 0) = 2.5;
  B(0, 1) = 5;
  B(1, 0) = 7.5;
  B(1, 1) = 10;

  A.MulNumber(2.5);
  ASSERT_TRUE(A == B);
}

TEST(Operation, Determinant) {
  Matrix A(5, 5);

  A(0, 0) = 0;
  A(0, 1) = 12;
  A(0, 2) = -12;
  A(0, 3) = 12;
  A(0, 4) = 6;

  A(1, 0) = -3;
  A(1, 1) = -9;
  A(1, 2) = 9;
  A(1, 3) = 9;
  A(1, 4) = -6;

  A(2, 0) = 0;
  A(2, 1) = 0;
  A(2, 2) = -2;
  A(2, 3) = 4;
  A(2, 4) = -2;

  A(3, 0) = -3;
  A(3, 1) = -17;
  A(3, 2) = 13;
  A(3, 3) = 3;
  A(3, 4) = -8;

  A(4, 0) = 0;
  A(4, 1) = 0;
  A(4, 2) = 4;
  A(4, 3) = -8;
  A(4, 4) = 0;

  ASSERT_DOUBLE_EQ(A.Determinant(), -1728);
}

TEST(Operation, Determinant2) {
  Matrix A(2, 2);
  A(0, 0) = 12;
  A(0, 1) = 1;
  A(1, 0) = 1;
  A(1, 1) = 1;
  ASSERT_DOUBLE_EQ(A.Determinant(), 11);
}

TEST(Operation, Determinant3) {
  Matrix A(1, 1);
  A(0, 0) = 12;
  ASSERT_DOUBLE_EQ(A.Determinant(), 12);
}

TEST(Operation, Traspose) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  Matrix B(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 3;
  B(1, 0) = 2;
  B(1, 1) = 4;

  ASSERT_TRUE(A.Transpose() == B);
}

TEST(Operation, Complements) {
  Matrix A;
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;
  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;

  Matrix B;
  B(0, 0) = 0;
  B(0, 1) = 10;
  B(0, 2) = -20;
  B(1, 0) = 4;
  B(1, 1) = -14;
  B(1, 2) = 8;
  B(2, 0) = -8;
  B(2, 1) = -2;
  B(2, 2) = 4;

  ASSERT_TRUE(B == A.CalcComplements());
}

TEST(Operation, Complements2) {
  Matrix A(1, 1);
  A(0, 0) = 10;
  Matrix B(1, 1);
  B(0, 0) = 1;
  ASSERT_TRUE(B == A.CalcComplements());
}

TEST(Operation, Inverse) {
  Matrix A;
  A(0, 0) = 2;
  A(0, 1) = 5;
  A(0, 2) = 7;
  A(1, 0) = 6;
  A(1, 1) = 3;
  A(1, 2) = 4;
  A(2, 0) = 5;
  A(2, 1) = -2;
  A(2, 2) = -3;

  Matrix B;
  B(0, 0) = 1;
  B(0, 1) = -1;
  B(0, 2) = 1;
  B(1, 0) = -38;
  B(1, 1) = 41;
  B(1, 2) = -34;
  B(2, 0) = 27;
  B(2, 1) = -29;
  B(2, 2) = 24;

  ASSERT_TRUE(B == A.InverseMatrix());
}

TEST(Operator, Eq_true) {
  Matrix A;
  Matrix B;
  ASSERT_EQ(A == B, true);
}

TEST(Operator, Eq_false) {
  Matrix A(2, 2);
  Matrix B;
  ASSERT_EQ(A == B, false);
}

TEST(Operator, Indexation) {
  Matrix A;
  A(0, 0) = 19.94;
  ASSERT_DOUBLE_EQ(A(0, 0), 19.94);
}

TEST(Operator, Sum) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  Matrix C(2, 2);
  C(0, 0) = 6;
  C(0, 1) = 8;
  C(1, 0) = 10;
  C(1, 1) = 12;

  Matrix D(A + B);
  ASSERT_TRUE(C == D);

  A += B;
  ASSERT_TRUE(A == C);
}

TEST(Operator, Sub) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  Matrix C(2, 2);
  C(0, 0) = 6;
  C(0, 1) = 8;
  C(1, 0) = 10;
  C(1, 1) = 12;

  Matrix D(C - B);
  ASSERT_TRUE(D == A);

  C -= B;
  ASSERT_TRUE(A == C);
}

TEST(Operator, MulNumber) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  Matrix B(2, 2);
  B(0, 0) = 2;
  B(0, 1) = 4;
  B(1, 0) = 6;
  B(1, 1) = 8;

  Matrix C(A * 2);
  ASSERT_TRUE(C == B);
  Matrix D(2 * A);
  ASSERT_TRUE(D == B);
  A *= 2;
  ASSERT_TRUE(A == B);
}

TEST(Operator, MulMatrix) {
  Matrix A(1, 2);
  A(0, 0) = 3;
  A(0, 1) = 4;

  Matrix B(2, 1);
  B(0, 0) = 3;
  B(1, 0) = 4;

  Matrix C(1, 1);
  C(0, 0) = 25;
  ASSERT_TRUE((A * B) == C);

  Matrix A2(A);
  Matrix B2(B);
  A *= B;
  ASSERT_TRUE(A == C);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}