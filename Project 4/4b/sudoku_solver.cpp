//
// Created by Jackymora Isa on 4/5/24.
//
#include "sudoku_solver.h"

bool findEmptyCell(board b, int& row, int& col) {
    for (row = 1; row <= BoardSize; row++) {
        for (col = 1; col <= BoardSize; col++) {
            if (b.isBlank(row, col)) {
                return true;
            }
        }
    }
    return false; // No empty cell found
}

bool isValidValue(board b, int row, int col, int value) {
    for (int i = 1; i <= BoardSize; i++) {
        if (b.getCell(row, i) == value || b.getCell(i, col) == value) return false;
    }

    int squareRowStart = ((row - 1) / SquareSize) * SquareSize + 1;
    int squareColStart = ((col - 1) / SquareSize) * SquareSize + 1;

    for (int i = 0; i < SquareSize; i++) {
        for (int j = 0; j < SquareSize; j++) {
            if (b.getCell(squareRowStart + i, squareColStart + j) == value) return false;
        }
    }
    return true; // The value is valid
}

bool solveSudoku(board& b, int& recursiveCallCount) {
    int row, col;

    if (!findEmptyCell(b, row, col)) {
        return true; // Solved
    }

    for (int value = MinValue; value <= MaxValue; value++) {
        if (isValidValue(b, row, col, value)) {
            b.setCell(row, col, value);
            recursiveCallCount++;

            if (solveSudoku(b, recursiveCallCount)) {
                return true; // Solution found
            }

            b.clearCell(row, col); // Backtrack
        }
    }

    return false; // No solution found
}

