
CC := g++
CFLAGS := -std=c++17 -g -Wall -Werror -Wextra
TEST_FLAGS :=  -lgtest
OBJ := s21_matrix_oop.cpp matrix_comparison.cpp matrix_arithmetic.cpp matrix_overload_operator.cpp matrix_operations.cpp


all: s21_matrix_oop.a
	

obj:
	$(CC) -c $(CFLAGS) $(OBJ) 

s21_matrix_oop.a: obj
	ar rcs s21_matrix_oop.a *.o
	ranlib s21_matrix_oop.a
	make clean

test: 
	$(CC) --coverage $(CFLAGS) s21_unit_test.cpp $(OBJ) $(TEST_FLAGS) -o main_test  
	./main_test
	rm -rf ./report

report: test
	lcov -t "main_test" -o main_test.info -c -d .
	genhtml -o report main_test.info
	open report/index.html 
	make clean


clean:
	rm -rf *.o
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info