#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(3), cols_(3) { initMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::out_of_range("Enter constructor cols or rows equl zero\n");
  }
  initMatrix();
}

S21Matrix ::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  initMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  removeMatrix();
  // printf("DESTROY\n");
}

void S21Matrix ::initMatrix() {
  matrix_ = new double *[rows_] {};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
  }
}

void S21Matrix ::removeMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix ::SetRows(int rows) {
  if (rows < 1) {
    throw std::out_of_range("Method SetRows rows < 1\n");
  }
  if (rows_ != rows) {
    S21Matrix buff(rows, cols_);
    int low_rows = rows < rows_ ? rows : rows_;
    for (int i = 0; i < low_rows; i++) {
      for (int j = 0; j < cols_; j++) {
        buff.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(buff);
  }
}

void S21Matrix ::SetCols(int cols) {
  if (cols < 1) {
    throw std::out_of_range("Method SetCols cols < 1\n");
  }
  if (cols_ != cols) {
    S21Matrix buff(rows_, cols);
    int low_cols = cols < cols_ ? cols : cols_;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < low_cols; j++) {
        buff.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(buff);
  }
}
