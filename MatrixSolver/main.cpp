#include <iostream>
#include "utils.h"
#include "rowreduce.h"
#include "Matrix.h"

int main() {	
	Matrix m;
	m.populateFromConstArray();

	m.printMatrix();

	m.reduce();

	std::cout << std::endl;
	m.printMatrix();

	std::cout << m[3][0] << std::endl;

	return 0;
}
