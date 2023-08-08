#include <algorithm>
#include <exception>

#include "s21_matrix_oop.h"

/**
 * @brief Сhecks matrix dimension
 *
 * @param rows
 * @param cols
 * @return true
 * @return false
 */
bool S21Matrix::IsNaturalNumbers(int rows, int cols) {
  return (rows > 0 && cols > 0);
}

/**
 * @brief Сompares dimensions of matrices
 *
 * @param other
 * @return true
 * @return false
 */
bool S21Matrix::IsSameDimensionMatrix(const S21Matrix& other) const {
  return (cols_ == other.cols_ && rows_ == other.rows_);
}

/**
 * @brief Сhecks if a matrix is square
 *
 * @return true
 * @return false
 */
bool S21Matrix::IsSquareMatrix() const { return (rows_ == cols_); }

/**
 * @brief Сhecks if a matrix is a one number
 *
 * @return true
 * @return false
 */
bool S21Matrix::IsMatrixNumber() const { return (rows_ == 1 && cols_ == 1); }

/**
 * @brief  Sets the matrix dimension
 *
 * @param new_rows
 * @param new_cols
 */
void S21Matrix::SetDimension(const int new_rows, const int new_cols) {
  if (!IsNaturalNumbers(new_rows, new_cols)) throw "Incorrect parameters";
  if (new_rows != rows_ || new_cols != cols_) {
    S21Matrix result(new_rows, new_cols);
    int old_rows = std::min(rows_, new_rows);
    int old_cols = std::min(cols_, new_cols);
    for (int i = 0; i < old_rows; ++i) {
      for (int j = 0; j < old_cols; ++j) {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
    std::swap(matrix_, result.matrix_);
    std::swap(rows_, result.rows_);
    std::swap(cols_, result.cols_);
  }
}

/**
 * @brief Мakes the matrix a submatrix with the removal of the specified row
 * and column
 *
 * @param del_row
 * @param del_col
 * @return S21Matrix
 */
S21Matrix S21Matrix::GetSubmatrix(int del_row, int del_col) {
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int oldi = 0, newi = 0; oldi < rows_; ++oldi) {
    if (oldi != del_row) {
      for (int oldj = 0, newj = 0; oldj < cols_; ++oldj) {
        if (oldj != del_col) {
          result.matrix_[newi][newj] = matrix_[oldi][oldj];
          ++newj;
        }
      }
      ++newi;
    }
  }
  return result;
}

/**
 * @brief Copy matrix from other matrix
 *
 * @param other
 */
void S21Matrix::CopyFrom(const S21Matrix& other) {
  if (this != &other) {
    if (!IsSameDimensionMatrix(other)) {
      FreeMatrixMemory();
      AllocateMatrixMemory(other.rows_, other.cols_);
    }
    CopyMatrixElements(other);
  }
}

/**
 * @brief Free matrix memory
 *
 */
void S21Matrix::FreeMatrixMemory() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
    matrix_[i] = NULL;
  }
  delete[] matrix_;
  InvalidateMatrix();
}

/**
 * @brief Allocate matrix memory
 *
 * @param rows
 * @param cols
 */
void S21Matrix::AllocateMatrixMemory(const int rows, const int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows];
  AllocateMatrixMemoryForRows(rows, cols);
}

/**
 * @brief  Allocate matrix memory rows
 *
 * @param rows
 * @param cols
 */
void S21Matrix::AllocateMatrixMemoryForRows(const int rows, const int cols) {
  for (int i = 0; i < rows; ++i) matrix_[i] = new double[cols]{};
}

/**
 * @brief Copy matrix elements (dimention of this matrix)
 *
 * @param other
 */
void S21Matrix::CopyMatrixElements(const S21Matrix& other) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
}

/**
 * @brief Invalidate the matrix
 *
 */
void S21Matrix::InvalidateMatrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}