#pragma once

#include "types.h"

const int ROWS = 3;
const int COLS = 4;

const int CONST_MATRIX[ROWS][COLS] = {
	{ 1,  1,  1,  2 },
	{ 2,  3,  1,  3 },
	{ 1, -1, -2, -6 }
};

void fillVectorMatrixFromArray(matrix_t& matrix);
void printVecMatrix(const matrix_t matrix);

void fillArrayMatrixFromArray(double**& array);
void printArrayMatrix(double** array);
void multiplyArrayRow(double** array, int row, double mult);
void divideArrayRow(double** array, int row, double div);
void multiplyArrayRowAndAdd(double** array, int fromRow, int toRow, double mult);
void divideArrayRowAndAdd(double** array, int fromRow, int toRow, double div);
