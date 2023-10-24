#include <iostream>
#include <vector>
#include <string>
#include "Matrix.h"

int main() {
	Matrix m1;
	m1.populateFromCSV("../matrix.csv");
	m1.printMatrix();

	std::cout << std::endl;

	m1.rowReduce();
	m1.printMatrix();
	m1.printMatrixData();

	m1.findBasisForRange();

	// std::vector<std::string> ans = m1.solve();

	// std::cout << std::endl;

	// for (std::string s : ans) {
	// 	std::cout << s << std::endl;
	// }

	return 0;
}
