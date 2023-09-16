#pragma once
#include "types.h"

class Matrix {
private:
    int m_rows;
    int m_columns;
    matrix_t m_matrix;

public:
    Matrix();

    matrix_t getMatrix();
    int getRows();
    int getCols();
    void populateFromArray(double** array, int numRows, int numCols);
    void populateFromVector(matrix_t m);
    void populateFromCSV();

    void multiplyRow(int row, double mult);
    void divideRow(int row, double div);

    void multAndAdd(int targetRow, int fromRow, double mult);
    void divAndAdd(int targetRow, int fromRow, double div);

    void printRow(int numRow);
    void printMatrix();
};
