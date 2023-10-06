#include <iostream>
#include <vector>
#include "Matrix.h"

int main()
{
	Matrix m;
	m.populateFromCSV("../matrix.csv");

	m.printMatrix();

	// m.rowReduce();

	std::vector<double> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	m.multiplyMatrixByVector(vec);
	std::cout << std::endl;
	m.printMatrix();

	return 0;
}
