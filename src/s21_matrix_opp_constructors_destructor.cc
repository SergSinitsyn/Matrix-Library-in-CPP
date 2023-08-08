#include <exception>

#include "s21_matrix_oop.h"

/**
 * @brief A basic constructor that initialises a matrix of some predefined
 * dimension
 *
 */
S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

/**
 * @brief Parametrized constructor with number of rows and columns
 *
 * @param rows
 * @param cols
 */
S21Matrix::S21Matrix(const int rows, const int cols)
    : rows_{rows}, cols_{cols}, matrix_{new double*[rows_]} {
  if (!IsNaturalNumbers(rows_, cols_)) throw "Incorrect parameters";

  AllocateMatrixMemoryForRows(rows, cols);
}

/**
 * @brief Copy constructor
 *
 * @param other
 */
S21Matrix::S21Matrix(const S21Matrix& other) {
  if (this != &other) {
    AllocateMatrixMemory(other.rows_, other.cols_);
    CopyMatrixElements(other);
  }
}

/**
 * @brief Move constructor
 *
 * @param other
 */
S21Matrix::S21Matrix(S21Matrix&& other) : rows_{0}, cols_{0}, matrix_{nullptr} {
  if (this != &other) {
    std::swap(matrix_, other.matrix_);
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
  }
}

/**
 * @brief Destructor
 *
 */
S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) FreeMatrixMemory();
}