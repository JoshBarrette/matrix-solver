#include "Matrix.h"
#include "utils.h"
#include <iostream>

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

void Matrix::populateFromConstArray() {
    this->m_rows = utils::ROWS;
    this->m_columns = utils::COLS;

    for (int i = 0; i < this->m_rows; i++) {
		row_t row;
		for (int j = 0; j < this->m_columns; j++) {
			row.push_back(utils::CONST_MATRIX[i][j]);
		}
		this->m_matrix.push_back(row);
	}
}

void Matrix::populateFromVector(matrix_t& m) {
    this->m_matrix = m;
    this->m_rows = m.size();
    if (this->m_rows > 0) {
        this->m_columns = m[0].size();
    } else {
        this->m_columns = 0;
    }

    // printf("Rows: %d, Cols: %d\n", this->m_rows, this->m_columns);
}

void Matrix::reduce() {
    this->descend();
    // this->ascend();
}

// TODO: Pretty sure this still doesn't catch some cases.
// Implement importing from CSVs to make this easier to work on.
void Matrix::descend() {
    int lastRow = this->m_rows - 1;
    int currentColumn = 0;

    for (int pivotRow = 0; pivotRow < lastRow; pivotRow++) {
        double currentNum = this->m_matrix[pivotRow][pivotRow];
        for (int findNonZero = currentColumn; currentColumn < this->m_columns; findNonZero++) {
            if (this->m_matrix[pivotRow + 1][findNonZero] == 0) {
                currentColumn++;
            } else {
                break;
            }
        }

        if (this->m_matrix[pivotRow][currentColumn] != 1) {
            this->divideRow(pivotRow, this->m_matrix[pivotRow][currentColumn]);
        }

        for (int targetRow = pivotRow + 1; targetRow < this->m_rows; targetRow++) {
            double mult = this->m_matrix[targetRow][currentColumn] / currentNum * -1.0;
            this->multAndAdd(targetRow, currentColumn, mult);
        }

        currentColumn++;
    }

    for (int column = this->m_columns - 1; column > 0; column--) {
        if (this->m_matrix[lastRow][column - 1] == 0) {
            this->divideRow(lastRow, this->m_matrix[lastRow][column]);
            return;
        }
    }
}

void Matrix::ascend() {
    int currentRow = this->m_rows - 1;

    for (int column = this->m_columns - 1; column > 0 && currentRow > 0; column--) {
        if (this->m_matrix[currentRow][column - 1] == 0) {
            // mult and add to row above to continue reducing
        }
    }
}

row_t& Matrix::operator[](int numRow) {
    if (numRow < this->m_rows && numRow >= 0) {
        return this->m_matrix[numRow];
    } else {
        return row_t{};
    }
}

void Matrix::multiplyRow(int rowNum, double mult) {
    row_t& row = this->m_matrix[rowNum];
    for (int i = 0; i < this->m_columns; i++) {
        if (row[i] != 0) {
            row[i] = row[i] * mult;
        }
    }
}

void Matrix::divideRow(int rowNum, double div) {
    row_t& row = this->m_matrix[rowNum];
    for (int i = 0; i < this->m_columns; i++) {
        if (row[i] != 0) {
            row[i] = row[i] / div;
        }
    }
}

void Matrix::multAndAdd(int targetRowNum, int fromRowNum, double mult) {
    row_t& fromRow = this->m_matrix[fromRowNum];
    row_t& targetRow = this->m_matrix[targetRowNum];
    for (int i = 0; i < this->m_columns; i++) {
        targetRow[i] += fromRow[i] * mult;
    }
}

void Matrix::divAndAdd(int targetRowNum, int fromRowNum, double div) {
    row_t& fromRow = this->m_matrix[fromRowNum];
    row_t& targetRow = this->m_matrix[targetRowNum];
    for (int i = 0; i < this->m_columns; i++) {
        targetRow[i] += fromRow[i] / div;
    }
}

matrix_t& Matrix::getMatrix() {
    return this->m_matrix;
}

row_t& Matrix::getRow(int rowNum) {
    return this->m_matrix[rowNum];
}

int Matrix::getRows() {
    return this->m_rows;
}

int Matrix::getCols() {
    return this->m_columns;
}

void Matrix::printRow(int numRow) {
    for(double column : m_matrix[numRow]) {
        printf("%7.1f", column);
    }
    printf("\n");
}

void Matrix::printMatrix() {
    for (row_t row : this->m_matrix) {
		for (double column : row) {
			printf("%7.1f", column);
		}
		printf("\n");
	}
}
