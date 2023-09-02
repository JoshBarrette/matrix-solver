#include <iostream>
#include "utils.h"

using namespace std;

/*
	matrix_t vectorMatrix;
	fillVectorMatrixFromArray(vectorMatrix);
	printVecMatrix(vectorMatrix);

	double** arrayMatrix;
	fillArrayMatrixFromArray(arrayMatrix);
	printArrayMatrix(arrayMatrix);
*/

void fillVectorMatrixFromArray(matrix_t &matrix) {
	for (int i = 0; i < ROWS; i++) {
		row_t row;
		for (int j = 0; j < COLS; j++) {
			row.push_back(CONST_MATRIX[i][j]);
		}
		matrix.push_back(row);
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

void fillArrayMatrixFromArray(double**& array) {
	array = new double* [ROWS];
	for (int i = 0; i < ROWS; i++) {
		array[i] = new double[COLS];
		for (int j = 0; j < COLS; j++) {
			array[i][j] = CONST_MATRIX[i][j];
		}
	}
}

void printArrayMatrix(double** array) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("%7.1f", array[i][j]);
		}
		cout << endl;
	}
}

void multiplyArrayRow(double** array, int row, double mult) {
	for (int i = 0; i < COLS; i++) {
		if (array[row][i] == 0) {
			continue;
		}
		
		array[row][i] = array[row][i] * mult;
	}
}

void divideArrayRow(double** array, int row, double div) {
	for (int i = 0; i < COLS; i++) {
		if (array[row][i] == 0) {
			continue;
		}

		array[row][i] = array[row][i] / div;
	}
}

void multiplyArrayRowAndAdd(double** array, int fromRow, int toRow, double mult) {
	for (int i = 0; i < COLS; i++) {
		array[toRow][i] += array[fromRow][i] * mult;
	}
}

void divideArrayRowAndAdd(double** array, int fromRow, int toRow, double div) {
	for (int i = 0; i < COLS; i++) {
		array[toRow][i] += array[fromRow][i] / div;
	}
}
