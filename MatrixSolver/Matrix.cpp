#include "Matrix.h"
#include <iostream>

Matrix::Matrix() {

}

void Matrix::populateFromArray(double** array, int numRows, int numCols) {
    this->m_matrix.clear();
    this->m_rows = numRows;
    this->m_columns = numCols;

    for(int row = 0; row < numRows; row++) {
        row_t currentRow;
        for(int col = 0; col < numCols; col++) {
            currentRow.push_back(array[row][col]);
        }
        this->m_matrix.push_back(currentRow);
    }
}

void Matrix::populateFromVector(matrix_t m) {
    this->m_matrix = m;
    this->m_rows = m.size();
    if (m_rows > 0) {
        this->m_columns = m.at(0).size();
    } else {
        m_columns = 0;
    }

    printf("Rows: %d, Cols: %d\n", this->m_rows, this->m_columns);
}

void Matrix::printRow(int numRow) {
    for(double column : m_matrix.at(numRow)) {
        printf("%7.1f", column);
    }
    printf("\n");
}

void Matrix::printMatrix() {
    for (row_t row : m_matrix) {
		for (double column : row) {
			printf("%7.1f", column);
		}
		printf("\n");
	}
}

matrix_t Matrix::getMatrix() {
    return this->m_matrix;
}

int Matrix::getRows() {
    return this->m_rows;
}

int Matrix::getCols() {
    return this->m_columns;
}
