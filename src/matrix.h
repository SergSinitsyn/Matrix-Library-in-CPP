#ifndef MATRIX_MATRIX_H_
#define MATRIX_MATRIX_H_

class Matrix {
 public:
  Matrix();
  Matrix(const int rows, const int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  int GetRows() const;
  int GetCols() const;
  void SetRows(const int new_rows);
  void SetCols(const int new_cols);

  bool EqMatrix(const Matrix& other) const;
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);
  Matrix Transpose();
  double Determinant();
  Matrix CalcComplements();
  Matrix InverseMatrix();

  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator*(const double num);
  friend Matrix operator*(const double num, Matrix& other);
  bool operator==(const Matrix& other) const;
  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other);
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(const double num);
  double& operator()(int i, int j);

 private:
  int rows_, cols_;
  double** matrix_;

  static constexpr double kAccuracy = 1.0e-7;

  bool IsNaturalNumbers(int rows, int cols);
  bool IsSameDimensionMatrix(const Matrix& other) const;
  bool IsSquareMatrix() const;
  bool IsMatrixNumber() const;
  void SetDimension(const int new_rows, const int new_cols);
  Matrix GetSubmatrix(int del_row, int del_col);
  void CopyFrom(const Matrix& other);
  void FreeMatrixMemory();
  void AllocateMatrixMemory(const int rows, const int cols);
  void CopyMatrixElements(const Matrix& other);
  void InvalidateMatrix();
};

#endif  // MATRIX_MATRIX_H_
