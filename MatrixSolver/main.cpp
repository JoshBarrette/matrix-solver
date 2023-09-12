#include <iostream>
#include "utils.h"
#include "rowreduce.h"

using namespace std;

int main() {
	double** arrayMatrix;
	utils::fillArrayMatrixFromArray(arrayMatrix);
	utils::printArrayMatrix(arrayMatrix);

	printf("\n");

	rowreduce::rowReduce(arrayMatrix);
	utils::printArrayMatrix(arrayMatrix);

	return 0;
}
