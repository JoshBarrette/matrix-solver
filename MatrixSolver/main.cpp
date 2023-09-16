#include <iostream>
#include "utils.h"
#include "rowreduce.h"
#include "Matrix.h"

using namespace std;

int main() {
	double** arrayMatrix;
	utils::fillArrayMatrixFromArray(arrayMatrix);
	// utils::printArrayMatrix(arrayMatrix);
	
	Matrix m;
	m.populateFromArray(arrayMatrix, 3, 4);

	m.printMatrix();

	return 0;
}
