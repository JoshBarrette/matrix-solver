#pragma once
#include "types.h"

class Matrix {
private:
    int m_rows = 0;
    int m_columns = 0;
    matrix_t m_matrix;

public:
    void populateFromArray(double** array, int numRows, int numCols);
    void populateFromConstArray();
    void populateFromVector(matrix_t& m);
    void populateFromCSV();

    void multiplyRow(int rowNum, double mult);
    void divideRow(int rowNum, double div);
    void multAndAdd(int targetRowNum, int fromRowNum, double mult);
    void divAndAdd(int targetRowNum, int fromRowNum, double div);

    void reduce();
    void descend();
    void ascend();

    row_t& operator[](int numRow);

    matrix_t& getMatrix();
    row_t& getRow(int rowNum);
    int getRows();
    int getCols();

    void printRow(int numRow);
    void printMatrix();
};
