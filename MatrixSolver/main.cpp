#include <iostream>
#include "Matrix.h"

int main() {	
	Matrix m;
	m.populateFromCSV("../matrix.csv");

	m.printMatrix();

	m.rowReduce();
	std::cout << std::endl;
	m.printMatrix();

	return 0;
}
