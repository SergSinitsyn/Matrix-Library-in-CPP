#include "matrix.h"

#include <algorithm>
#include <cmath>
#include <exception>

Matrix::Matrix() : Matrix(3, 3) {}

Matrix::Matrix(const int rows, const int cols) {
  if (!IsNaturalNumbers(rows, cols)) throw "Incorrect parameters";
  AllocateMatrixMemory(rows, cols);
}

Matrix::Matrix(const Matrix& other) {
  if (this != &other) {
    AllocateMatrixMemory(other.rows_, other.cols_);
    CopyMatrixElements(other);
  }
}

Matrix::Matrix(Matrix&& other) : rows_{0}, cols_{0}, matrix_{nullptr} {
  if (this != &other) {
    std::swap(matrix_, other.matrix_);
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
  }
}

Matrix::~Matrix() {
  if (matrix_ != nullptr) FreeMatrixMemory();
}

int Matrix::GetRows() const { return rows_; }

int Matrix::GetCols() const { return cols_; }

void Matrix::SetRows(const int new_rows) { SetDimension(new_rows, cols_); }

void Matrix::SetCols(const int new_cols) { SetDimension(rows_, new_cols); }

bool Matrix::EqMatrix(const Matrix& other) const {
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

void Matrix::SumMatrix(const Matrix& other) {
  if (!IsSameDimensionMatrix(other)) throw "Different dimensions of matrices";
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] += other.matrix_[i][j];
}

void Matrix::SubMatrix(const Matrix& other) {
  if (!IsSameDimensionMatrix(other)) throw "Different dimensions of matrices";
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] -= other.matrix_[i][j];
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_)
    throw "The number of columns of the first matrix is not equal to the number of rows of the second matrix";
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

Matrix Matrix::Transpose() {
  Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double Matrix::Determinant() {
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

Matrix Matrix::CalcComplements() {
  if (!IsSquareMatrix()) throw "Matrix is not square";
  Matrix result(rows_, cols_);
  if (!IsMatrixNumber()) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        Matrix temp = GetSubmatrix(i, j);
        result.matrix_[i][j] = temp.Determinant() * pow(-1, (1 + i) + (1 + j));
      }
    }
  } else {
    result.matrix_[0][0] = 1.;
  }
  return result;
}

Matrix Matrix::InverseMatrix() {
  Matrix result;
  double determinant = Determinant();
  if (fabs(determinant) < kAccuracy) throw "Matrix determinant is 0";
  result = CalcComplements().Transpose() * (1. / determinant);
  return result;
}

Matrix Matrix::operator+(const Matrix& other) {
  Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

Matrix Matrix::operator*(const double num) {
  Matrix result(*this);
  result.MulNumber(num);
  return result;
}

Matrix operator*(const double num, Matrix& other) {
  Matrix result(other);
  result.MulNumber(num);
  return result;
}

bool Matrix::operator==(const Matrix& other) const { return EqMatrix(other); }

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) CopyFrom(other);
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) {
  if (this != &other) CopyFrom(other);
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

Matrix& Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double& Matrix::operator()(int i, int j) {
  if (i > rows_ || j > cols_ || !IsNaturalNumbers(i, j))
    throw "Index is outside the matrix";
  --i, --j;
  return matrix_[i][j];
}

bool Matrix::IsNaturalNumbers(int rows, int cols) {
  return (rows > 0 && cols > 0);
}

bool Matrix::IsSameDimensionMatrix(const Matrix& other) const {
  return (cols_ == other.cols_ && rows_ == other.rows_);
}

bool Matrix::IsSquareMatrix() const { return (rows_ == cols_); }

bool Matrix::IsMatrixNumber() const { return (rows_ == 1 && cols_ == 1); }

void Matrix::SetDimension(const int new_rows, const int new_cols) {
  if (!IsNaturalNumbers(new_rows, new_cols)) throw "Incorrect parameters";
  if (new_rows != rows_ || new_cols != cols_) {
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
}

Matrix Matrix::GetSubmatrix(int del_row, int del_col) {
  Matrix result(rows_ - 1, cols_ - 1);
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
  for (int i = 0; i < rows; ++i) matrix_[i] = new double[cols]{};
}

void Matrix::CopyMatrixElements(const Matrix& other) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
}

void Matrix::InvalidateMatrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}