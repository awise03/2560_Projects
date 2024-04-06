//
// Created by Jackymora Isa on 4/5/24.
//
#include "sudoku_solver.h"

bool findEmptyCell(const board& b, int& row, int& col)
{
    // Iterate through the board and find the first empty cell
    for(row = 1; row <= BoardSize; row++)
    {
        for(col = 1; col <= BoardSize; col++)
        {
            if(b.isBlank(row, col))
            {
                return true;
            }
        }
    }

    // If no empty cell is found, return false
    row = col = 0;
    return false;
}

bool isValidValue(const board& b, int row, int col, int value)
{
    // Check if the value is already present in the same row, column, or square
    for(int i = 1; i <= BoardSize; i++)
    {
        if(b.getCell(row, i) == value || b.getCell(i, col) == value)
        {
            return false;
        }
    }

    // Check the square
    int squareRow = (row - 1)/ SquareSize;
    int squareCol = (col - 1)/ SquareSize;

    for(int i = squareRow * SquareSize + 1; i <= (squareRow +1) * SquareSize; i++)
    {
        for(int j = squareCol * SquareSize + 1; j <= (squareCol + 1) * SquareSize; j++)
        {
            if(b.getCell(i,j) == value)
            {
                return false;
            }
        }
    }

    // If the value is valid, return true
    return true;
}

bool solveSudoku(board& b, int& recursiveCallCount)
{
    int row, col;

    // Base case: If no empty cell is found, the board is solved
    if(!findEmptyCell(b, row, col))
    {
        return true;
    }

    // Try all possible values for the empty cell
    for(int value = MinValue; value <= MaxValue; value++)
    {
        recursiveCallCount++;

        // If the value is valid for the cell, assign it and recursively solve the board
        if(isValidValue(b, row, col, value))
        {
            b.setCell(row, col, value);

            if (solveSudoku(b, recursiveCallCount))
            {
                return true;
            }
        }
    }

    // If no value leads to a solution, return false
    return false;
}
