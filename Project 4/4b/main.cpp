//
// Created by Jackymora Isa on 4/5/24.
//
#include "sudoku_solver.h"
#include <fstream>
#include <iostream>
#include <iomanip>

int main()
{
    // ... (open the sudoku.txt file and read the boards)

    while (fin && fin.peek() != 'Z')
    {
        board b1(SquareSize);
        b1.initialize(fin);

        int recursiveCallCount = 0;
        if(solveSudoku(b1, recursiveCallCount))
        {
            cout << "Solved board:" << endl;
            b1.print();
            cout << "Recursive calls made: " << recursiveCallCount << endl;
            // Update the total recursive call count and other statistics
        }
        else
        {
            cout << "Unable to solve the board." << endl;
        }
    }

    // ... (print the average and total number of recursive calls)
}
