#include <iostream>
#include "utils.h"
#include "rowreduce.h"

using namespace std;

int main() {
	double** arrayMatrix;
	fillArrayMatrixFromArray(arrayMatrix);
	printArrayMatrix(arrayMatrix);

	printf("\n");

	// multiplyArrayRowAndAdd(arrayMatrix, 0, 1, -2);
	descend(arrayMatrix);
	printArrayMatrix(arrayMatrix);

	return 0;
}
