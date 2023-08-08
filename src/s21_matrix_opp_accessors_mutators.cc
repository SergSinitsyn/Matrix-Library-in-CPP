#include "s21_matrix_oop.h"

/**
 * @brief Gets the number of matrix rows
 *
 * @return int
 */
int S21Matrix::GetRows() const { return rows_; }

/**
 * @brief Gets the number of matrix colunms
 *
 * @return int
 */
int S21Matrix::GetCols() const { return cols_; }

/**
 * @brief Sets the number of matrix rows
 *
 * @param new_rows
 */
void S21Matrix::SetRows(const int new_rows) { SetDimension(new_rows, cols_); }

/**
 * @brief Sets the number of matrix colunms
 *
 * @param new_cols
 */
void S21Matrix::SetCols(const int new_cols) { SetDimension(rows_, new_cols); }