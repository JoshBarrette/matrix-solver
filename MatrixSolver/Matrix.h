#pragma once

#include <string>
#include "types.h"

class Matrix
{
public:
    int m_rows = 0;
    int m_columns = 0;
    matrix_t m_matrix;

    void populateFromArray(double **array, int numRows, int numCols);
    void populateFromConstArray();
    void populateFromVector(matrix_t &m);
    void populateFromCSV(std::string fileName);

    void multiplyRow(int rowNum, double mult);
    void divideRow(int rowNum, double div);
    void multAndAdd(int targetRowNum, int fromRowNum, double mult);
    void divAndAdd(int targetRowNum, int fromRowNum, double div);

    void rowReduce();
    void descend();
    void ascend();

    bool lookForSwap(int startingRow, int column);
    void swapRows(int rowNum1, int rowNum2);

    row_t &operator[](int numRow);

    void printRow(int numRow);
    void printMatrix();
};
