#ifndef MAIN
#define MAIN

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double **matrix_ =
      nullptr;  // Pointer to the memory where the matrix is allocated

 public:
  S21Matrix();                      // Default constructor
  S21Matrix(int rows_, int cols_);  // Default constructor
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();  // Destructor

  void initMatrix();
  void removeMatrix();
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix &other);

  bool EqMatrix(const S21Matrix &other) const;

  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other);
  S21Matrix operator*(const double x);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  bool operator==(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double x);
  double &operator()(const int rows, const int cols);

  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant() const;
  S21Matrix create_minor(int del_row, int del_column) const;
  S21Matrix InverseMatrix();
};

#endif
