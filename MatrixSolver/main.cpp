#include <iostream>
#include <vector>
#include "Matrix.h"

int main()
{
	Matrix m1;
	m1.populateFromCSV("../test_matrix_2.csv");
	m1.printMatrix();
	std::cout << std::endl;

	m1.transposeMatrix();
	m1.printMatrix();

	// m.printMatrix();

	// // m.rowReduce();

	// std::vector<double> vec;
	// vec.push_back(1);
	// vec.push_back(2);
	// vec.push_back(3);
	// vec.push_back(4);
	// m.multiplyMatrixByVector(vec);
	// std::cout << std::endl;
	// m.printMatrix();

	return 0;
}
