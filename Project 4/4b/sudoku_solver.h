//
// Created by Jackymora Isa on 4/5/24.
//

#ifndef INC_2560_PROJECTS_SUDOKU_SOLVER_H
#define INC_2560_PROJECTS_SUDOKU_SOLVER_H

#include "board.cpp"

// Helper function to find the next empty cell on the board
bool findEmptyCell(const board& b, int& row, int& col);

// Helper function to check if a value is valid for a given cell
bool isValidValue(const board& b, int row, int col, int value);

// Recursive function to solve the puzzle
bool solveSudoku(board& b, int& recursiveCallCount);


#endif //INC_2560_PROJECTS_SUDOKU_SOLVER_H
