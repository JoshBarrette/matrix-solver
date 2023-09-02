#include "rowreduce.h"
#include "utils.h"

// TODO: this still doesn't catch some edge cases (free variables)
void descend(double** array) {
    int lastRow = ROWS - 1;
    for (int pivotRow = 0; pivotRow < lastRow; pivotRow++) {
        if (array[pivotRow][pivotRow] != 1.0) {
            divideArrayRow(array, pivotRow, array[pivotRow][pivotRow]);
        }

        for (int targetRow = pivotRow + 1; targetRow < ROWS; targetRow++) {
            double mult = array[targetRow][pivotRow] / array[pivotRow][pivotRow] * -1.0;
            multiplyArrayRowAndAdd(array, pivotRow, targetRow, mult);
        }
    }

    for (int column = COLS - 1; column > 0; column--) {
        if (array[lastRow][column - 1] == 0) {
            divideArrayRow(array, lastRow, array[lastRow][column]);
            return;
        }
    }
}
