#pragma once

#include <string>
#include <vector>
#include "types.h"

class Matrix
{
public:
    int m_rows = 0;
    int m_columns = 0;
    matrix_t m_matrix;
    int m_freeVariables;

    void populateFromArray(double **array, int numRows, int numCols);
    void populateFromConstArray();
    void populateFromVector(matrix_t &m);
    void populateFromCSV(std::string fileName);

    std::vector<std::string> solve();
    void findBasisForNullSpace();
    void findBasisForKernel();

    void rowReduce();
    void descend();
    bool lookForSwap(int startingRow, int column);
    void swapRows(int rowNum1, int rowNum2);
    void ascend();    

    void multiplyRow(int rowNum, double mult);
    void divideRow(int rowNum, double div);
    void multAndAdd(int targetRowNum, int fromRowNum, double mult);
    void divAndAdd(int targetRowNum, int fromRowNum, double div);

    void transposeMatrix();
    void transposeSquareMatrix();
    void transposeRectangularMatrix();

    void multiplyMatrixByVector(std::vector<double> vec);
    void multiplyMatrixByMatrix(matrix_t m);

    row_t &operator[](int numRow);

    void printRow(int numRow);
    void printMatrix();
    void printMatrixData();

private:
    // Added what this function does to ascend()
    void countFreeVariables();
};
