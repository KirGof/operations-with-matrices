#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool result = true;
  if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    result = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > 1e-6) {
          result = false;
          break;
        }
      }
    }
  }
  return result;
}
