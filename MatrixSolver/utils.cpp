#include <iostream>
#include "utils.h"

using namespace std;

void fillVectorMatrixFromArray(matrix_t& m) {
	for (int i = 0; i < ROWS; i++) {
		row_t row;
		for (int j = 0; j < COLS; j++) {
			row.push_back(CONST_MATRIX[i][j]);
		}
		m.push_back(row);
	}
}

void printVecMatrix(const matrix_t matrix) {
	for (row_t row : matrix) {
		for (double column : row) {
			printf("%7.1f", column);
		}
		cout << endl;
	}
}

void fillArrayMatrixFromArray(double**& m) {
	m = new double* [ROWS];
	for (int i = 0; i < ROWS; i++) {
		m[i] = new double[COLS];
		for (int j = 0; j < COLS; j++) {
			m[i][j] = CONST_MATRIX[i][j];
		}
	}
}

void printArrayMatrix(double** arr) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("%7.1f", arr[i][j]);
		}
		cout << endl;
	}
}
