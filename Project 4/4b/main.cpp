//
// Created by Jackymora Isa on 4/5/24.
//
#include "sudoku_solver.h"
#include <fstream>
#include <iostream>
#include <iomanip>

int main()
{
   ifstream fin("sudoku.txt");
   if(!fin)
   {
       cerr << "Error opening sudoku.txt" << endl;
       return 1;
   }
   int totalRecursiveCalls = 0;
   int totalBoards = 0;

    while (fin && fin.peek() != 'Z')
    {
        // Initialize a board object with the puzzle
        board b1(SquareSize);
        b1.initialize(fin);

        // Solve the Sudoku puzzle
        int recursiveCallCount = 0;
        if(solveSudoku(b1, recursiveCallCount))
        {
            cout << "Solved board:" << endl;
            b1.print();
            cout << "Recursive calls made: " << recursiveCallCount << endl;

            // Update statistics
            totalRecursiveCalls += recursiveCallCount;
            totalBoards++;
        }
        else
        {
            cout << "Unable to solve the board." << endl;
        }
    }

    // Print the average and total number of recursive calls
    if(totalBoards > 0)
    {
        double averageRecursiveCalls = static_cast<double>(totalRecursiveCalls) / totalBoards;
        cout << fixed << setprecision(2);
        cout << "Total boards solved: " << totalBoards << endl;
        cout << "Total recursive calls made: " << totalRecursiveCalls << endl;
        cout << "Average recursive calls per board: " << averageRecursiveCalls << endl;
    }
    else
    {
        cout << "No Sudoku puzzles were solved." << endl;
    }

    return 0;
}
