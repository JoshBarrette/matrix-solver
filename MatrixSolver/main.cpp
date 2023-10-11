#include <iostream>
#include <vector>
#include <string>
#include "Matrix.h"

int main()
{
	Matrix m1;
	m1.populateFromCSV("../test_matrix_2.csv");
	m1.printMatrix();
	
	std::cout << std::endl;

	m1.rowReduce();
	m1.printMatrix();
	std::vector<std::string> ans = m1.solve();

	std::cout << std::endl;

	for (std::string s : ans) {
		std::cout << s << std::endl;
	}

	return 0;
}
