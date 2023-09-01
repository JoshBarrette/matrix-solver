#include <iostream>
#include "utils.h"

using namespace std;

int main() {
	matrix_t vectorMatrix;
	fillVectorMatrixFromArray(vectorMatrix);
	printVecMatrix(vectorMatrix);

	printf("\n");

	double** arrayMatrix;
	fillArrayMatrixFromArray(arrayMatrix);
	printArrayMatrix(arrayMatrix);

	return 0;
}
