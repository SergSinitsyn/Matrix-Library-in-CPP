#ifndef MATRIX_MATRIX_EXCEPTION_H_
#define MATRIX_MATRIX_EXCEPTION_H_

#include <exception>
#include <string>

class MatrixException : public std::exception {
 public:
  explicit MatrixException(const std::string& message)
      : message_("Matrix: " + message) {}

  const char* what() const noexcept override { return message_.c_str(); }

 private:
  std::string message_;
};

class MatrixInvalidArgumentException : public MatrixException {
 public:
  explicit MatrixInvalidArgumentException()
      : MatrixException("Invalid parameters") {}
};

class MatrixLogicErrorException : public MatrixException {
 public:
  explicit MatrixLogicErrorException(const std::string& message)
      : MatrixException(message) {}
};

class MatrixOutOfRangeException : public MatrixException {
 public:
  explicit MatrixOutOfRangeException()
      : MatrixException("Index is outside the matrix") {}
};

#endif  // MATRIX_MATRIX_EXCEPTION_H_