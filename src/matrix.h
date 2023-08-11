#ifndef MATRIX_MATRIX_H_
#define MATRIX_MATRIX_H_

class Matrix {
 public:
  Matrix();
  Matrix(const int, const int);
  Matrix(const int);
  Matrix(const Matrix&) noexcept;
  Matrix(Matrix&&) noexcept;
  ~Matrix();

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(const int);
  void SetCols(const int);

  Matrix operator+(const Matrix&) const;
  Matrix operator-(const Matrix&) const;
  Matrix operator*(const Matrix&) const;
  Matrix operator*(const double) const;
  friend Matrix operator*(const double, Matrix&);
  bool operator==(const Matrix&) const;
  Matrix& operator=(const Matrix&) noexcept;
  Matrix& operator=(Matrix&&) noexcept;
  Matrix& operator+=(const Matrix&);
  Matrix& operator-=(const Matrix&);
  Matrix& operator*=(const Matrix&);
  Matrix& operator*=(const double) noexcept;
  double& operator()(int, int);

  bool EqMatrix(const Matrix&) const;
  void SumMatrix(const Matrix&);
  void SubMatrix(const Matrix&);
  void MulNumber(const double) noexcept;
  void MulMatrix(const Matrix&);
  Matrix Transpose() const noexcept;
  double Determinant() const;
  Matrix CalcComplements() const;
  Matrix InverseMatrix() const;

 private:
  int rows_;
  int cols_;
  double** matrix_;

  static constexpr double kAccuracy = 1E-7;

  bool IsNaturalNumbers(int, int) const noexcept;
  bool IsSameDimensionMatrix(const Matrix&) const noexcept;
  bool IsSquareMatrix() const noexcept;
  bool IsMatrixNumber() const noexcept;
  void SetDimension(const int, const int);
  Matrix GetSubmatrix(int, int) const noexcept;
  void CopyFrom(const Matrix&);
  void FreeMatrixMemory();
  void AllocateMatrixMemory(const int, const int);
  void CopyMatrixElements(const Matrix&);
  void InvalidateMatrix() noexcept;
};

#endif  // MATRIX_MATRIX_H_
