#include <iostream>
#include <vector>

using namespace std;

typedef vector<double> row_t;
typedef vector<row_t> matrix_t;

void fillMatrixFromArray(matrix_t &m) {
	const int rows = 3;
	const int cols = 4;
	
	int matrix[rows][cols] = {
		{ 1,  1,  1,  2 },
		{ 2,  3,  1,  3 },
		{ 1, -1, -2, -6 }
	};

	for (int i = 0; i < rows; i++) {
		row_t row;
		for (int j = 0; j < cols; j++) {
			row.push_back(matrix[i][j]);
		}
		m.push_back(row);
	}
}

void printVecMatrix(const matrix_t matrix) {
	for (row_t row : matrix) {
		for (double column : row) {
			printf("%7.1f", column);
		}
		cout << endl;
	}
}

int main() {
	matrix_t m;

	fillMatrixFromArray(m);

	printVecMatrix(m);

	return 0;
}
