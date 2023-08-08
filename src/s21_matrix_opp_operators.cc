#include <exception>

#include "s21_matrix_oop.h"

/**
 * @brief Addition of two matrices
 *
 * @param other
 * @return S21Matrix
 */
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

/**
 * @brief Subtraction of one matrix from another
 *
 * @param other
 * @return S21Matrix
 */
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

/**
 * @brief Matrix multiplication
 *
 * @param other
 * @return S21Matrix
 */
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

/**
 * @brief Matrix multiplication by a number
 *
 * @param num
 * @return S21Matrix
 */
S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

/**
 * @brief Number multiplication by a matrix
 *
 * @param num
 * @return S21Matrix
 */
S21Matrix operator*(const double num, S21Matrix& other) {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}

/**
 * @brief Checks for matrices equality
 *
 * @param other
 * @return true
 * @return false
 */
bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

/**
 * @brief Copy assignment operator
 *
 * @param other
 * @return S21Matrix&
 */
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) CopyFrom(other);
  return *this;
}

/**
 * @brief Copy assignment operator
 *
 * @param other
 * @return S21Matrix&
 */
S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) CopyFrom(other);
  return *this;
}

/**
 * @brief Addition assignment
 *
 * @param other
 * @return S21Matrix&
 */
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

/**
 * @brief Difference assignment
 *
 * @param other
 * @return S21Matrix&
 */
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}
/**
 * @brief Multiplication by a matrix assignment
 *
 * @param other
 * @return S21Matrix&
 */
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

/**
 * @brief Multiplication matrix by a number assignment
 *
 * @param num
 * @return S21Matrix&
 */
S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

/**
 * @brief Indexation by matrix elements (row, column)
 *
 * @param i number of row (from 1 to rows)
 * @param j numder of column (from 1 to columns)
 * @return double
 */
double& S21Matrix::operator()(int i, int j) {
  if (i > rows_ || j > cols_ || !IsNaturalNumbers(i, j))
    throw "Index is outside the matrix";
  --i, --j;
  return matrix_[i][j];
}
