#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(const int rows, const int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  int GetRows() const;
  int GetCols() const;
  void SetRows(const int new_rows);
  void SetCols(const int new_cols);

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  friend S21Matrix operator*(const double num, S21Matrix& other);
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int i, int j);

 private:
  int rows_, cols_;
  double** matrix_;

  static constexpr double kAccuracy = 1.0e-7;

  bool IsNaturalNumbers(int rows, int cols);
  bool IsSameDimensionMatrix(const S21Matrix& other) const;
  bool IsSquareMatrix() const;
  bool IsMatrixNumber() const;
  void SetDimension(const int new_rows, const int new_cols);
  S21Matrix GetSubmatrix(int del_row, int del_col);
  void CopyFrom(const S21Matrix& other);
  void FreeMatrixMemory();
  void AllocateMatrixMemory(const int rows, const int cols);
  void AllocateMatrixMemoryForRows(const int rows, const int cols);
  void CopyMatrixElements(const S21Matrix& other);
  void InvalidateMatrix();
};

#endif  // SRC_S21_MATRIX_OOP_H_
