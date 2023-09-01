#pragma once

#include "types.h"

const int ROWS = 3;
const int COLS = 4;

const int CONST_MATRIX[ROWS][COLS] = {
	{ 1,  1,  1,  2 },
	{ 2,  3,  1,  3 },
	{ 1, -1, -2, -6 }
};

void fillVectorMatrixFromArray(matrix_t& m);
void printVecMatrix(const matrix_t matrix);
void fillArrayMatrixFromArray(double**& m);
void printArrayMatrix(double** arr);
