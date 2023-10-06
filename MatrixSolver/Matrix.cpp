#include "Matrix.h"
#include "utils.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

void Matrix::populateFromArray(double **array, int numRows, int numCols)
{
    this->m_matrix.clear();
    this->m_rows = numRows;
    this->m_columns = numCols;

    for (int row = 0; row < numRows; row++)
    {
        row_t currentRow;
        for (int col = 0; col < numCols; col++)
        {
            currentRow.push_back(array[row][col]);
        }
        this->m_matrix.push_back(currentRow);
    }
}

void Matrix::populateFromConstArray()
{
    this->m_rows = utils::ROWS;
    this->m_columns = utils::COLS;

    for (int i = 0; i < this->m_rows; i++)
    {
        row_t row;
        for (int j = 0; j < this->m_columns; j++)
        {
            row.push_back(utils::CONST_MATRIX[i][j]);
        }
        this->m_matrix.push_back(row);
    }
}

void Matrix::populateFromVector(matrix_t &m)
{
    this->m_matrix = m;
    this->m_rows = m.size();
    if (this->m_rows > 0)
    {
        this->m_columns = m[0].size();
    }
    else
    {
        this->m_columns = 0;
    }
}

void Matrix::populateFromCSV(std::string fileName)
{
    this->m_columns = 0;
    this->m_rows = 0;
    this->m_matrix.clear();

    std::ifstream fileStream(fileName);
    std::string line;

    while (std::getline(fileStream, line))
    {
        row_t currentRow;
        std::istringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ','))
        {
            double value = std::stod(cell);
            currentRow.push_back(value);
            this->m_columns++;
        }

        this->m_matrix.push_back(currentRow);
        this->m_rows++;
    }

    this->m_columns = this->m_columns / this->m_rows;
}

void Matrix::rowReduce()
{
    this->descend();
    this->ascend();
}

void Matrix::descend()
{
    int lastRow = this->m_rows - 1;
    int currentColumn = 0;

    for (int pivotRow = 0; pivotRow < lastRow && currentColumn < this->m_columns; pivotRow++)
    {
        bool shouldContinue = false;
        if (this->m_matrix[pivotRow][pivotRow] == 0)
        {
            shouldContinue = lookForSwap(pivotRow, currentColumn);
        }

        if (shouldContinue)
        {
            currentColumn++;
            continue;
        }

        if (this->m_matrix[pivotRow][currentColumn] != 1)
        {
            this->divideRow(pivotRow, this->m_matrix[pivotRow][currentColumn]);
        }

        for (int targetRow = pivotRow + 1; targetRow < this->m_rows; targetRow++)
        {
            double mult = this->m_matrix[targetRow][currentColumn] * -1.0;
            this->multAndAdd(targetRow, pivotRow, mult);
        }

        currentColumn++;
    }

    for (int column = this->m_columns - 1; column > 0; column--)
    {
        if (this->m_matrix[lastRow][column - 1] == 0)
        {
            this->divideRow(lastRow, this->m_matrix[lastRow][column]);
            return;
        }
    }
}

bool Matrix::lookForSwap(int startingRow, int column)
{
    for (int row = startingRow + 1; row < this->m_rows; row++)
    {
        if (this->m_matrix[row][column] != 0)
        {
            this->swapRows(startingRow, row);
            return false;
        }
    }

    return true;
}

void Matrix::swapRows(int rowNum1, int rowNum2)
{
    row_t temp = this->m_matrix[rowNum1];
    this->m_matrix[rowNum1] = this->m_matrix[rowNum2];
    this->m_matrix[rowNum2] = temp;
}

void Matrix::ascend()
{
    int currentColumn;

    for (int currentRow = this->m_rows - 1; currentRow > 0; currentRow--)
    {
        for (currentColumn = 0; currentColumn < this->m_columns; currentColumn++)
        {
            if (this->m_matrix[currentRow][currentColumn] == 0)
            {
                continue;
            }

            for (int risingRow = currentRow - 1; risingRow >= 0; risingRow--)
            {
                double mult = -1.0 * this->m_matrix[risingRow][currentColumn];
                this->multAndAdd(risingRow, currentRow, mult);
                // printf("currentRow: %d, currentColumn: %d, risingRow: %d, mult: %f\n",
                //        currentRow, currentColumn, risingRow, mult);
            }
            break;
        }

        if (currentColumn == 0)
        {
            return;
        }
    }
}

inline row_t &Matrix::operator[](int numRow)
{
    return this->m_matrix[numRow];
}

void Matrix::multiplyRow(int rowNum, double mult)
{
    row_t &row = this->m_matrix[rowNum];
    for (int i = 0; i < this->m_columns; i++)
    {
        if (row[i] != 0)
        {
            row[i] = row[i] * mult;
        }
    }
}

void Matrix::divideRow(int rowNum, double div)
{
    row_t &row = this->m_matrix[rowNum];
    for (int i = 0; i < this->m_columns; i++)
    {
        if (row[i] != 0)
        {
            row[i] = row[i] / div;
        }
    }
}

void Matrix::multAndAdd(int targetRowNum, int fromRowNum, double mult)
{
    row_t &fromRow = this->m_matrix[fromRowNum];
    row_t &targetRow = this->m_matrix[targetRowNum];
    for (int i = 0; i < this->m_columns; i++)
    {
        targetRow[i] += fromRow[i] * mult;
    }
}

void Matrix::divAndAdd(int targetRowNum, int fromRowNum, double div)
{
    row_t &fromRow = this->m_matrix[fromRowNum];
    row_t &targetRow = this->m_matrix[targetRowNum];
    for (int i = 0; i < this->m_columns; i++)
    {
        targetRow[i] += fromRow[i] / div;
    }
}

void Matrix::multiplyMatrixByVector(std::vector<double> vec)
{
    int vecLength = vec.size();

    if (vecLength != this->m_columns)
    {
        printf("Incompatible vector size.\n");
        return;
    }

    matrix_t newMatrix;
    for (int currentRow = 0; currentRow < this->m_rows; currentRow++)
    {
        row_t newRow;
        newRow.push_back(0);
        for (int currentColumn = 0; currentColumn < this->m_columns; currentColumn++)
        {
            newRow[0] += this->m_matrix[currentRow][currentColumn] * vec[currentColumn];
        }
        newMatrix.push_back(newRow);
    }

    this->m_matrix = newMatrix;
    this->m_columns = 1;
}

void Matrix::multiplyMatrixByMatrix(matrix_t m)
{
    int multRows = m.size();
    // possible out of bounds error (good thing this is just a personal project)
    int multColumns = m[0].size();

    if (multRows != this->m_columns || multColumns != this->m_rows)
    {
        printf("Incompatible matrix sizes.\n");
        return;
    }

    matrix_t newMatrix;
    for (int currentVector = 0; currentVector < multColumns; currentVector++)
    {
        for (int currentRow = 0; currentRow < this->m_rows; currentRow++)
        {
            row_t row;
            if (currentVector != 0)
            {
                row = newMatrix[currentRow];
            }
            row.push_back(0);

            for (int currentColumn = 0; currentColumn < this->m_columns; currentColumn++)
            {
                row[currentVector] += this->m_matrix[currentRow][currentColumn] * m[currentColumn][currentVector];
            }

            if (currentVector == 0)
            {
                newMatrix.push_back(row);
            }
            else
            {
                newMatrix[currentRow] = row;
            }
        }
    }

    this->m_matrix = newMatrix;
    this->m_rows = multColumns;
    this->m_columns = multColumns;
}

void Matrix::printRow(int numRow)
{
    for (double column : m_matrix[numRow])
    {
        printf("%7.1f", column);
    }
    printf("\n");
}

void Matrix::printMatrix()
{
    for (row_t row : this->m_matrix)
    {
        for (double column : row)
        {
            printf("%7.1f", column);
        }
        printf("\n");
    }
}
