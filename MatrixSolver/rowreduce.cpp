#include "rowreduce.h"
#include "utils.h"

void rowreduce::rowReduce(double** array) {
    descend(array);
}

void rowreduce::descend(double** array) {
    int lastRow = utils::ROWS - 1;
    int currentColumn = 0;

    for (int pivotRow = 0; pivotRow < lastRow; pivotRow++) {
        double currentNum = array[pivotRow][pivotRow];
        for (int findNonZero = currentColumn; currentColumn < utils::COLS; findNonZero++) {
            if (array[pivotRow + 1][findNonZero] == 0) {
                currentColumn++;
            } else {
                break;
            }
        }

        if (array[pivotRow][currentColumn] != 1) {
            utils::divideArrayRow(array, pivotRow, array[pivotRow][currentColumn]);
        }

        for (int targetRow = pivotRow + 1; targetRow < utils::ROWS; targetRow++) {
            double mult = array[targetRow][currentColumn] / currentNum * -1.0;
            utils::multiplyArrayRowAndAdd(array, currentColumn, targetRow, mult);
        }

        currentColumn++;
    }

    for (int column = utils::COLS - 1; column > 0; column--) {
        if (array[lastRow][column - 1] == 0) {
            utils::divideArrayRow(array, lastRow, array[lastRow][column]);
            return; // this does NOT work...
        }
    }
}
