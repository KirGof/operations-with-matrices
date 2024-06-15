#include "s21_matrix_oop.h"

S21Matrix S21Matrix::Transpose() {
  S21Matrix buff(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      buff.matrix_[j][i] = matrix_[i][j];
    }
  }
  return buff;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::out_of_range(
        "Method CalcComplements The matrix is not square\n");
  }
  S21Matrix buff(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    int sign = i % 2 == 0 ? 1 : -1;
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = this->create_minor(i, j);
      double det = minor.Determinant();
      buff.matrix_[i][j] = sign * det;
      sign = -sign;
    }
  }
  return buff;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::out_of_range("Method Determinant The matrix is not square\n");
  }
  double res = 0;
  if (rows_ == 1 && cols_ == 1) {
    res = matrix_[0][0];
  } else if (rows_ == 2 && cols_ == 2) {
    res = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else if (rows_ < 8) {
    double sign = 1;
    for (int i = 0; i < rows_; i++) {
      S21Matrix minor = this->create_minor(0, i);
      double det = minor.Determinant();
      res += sign * matrix_[0][i] * det;
      sign = -sign;
    }
  } else {
    res = 1;
    for (int i = 0; i < rows_; ++i) {
      int k = i;
      for (int j = i + 1; j < rows_; ++j)
        if (std::abs(matrix_[j][i]) > std::abs(matrix_[k][i])) k = j;
      if (std::abs(matrix_[k][i]) < 1E-9) {
        res = 0;
        break;
      }
      std::swap(matrix_[i], matrix_[k]);
      if (i != k) res = -res;
      res *= matrix_[i][i];
      for (int j = i + 1; j < rows_; ++j) matrix_[i][j] /= matrix_[i][i];
      for (int j = 0; j < rows_; ++j)
        if (j != i && std::abs(matrix_[j][i]) > 1E-9)
          for (int k = i + 1; k < rows_; ++k)
            matrix_[j][k] -= matrix_[i][k] * matrix_[j][i];
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (det == 0.0) {
    throw std::out_of_range("Method InverseMatrix Matrix determinant is 0\n");
  }
  return CalcComplements().Transpose() * (1.0 / det);
}

S21Matrix S21Matrix ::create_minor(const int del_row, int del_column) const {
  int minor_rows = 0;
  int minor_columns = 0;
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    if (i != del_row) {
      for (int j = 0; j < cols_; j++) {
        if (j != del_column) {
          minor.matrix_[minor_rows][minor_columns] = matrix_[i][j];
          minor_columns++;
        }
      }
      minor_columns = 0;
      minor_rows++;
    }
  }
  return minor;
}
