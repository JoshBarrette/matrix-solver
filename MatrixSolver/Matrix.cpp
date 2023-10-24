#include "Matrix.h"
#include "utils.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void Matrix::populateFromArray(double** array, int numRows, int numCols) {
    this->m_matrix.clear();
    this->m_rows = numRows;
    this->m_columns = numCols;

    for (int row = 0; row < numRows; row++) {
        row_t currentRow;
        for (int col = 0; col < numCols; col++) {
            currentRow.push_back(array[row][col]);
        }
        this->m_matrix.push_back(currentRow);
    }
}

void Matrix::populateFromConstArray() {
    this->m_matrix.clear();
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
}

void Matrix::populateFromCSV(std::string fileName) {
    this->m_columns = 0;
    this->m_rows = 0;
    this->m_matrix.clear();
    this->m_baseMatrix.clear();

    std::ifstream fileStream(fileName);
    std::string line;

    while (std::getline(fileStream, line)) {
        row_t currentRow;
        std::istringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            double value = std::stod(cell);
            currentRow.push_back(value);
            this->m_columns++;
        }

        this->m_matrix.push_back(currentRow);
        this->m_baseMatrix.push_back(currentRow);
        this->m_rows++;
    }

    this->m_columns = this->m_columns / this->m_rows;
}

// This doesn't catch if the matrix is unsolvable :c
std::vector<std::string> Matrix::solve() {
    std::vector<std::string> ans;
    std::string currentVar;
    int currentRow = 0;

    // I don't think we ever need to worry about the row going out of bounds but I'm playing it safe
    for (int currentColumn = 0; currentColumn < this->m_columns - 1 && currentRow < this->m_rows; currentColumn++) {
        currentVar = "";
        currentVar.append(1, (char)'a' + currentColumn).append(" = ");

        if (this->m_matrix[currentRow][currentColumn] == 0) {
            currentVar.append(1, (char)'a' + currentColumn);
            ans.push_back(currentVar);
            continue;
        }

        for (int subColumn = currentColumn + 1; subColumn < this->m_columns - 1; subColumn++) {
            if (this->m_matrix[currentRow][subColumn] == 0) {
                continue;
            }

            currentVar.append(
                std::to_string(-1.0 * this->m_matrix[currentRow][subColumn]) + (char)('a' + subColumn) + " + ");
        }

        if (this->m_matrix[currentRow][this->m_columns - 1] != 0) {
            currentVar.append(std::to_string(this->m_matrix[currentRow][this->m_columns - 1]));
        } else if (currentVar.length() == 4 && this->m_matrix[currentRow][this->m_columns - 1] == 0) {
            currentVar.append(std::to_string(this->m_matrix[currentRow][this->m_columns - 1]));
        } else if (currentVar.length() > 0) {
            currentVar.resize(currentVar.length() - 2);
        }

        if (!currentVar.empty()) {
            ans.push_back(currentVar);
        }

        currentRow++;
    }

    return ans;
}

void Matrix::findBasisForNullSpace() {
    this->m_basisForNullSpace.clear();
    this->m_basisForNullSpace = matrix_t(this->m_freeVariablesCount, row_t(this->m_columns, 0));
    this->m_freeVarChars = std::vector<char>(this->m_freeVariablesCount);

    for (int currentRow = 0; currentRow < this->m_rows; currentRow++) {
        int currentVec = 0;
        for (int currentColumn = 0; currentColumn < this->m_columns; currentColumn++) {
            if (this->m_leadingVariables.find(currentColumn) != this->m_leadingVariables.end()) {
                continue;
            }

            if (this->m_matrix[currentRow][currentColumn] != 0) {
                this->m_basisForNullSpace[currentVec][currentRow] = -1.0 * this->m_matrix[currentRow][currentColumn];
            }

            this->m_freeVarChars[currentVec] = currentColumn + 97;
            this->m_basisForNullSpace[currentVec][currentColumn] = 1;
            currentVec++;
        }
    }
}

void Matrix::findBasisForRange() {
    this->m_basisForRange.clear();
    this->m_basisForRange = matrix_t(this->m_leadingVariables.size(), row_t(this->m_rows));

    int currentVec = 0;
    for (std::set<int>::iterator itr = this->m_leadingVariables.begin();
        itr != this->m_leadingVariables.end();
        itr++) {
        for (int currentRow = 0; currentRow < this->m_rows; currentRow++) {
            this->m_basisForRange[currentVec][currentRow] = this->m_baseMatrix[*itr][currentRow];
        }
        currentVec++;
    }
}

void Matrix::rowReduce() {
    this->descend();
    this->ascend();
}

void Matrix::descend() {
    int lastRow = this->m_rows - 1;
    int currentColumn = 0;
    int lastFilledRow = 0;

    for (int pivotRow = 0; pivotRow < lastRow && currentColumn < this->m_columns; pivotRow++) {
        lastFilledRow++;
        bool shouldContinue = false;
        if (this->m_matrix[pivotRow][pivotRow] == 0) {
            shouldContinue = this->lookForSwap(pivotRow, currentColumn);
        }

        if (shouldContinue) {
            currentColumn++;
            continue;
        }

        if (this->m_matrix[pivotRow][currentColumn] != 1) {
            this->divideRow(pivotRow, this->m_matrix[pivotRow][currentColumn]);
        }

        for (int targetRow = pivotRow + 1; targetRow < this->m_rows; targetRow++) {
            double mult = -1.0 * this->m_matrix[targetRow][currentColumn];
            this->multAndAdd(targetRow, pivotRow, mult);
        }

        currentColumn++;
    }

    for (int column = 0; column < this->m_columns; column++) {
        if (this->m_matrix[lastFilledRow][column] != 0) {
            this->divideRow(lastFilledRow, this->m_matrix[lastFilledRow][column]);
            return;
        }
    }
}

bool Matrix::lookForSwap(int startingRow, int column) {
    for (int row = startingRow + 1; row < this->m_rows; row++) {
        if (this->m_matrix[row][column] != 0) {
            this->swapRows(startingRow, row);
            return false;
        }
    }

    return true;
}

void Matrix::swapRows(int rowNum1, int rowNum2) {
    row_t temp = this->m_matrix[rowNum1];
    this->m_matrix[rowNum1] = this->m_matrix[rowNum2];
    this->m_matrix[rowNum2] = temp;
}

void Matrix::ascend() {
    int currentColumn;
    this->m_freeVariablesCount = this->m_columns;
    this->m_leadingVariables.clear();

    for (int currentRow = this->m_rows - 1; currentRow > 0; currentRow--) {
        for (currentColumn = 0; currentColumn < this->m_columns; currentColumn++) {
            if (this->m_matrix[currentRow][currentColumn] == 0) {
                continue;
            }
            this->m_freeVariablesCount--;
            this->m_leadingVariables.insert(currentColumn);
            for (int risingRow = currentRow - 1; risingRow >= 0; risingRow--) {
                double mult = -1.0 * this->m_matrix[risingRow][currentColumn];
                this->multAndAdd(risingRow, currentRow, mult);
                // printf("currentRow: %d, currentColumn: %d, risingRow: %d, mult: %f\n",
                //        currentRow, currentColumn, risingRow, mult);
            }
            break;
        }

        if (currentColumn == 0) {
            break;
        }
    }

    for (int currentColumn = 0; currentColumn < this->m_columns && this->m_rows> 0; currentColumn++) {
        if (this->m_matrix[0][currentColumn] != 0) {
            this->m_freeVariablesCount--;
            this->m_leadingVariables.insert(currentColumn);
            return;
        }
    }
}

inline row_t& Matrix::operator[](int numRow) {
    return this->m_matrix[numRow];
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
    if (mult == 0) {
        return;
    }

    row_t& fromRow = this->m_matrix[fromRowNum];
    row_t& targetRow = this->m_matrix[targetRowNum];
    for (int i = 0; i < this->m_columns; i++) {
        targetRow[i] += fromRow[i] * mult;
    }
}

void Matrix::divAndAdd(int targetRowNum, int fromRowNum, double div) {
    if (div == 0) {
        printf("Attempted to divide multiply row %d by 0 and add to row %d\n", fromRowNum, targetRowNum);
        return;
    }

    row_t& fromRow = this->m_matrix[fromRowNum];
    row_t& targetRow = this->m_matrix[targetRowNum];
    for (int i = 0; i < this->m_columns; i++) {
        targetRow[i] += fromRow[i] / div;
    }
}

void Matrix::transposeMatrix() {
    if (this->m_columns == this->m_rows) {
        this->transposeSquareMatrix();
    } else {
        this->transposeRectangularMatrix();
    }
}

void Matrix::transposeSquareMatrix() {
    double temp;
    for (int i = 0; i < this->m_columns; i++) {
        for (int j = 1 + i; j < this->m_columns; j++) {
            temp = this->m_matrix[i][j];
            this->m_matrix[i][j] = this->m_matrix[j][i];
            this->m_matrix[j][i] = temp;
        }
    }
}

void Matrix::transposeRectangularMatrix() {
    int newColumns = this->m_rows;
    int newRows = this->m_columns;
    matrix_t newMatrix(newRows);

    for (int i = 0; i < newRows; i++) {
        std::vector<double> newRow(newColumns);
        newMatrix[i] = newRow;
        for (int j = 0; j < newColumns; j++) {
            newMatrix[i][j] = this->m_matrix[j][i];
        }
    }

    this->m_columns = newColumns;
    this->m_rows = newRows;
    this->m_matrix = newMatrix;
}

void Matrix::multiplyMatrixByVector(std::vector<double> vec) {
    int vecLength = vec.size();

    if (vecLength != this->m_columns) {
        printf("Incompatible vector size.\n");
        return;
    }

    matrix_t newMatrix;
    for (int currentRow = 0; currentRow < this->m_rows; currentRow++) {
        row_t newRow;
        newRow.push_back(0);
        for (int currentColumn = 0; currentColumn < this->m_columns; currentColumn++) {
            newRow[0] += this->m_matrix[currentRow][currentColumn] * vec[currentColumn];
        }
        newMatrix.push_back(newRow);
    }

    this->m_matrix = newMatrix;
    this->m_columns = 1;
}

// Can probably clean up this code by initializing the vectors to set sizes
// instead of just pushing things back over and over
void Matrix::multiplyMatrixByMatrix(matrix_t m) {
    int multRows = m.size();
    // possible out of bounds error (good thing this is just a personal project)
    int multColumns = m[0].size();

    if (multRows != this->m_columns || multColumns != this->m_rows) {
        printf("Incompatible matrix sizes.\n");
        return;
    }

    matrix_t newMatrix;
    for (int currentVector = 0; currentVector < multColumns; currentVector++) {
        for (int currentRow = 0; currentRow < this->m_rows; currentRow++) {
            row_t row;
            if (currentVector != 0) {
                row = newMatrix[currentRow];
            }
            row.push_back(0);

            for (int currentColumn = 0; currentColumn < this->m_columns; currentColumn++) {
                row[currentVector] += this->m_matrix[currentRow][currentColumn] * m[currentColumn][currentVector];
            }

            if (currentVector == 0) {
                newMatrix.push_back(row);
            } else {
                newMatrix[currentRow] = row;
            }
        }
    }

    this->m_matrix = newMatrix;
    this->m_rows = multColumns;
    this->m_columns = multColumns;
}

void Matrix::printRow(int numRow) {
    for (double column : m_matrix[numRow]) {
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

void Matrix::printBaseMatrix() {
    for (row_t row : this->m_baseMatrix) {
        for (double column : row) {
            printf("%7.1f", column);
        }
        printf("\n");
    }
}

void Matrix::printMatrixData() {
    printf("Matrix Data:\n");

    printf("Rows: %d, columns %d\n", this->m_rows, this->m_columns);

    printf("Number of free variables: %d\n", this->m_freeVariablesCount);
    printf("Leading variable columns: %d\n", this->m_leadingVariables.size());
    for (int i : this->m_leadingVariables) {
        printf("%d\t", i);
    }
    printf("\n");
}

void Matrix::countFreeVariables() {
    int currentRow = 0;
    this->m_freeVariablesCount = 0;
    bool onLastRow = false;

    for (int currentColumn = 0; currentColumn < this->m_columns; currentColumn++) {
        if (this->m_matrix[currentRow][currentColumn] == 0) {
            this->m_freeVariablesCount++;
            continue;
        } else if (onLastRow && this->m_matrix[currentRow][currentColumn - 1] != 0) {
            this->m_freeVariablesCount++;
            continue;
        }

        if (currentRow < this->m_rows - 1) {
            currentRow++;
        } else {
            onLastRow = true;
        }
    }
}
