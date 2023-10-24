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

void utils::fillVectorMatrixFromArray(matrix_t& matrix) {
	for (int i = 0; i < ROWS; i++) {
		row_t row;
		for (int j = 0; j < COLS; j++) {
			row.push_back(CONST_MATRIX[i][j]);
		}
		matrix.push_back(row);
	}
}

void utils::printVecMatrix(const matrix_t matrix) {
	for (row_t row : matrix) {
		for (double column : row) {
			printf("%7.1f", column);
		}
		cout << endl;
	}
}

void utils::fillArrayMatrixFromArray(double**& array) {
	array = new double* [ROWS];
	for (int i = 0; i < ROWS; i++) {
		array[i] = new double[COLS];
		for (int j = 0; j < COLS; j++) {
			array[i][j] = CONST_MATRIX[i][j];
		}
	}
}

void utils::printArrayMatrix(double** array) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("%7.1f", array[i][j]);
		}
		cout << endl;
	}
}

void utils::multiplyArrayRow(double** array, int row, double mult) {
	for (int i = 0; i < COLS; i++) {
		if (array[row][i] != 0) {
			array[row][i] = array[row][i] * mult;
		}
	}
}

void utils::divideArrayRow(double** array, int row, double div) {
	for (int i = 0; i < COLS; i++) {
		if (array[row][i] != 0) {
			array[row][i] = array[row][i] / div;
		}
	}
}

void utils::multiplyArrayRowAndAdd(double** array, int pivotRow, int targetRow, double mult) {
	for (int column = 0; column < COLS; column++) {
		array[targetRow][column] += array[pivotRow][column] * mult;
	}
}

void utils::divideArrayRowAndAdd(double** array, int pivotRow, int targetRow, double div) {
	for (int column = 0; column < COLS; column++) {
		array[targetRow][column] += array[pivotRow][column] / div;
	}
}
