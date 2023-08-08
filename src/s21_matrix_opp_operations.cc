#include <cmath>
#include <exception>

#include "s21_matrix_oop.h"
/**
 * @brief Checks matrices for equality with each other
 *
 * @param other
 * @return true
 * @return false
 */
bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool result = true;
  if (this != &other) {
    result = false;
    if (IsSameDimensionMatrix(other)) {
      result = true;
      for (int i = 0; i < rows_ && result; ++i) {
        for (int j = 0; j < cols_ && result; ++j) {
          if (fabs(matrix_[i][j] - other.matrix_[i][j]) > kAccuracy) {
            result = false;
          }
        }
      }
    }
  }
  return result;
}

/**
 * @brief Adds the second matrix to the current one
 *
 * @param other
 */
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!IsSameDimensionMatrix(other)) throw "Different dimensions of matrices";
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] += other.matrix_[i][j];
}

/**
 * @brief Subtracts another matrix from the current one
 *
 * @param other
 */
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!IsSameDimensionMatrix(other)) throw "Different dimensions of matrices";
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] -= other.matrix_[i][j];
}

/**
 * @brief Multiplies the current matrix by a number
 *
 * @param num
 */
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

/**
 * @brief Multiplies the current matrix by the second matrix
 *
 * @param other
 */
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw "The number of columns of the first matrix is not equal to the number of rows of the second matrix";
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

/**
 * @brief Creates a new transposed matrix from the current one and returns it
 *
 * @return S21Matrix
 */
S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

/**
 * @brief Calculates and returns the determinant of the current matrix
 *
 * @return double
 */
double S21Matrix::Determinant() {
  if (!IsSquareMatrix()) throw "Matrix is not square";
  double result = 0;
  if (IsMatrixNumber()) {
    result = matrix_[0][0];
  } else if (cols_ == 2 && rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    for (int j = 0; j < cols_; ++j) {
      if (matrix_[0][j] != 0) {
        result += (matrix_[0][j]) * (GetSubmatrix(0, j).Determinant()) *
                  pow(-1, 2 + j);
      }
    }
  }
  return result;
}

/**
 * @brief Calculates the algebraic addition matrix of the current one and
 * returns it
 *
 * @return S21Matrix
 */
S21Matrix S21Matrix::CalcComplements() {
  if (!IsSquareMatrix()) throw "Matrix is not square";
  S21Matrix result(rows_, cols_);
  if (!IsMatrixNumber()) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        S21Matrix temp = GetSubmatrix(i, j);
        result.matrix_[i][j] = temp.Determinant() * pow(-1, (1 + i) + (1 + j));
      }
    }
  } else {
    result.matrix_[0][0] = 1.;
  }
  return result;
}

/**
 * @brief Calculates and returns the inverse matrix
 *
 * @return S21Matrix
 */
S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix result;
  double determinant = Determinant();
  if (fabs(determinant) < kAccuracy) throw "Matrix determinant is 0";
  result = CalcComplements().Transpose() * (1. / determinant);
  return result;
}
