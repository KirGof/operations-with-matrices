#include "s21_matrix_oop.h"

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  S21Matrix buff(other);
  *this = std::move(buff);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);

  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix buff(*this);
  buff.SumMatrix(other);
  return buff;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix buff(*this);
  buff.SubMatrix(other);
  return buff;
}

S21Matrix S21Matrix::operator*(const double x) {
  S21Matrix buff(*this);
  buff.MulNumber(x);
  return buff;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix buff(*this);
  buff.MulMatrix(other);
  return buff;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double x) {
  this->MulNumber(x);
  return *this;
}

double &S21Matrix::operator()(const int rows, const int cols) {
  if (rows > rows_ || cols > cols_ || rows < 0 || cols < 0) {
    throw std::out_of_range("Index outside the matrix\n");
  }
  return matrix_[rows][cols];
}
