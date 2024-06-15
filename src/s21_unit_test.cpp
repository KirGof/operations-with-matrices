#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

void fillMatrix(double *seq, S21Matrix &other) {
  int n = 0;
  for (int i = 0; i < other.GetRows(); i++) {
    for (int j = 0; j < other.GetCols(); j++) {
      other(i, j) = seq[n++];
    }
  }
}

TEST(Matrix, Constructors) {
  S21Matrix left;
  left(0, 0) = 11.11;
  S21Matrix right(3, 3);
  right(0, 0) = 11.11;
  EXPECT_EQ(left, right);
}

TEST(Matrix, Copy) {
  S21Matrix basic(2, 2);
  double seq[] = {11.11, 12.12, 21.21, 31.31};
  fillMatrix(seq, basic);
  S21Matrix copy(basic);
  EXPECT_EQ(basic, copy);
}

TEST(Matrix, Move) {
  S21Matrix basic(2, 2);
  double seq[] = {11.11, 12.12, 21.21, 31.31};
  fillMatrix(seq, basic);
  S21Matrix copy(basic);
  S21Matrix move(std::move(basic));
  EXPECT_EQ(move, copy);
  EXPECT_FALSE(move == basic);
}

TEST(Matrix, SetterGetter) {
  S21Matrix right(123, 911);
  EXPECT_EQ(right.GetCols(), 911);
  EXPECT_EQ(right.GetRows(), 123);
  right.SetRows(2);
  EXPECT_EQ(right.GetRows(), 2);
  right.SetCols(20);
  EXPECT_EQ(right.GetCols(), 20);
}

TEST(Matrix, Operations) {
  S21Matrix basic(3, 3);
  double seq[] = {1, 2, 4, 3, 3, 5, 2, 4, 4};
  fillMatrix(seq, basic);
  S21Matrix one(3, 3);
  double seq_one[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  fillMatrix(seq_one, one);
  S21Matrix calc(3, 3);
  calc = basic.InverseMatrix();
  EXPECT_TRUE(calc == basic.InverseMatrix());
  calc.MulMatrix(basic);
  EXPECT_EQ(one, calc);
  S21Matrix res(3, 3);
  double val[] = {3, 0, 0, 0, 3, 0, 0, 0, 3};
  fillMatrix(val, res);
  one.MulNumber(3);
  EXPECT_EQ(res, one);
}

TEST(Matrix, Determinant) {
  S21Matrix other = S21Matrix();
  other.SetCols(4);
  other.SetRows(4);
  double seq[] = {1, 2, 3, 5, 6, 1, 12, 3, 0, 11, 2, 33, 7, 68, 9, 71};
  fillMatrix(seq, other);
  double det = -6984;
  EXPECT_EQ(other.Determinant(), det);
  other.SetCols(80);
  other.SetRows(80);
  EXPECT_EQ(other.Determinant(), 0.0);
  S21Matrix one(1, 1);
  one(0, 0) = 5;
  EXPECT_EQ(one.Determinant(), one(0, 0));
}

TEST(Matrix, Operators) {
  S21Matrix basic(3, 3);
  double seq[] = {11.01, 22.02, 33.03, 44.04, 55.05,
                  66.06, 77.07, 88.08, 99.09};
  fillMatrix(seq, basic);
  S21Matrix sum(3, 3);
  sum = basic + basic;
  basic *= 2.0;
  EXPECT_EQ(sum, basic);
  for (int i = 0; i < 3; i++) {
    sum += basic;
    sum *= 2.0;
    EXPECT_FALSE(sum == basic);
    sum *= 0.5;
    sum -= basic;
  }
  EXPECT_EQ(sum, basic);
  sum = sum * sum;
  basic *= basic;
  EXPECT_EQ(basic, sum);
  basic = basic - sum;
  sum = sum - basic;
  EXPECT_FALSE(basic == sum);
}

TEST(Matrix, CalcComplements) {
  S21Matrix basic(3, 3);
  double seq1[] = {-1, 2, 5, 3, 4, 6, -8, 2, 12};
  fillMatrix(seq1, basic);
  S21Matrix res(3, 3);
  double seq2[] = {36, -84, 38, -14, 28, -14, -8, 21, -10};
  fillMatrix(seq2, res);
  EXPECT_EQ(res, basic.CalcComplements());
}

TEST(Matrix, Errors) {
  EXPECT_THROW(S21Matrix errors(-123, 0), std::out_of_range);
  EXPECT_THROW(S21Matrix errors(1, 0), std::out_of_range);
  S21Matrix errorLeft(1, 55);
  S21Matrix errorRight(2, 55);
  EXPECT_THROW(errorLeft -= errorRight, std::out_of_range);
  EXPECT_THROW(errorLeft += errorRight, std::out_of_range);
  EXPECT_THROW(errorLeft *= errorRight, std::out_of_range);
  EXPECT_THROW(errorLeft - errorRight, std::out_of_range);
  EXPECT_THROW(errorLeft + errorRight, std::out_of_range);
  EXPECT_THROW(errorLeft * errorRight, std::out_of_range);
  EXPECT_THROW(errorLeft.Determinant(), std::out_of_range);
  EXPECT_THROW(errorLeft.CalcComplements(), std::out_of_range);
  S21Matrix basic(4, 4);
  EXPECT_THROW(basic.InverseMatrix(), std::out_of_range);
  EXPECT_THROW(basic(1, 123), std::out_of_range);
  EXPECT_THROW(basic(-12, 1), std::out_of_range);
  S21Matrix qwerty(1, 1);
  EXPECT_THROW(qwerty.SetCols(0), std::out_of_range);
  EXPECT_THROW(qwerty.SetRows(0), std::out_of_range);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
