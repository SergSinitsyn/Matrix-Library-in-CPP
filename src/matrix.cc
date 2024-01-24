#include "matrix.h"

#include <algorithm>
#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#include "matrix_exception.h"

Matrix::Matrix() : Matrix(3, 3) {}

Matrix::Matrix(const int rows, const int cols) {
  if (!IsNaturalNumbers(rows, cols)) {
    throw MatrixInvalidArgumentException();
  }

  AllocateMatrixMemory(rows, cols);
}

Matrix::Matrix(const int size) : Matrix(size, size) {}

Matrix::Matrix(const Matrix& other) noexcept {
  if (this != &other) {
    AllocateMatrixMemory(other.rows_, other.cols_);
    CopyMatrixElements(other);
  }
}

Matrix::Matrix(Matrix&& other) noexcept : rows_{0}, cols_{0}, matrix_{nullptr} {
  if (this != &other) {
    std::swap(matrix_, other.matrix_);
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
  }
}

Matrix::Matrix(const std::vector<double>& data) {
  rows_ = 1;
  cols_ = data.size();
  if (cols_ <= 0) {
    throw MatrixInvalidArgumentException();
  }
  matrix_ = new double*[rows_];
  matrix_[0] = new double[cols_];
  for (int j = 0; j < cols_; ++j) {
    matrix_[0][j] = data[j];
  }
}

Matrix::Matrix(const std::vector<double>& data, const int rows,
               const int cols) {
  if (!IsNaturalNumbers(rows, cols)) {
    throw MatrixInvalidArgumentException();
  }
  if (static_cast<size_t>(rows * cols) != data.size()) {
    throw MatrixLogicErrorException("Dimensions don't match to data size");
  }

  AllocateMatrixMemory(rows, cols);

  for (int i = 0; i < rows; ++i) {
    std::copy(data.begin() + i * cols, data.begin() + (i + 1) * cols,
              matrix_[i]);
  }
}

Matrix::~Matrix() {
  if (matrix_ != nullptr) {
    FreeMatrixMemory();
  }
}

int Matrix::GetRows() const noexcept { return rows_; }

int Matrix::GetCols() const noexcept { return cols_; }

void Matrix::SetRows(const int new_rows) { SetDimension(new_rows, cols_); }

void Matrix::SetCols(const int new_cols) { SetDimension(rows_, new_cols); }

Matrix Matrix::operator+(const Matrix& other) const {
  Matrix result(*this);
  return result += other;
}

Matrix Matrix::operator-(const Matrix& other) const {
  Matrix result(*this);
  return result -= other;
}

Matrix Matrix::operator*(const Matrix& other) const {
  Matrix result(*this);
  return result *= other;
}

Matrix Matrix::operator*(const double num) const {
  Matrix result(*this);
  return result *= num;
}

Matrix operator*(const double num, Matrix& other) {
  Matrix result(other);
  return result *= num;
}

bool Matrix::operator==(const Matrix& other) const { return EqMatrix(other); }

Matrix& Matrix::operator=(const Matrix& other) noexcept {
  if (this != &other) {
    CopyFrom(other);
  }
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
  if (this != &other) {
    CopyFrom(other);
  }
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const double num) noexcept {
  MulNumber(num);
  return *this;
}

double& Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw MatrixOutOfRangeException();
  }
  return matrix_[i][j];
}

const double& Matrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw MatrixOutOfRangeException();
  }
  return matrix_[i][j];
}

std::vector<double> Matrix::ToVector() const {
  std::vector<double> result(rows_ * cols_);
  for (int i = 0; i < rows_; ++i) {
    std::copy(matrix_[i], matrix_[i] + cols_, result.data() + i * cols_);
  }
  return result;
}

bool Matrix::EqMatrix(const Matrix& other) const {
  if (this == &other) {
    return true;
  }
  if (!IsSameDimensionMatrix(other)) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > kAccuracy) {
        return false;
      }
    }
  }
  return true;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (!IsSameDimensionMatrix(other)) {
    throw MatrixLogicErrorException("Different dimensions of matrices");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix& other) {
  if (!IsSameDimensionMatrix(other)) {
    throw MatrixLogicErrorException("Different dimensions of matrices");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_) {
    throw MatrixLogicErrorException(
        "The number of columns of the first matrix is not equal to the "
        "number "
        "of rows of the second matrix");
  }

  Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

Matrix Matrix::HadamardProduct(const Matrix& other) {
  if (!IsSameDimensionMatrix(other)) {
    throw MatrixLogicErrorException("Different dimensions of matrices");
  }
  Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] = matrix_[i][j] * other.matrix_[i][j];
    }
  }
  return result;
}

void Matrix::SwapRows(int a, int b) {
  if (a >= rows_ || b >= rows_ || a < 0 || b < 0) {
    throw MatrixOutOfRangeException();
  }
  if (a != b) std::swap(matrix_[a], matrix_[b]);
}

Matrix Matrix::Transpose() const noexcept {
  Matrix result(cols_, rows_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double Matrix::Determinant() const {
  if (!IsSquareMatrix()) {
    throw MatrixLogicErrorException("Matrix is not square");
  }

  if (IsMatrixNumber()) {
    return matrix_[0][0];
  }

  double result = 0;
  for (int j = 0; j < cols_; ++j) {
    if (std::abs(matrix_[0][j]) > kAccuracy) {
      result += matrix_[0][j] * GetSubmatrix(0, j).Determinant() *
                (j % 2 == 0 ? 1 : -1);
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() const {
  if (!IsSquareMatrix()) {
    throw MatrixLogicErrorException("Matrix is not square");
  }

  Matrix result(rows_, cols_);
  if (IsMatrixNumber()) {
    result.matrix_[0][0] = 1.0;
    return result;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] =
          GetSubmatrix(i, j).Determinant() * ((i + j) % 2 == 0 ? 1 : -1);
    }
  }
  return result;
}

Matrix Matrix::InverseMatrix() const {
  double determinant = Determinant();
  if (std::abs(determinant) < kAccuracy) {
    throw MatrixLogicErrorException("Matrix determinant is 0");
  }

  return CalcComplements().Transpose() * (1.0 / determinant);
}

Matrix Matrix::ApplyFunction(std::function<double(double&)> function) const {
  Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] = function(matrix_[i][j]);
    }
  }
  return result;
}

void Matrix::FillMatrixWithRandomValues(double min, double max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(min, max);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = dis(gen);
    }
  }
}

void Matrix::Print() noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

double Matrix::SumOfMatrixElements() const {
  double sum = 0.0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      sum += matrix_[i][j];
    }
  }
  return sum;
}

bool Matrix::IsNaturalNumbers(int rows, int cols) const noexcept {
  return (rows > 0 && cols > 0);
}

bool Matrix::IsSameDimensionMatrix(const Matrix& other) const noexcept {
  return ((cols_ == other.cols_) && (rows_ == other.rows_));
}

bool Matrix::IsSquareMatrix() const noexcept { return (rows_ == cols_); }

bool Matrix::IsMatrixNumber() const noexcept {
  return ((rows_ == 1) && (cols_ == 1));
}

void Matrix::SetDimension(const int new_rows, const int new_cols) {
  if (!IsNaturalNumbers(new_rows, new_cols)) {
    throw MatrixInvalidArgumentException();
  }
  if ((new_rows == rows_) && (new_cols == cols_)) {
    return;
  }

  Matrix result(new_rows, new_cols);
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

Matrix Matrix::GetSubmatrix(int deleted_row, int deleted_col) const noexcept {
  Matrix result(rows_ - 1, cols_ - 1);

  int new_i = 0;
  for (int old_i = 0; old_i < rows_; ++old_i) {
    if (old_i == deleted_row) continue;

    int new_j = 0;
    for (int old_j = 0; old_j < cols_; ++old_j) {
      if (old_j == deleted_col) continue;
      result.matrix_[new_i][new_j] = matrix_[old_i][old_j];
      ++new_j;
    }
    ++new_i;
  }
  return result;
}

void Matrix::CopyFrom(const Matrix& other) {
  if (this != &other) {
    if (!IsSameDimensionMatrix(other)) {
      FreeMatrixMemory();
      AllocateMatrixMemory(other.rows_, other.cols_);
    }
    CopyMatrixElements(other);
  }
}

void Matrix::FreeMatrixMemory() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
    matrix_[i] = NULL;
  }
  delete[] matrix_;
  InvalidateMatrix();
}

void Matrix::AllocateMatrixMemory(const int rows, const int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows];
  for (int i = 0; i < rows; ++i) {
    matrix_[i] = new double[cols]{};
  }
}

void Matrix::CopyMatrixElements(const Matrix& other) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void Matrix::InvalidateMatrix() noexcept {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}
