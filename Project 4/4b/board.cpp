#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;
typedef int ValueType; // The type of the value in a cell
const int Blank = -1; // Indicates that a cell is blank
const int SquareSize = 3; // The number of cells in a small square
// (usually 3). The board has
// SquareSize^2 rows and SquareSize^2
// columns.
const int BoardSize = SquareSize * SquareSize;
const int MinValue = 1;
const int MaxValue = 9;
int numSolutions = 0;

// Stores the entire Sudoku board
class board
{
    public:
        board(int);
        void clear();
        void initialize(ifstream &fin);
        void print();
        bool isBlank(int, int);
        void printConflicts();
        void updateConflicts();
        void clearCell(int, int);
        void setCell(int, int, int);
        bool checkSolved();
        ValueType getCell(int, int);
    private:
        // The following matrices go from 1 to BoardSize in each
        // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
        matrix<ValueType> value;
        // Matrices to store conflict in rows, columns, and sqaures
        matrix<vector<int> > rowConflicts;
        matrix<vector<int> > colConflicts;
        matrix<vector<int> > squareConflicts;
};

board::board(int sqSize)
    : value(BoardSize+1,BoardSize+1),
      rowConflicts(BoardSize + 1, BoardSize + 1),
      colConflicts(BoardSize + 1, BoardSize + 1),
      squareConflicts(BoardSize + 1, BoardSize + 1)// Board constructor
{
    clear();
}

void board::clear() // Mark all possible values as legal for each board entry
{
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            value[i][j] = Blank;
            rowConflicts[i][j].clear();
            colConflicts[i][j].clear();
            squareConflicts[i][j].clear();
        }
    }

}

void board::initialize(ifstream &fin) // Read a Sudoku board from the input file.
{
    char ch;

    clear();

    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
        {
        fin >> ch;
        // If the read char is not Blank
        if (ch != '.')
            setCell(i,j,ch-'0'); // Convert char to int
        }

    updateConflicts();    
}

// Return the square number of cell i,j (counting from left to right,
// top to bottom. Note that i and j each go from 1 to BoardSize
int squareNumber(int i, int j)
{
    // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
    // coordinates of the square that i,j is in.
    return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

void board::updateConflicts()
{
    // Clear all conflicts first
    for(int i = 1; i <= BoardSize; i++)
    {
        for(int j = 1; j <= BoardSize; j++)
        {
            rowConflicts[i][j].clear();
            colConflicts[i][j].clear();
            squareConflicts[i][j].clear();
        }
    }

    // Iterate through the board and update conflicts
    for(int i = 1; i <= BoardSize; i++) {
        for (int j = 1; j <= BoardSize; j++) {
            int val = value[i][j];
            if (val != Blank) {
                // Add conflicts to the respective matrices
                rowConflicts[i][val].push_back(j);
                colConflicts[j][val].push_back(i);
                squareConflicts[squareNumber(i, j)][val].push_back(i * BoardSize + j);
            }
        }
    }
}

void board::printConflicts()
{
    cout << "Row Conflicts:" << endl;
    for (int i = 1; i <= BoardSize; i++) {
        cout << "Row " << i << ": ";
        for (int val = MinValue; val <= MaxValue; val++) {
            // Iterate over possible values (1 to 9)
            cout << val << ": ";
            for (const int& j : rowConflicts[i][val]) {
                // Print conflicting column indices for this row and value
                cout << j << " ";
            }
            cout << "| ";
        }
        cout << endl;
    }

    cout << "Column Conflicts:" << endl;
    for (int j = 1; j <= BoardSize; j++) {
        cout << "Column " << j << ": ";
        for (int val = MinValue; val <= MaxValue; val++) {
            // Iterate over possible values (1 to 9)
            cout << val << ": ";
            for (const int& i : colConflicts[j][val]) {
                // Print conflicting row indices for this column and value
                cout << i << " ";
            }
            cout << "| ";
        }
        cout << endl;
    }

    cout << "Square Conflicts:" << endl;
    for (int sq = 1; sq <= BoardSize; sq++) {
        cout << "Square " << sq << ": ";
        for (int val = MinValue; val <= MaxValue; val++) {
            // Iterate over possible values (1 to 9)
            cout << val << ": ";
            for (const int& cell : squareConflicts[sq][val]) {
                // Print conflicting cell indices for this square and value
                int i = cell / BoardSize + 1; // Convert cell index to row index
                int j = cell % BoardSize; // Convert cell index to column index
                if (j == 0) {
                    j = BoardSize;
                    i--;
                }
                cout << "(" << i << "," << j << ") ";
            }
            cout << "| ";
        }
        cout << endl;
    }
}



// Sets the cell at the given index to the given value
void board::setCell(int i, int j, int val) {
    value[i][j] = val;
    updateConflicts();
}

void board::clearCell(int i, int j) {
    value[i][j] = Blank;
    updateConflicts();
}


ostream &operator<<(ostream &ostr, vector<int> &v) // Overloaded output operator for vector class.
{
    for (int i = 0; i < v.size(); i++)
        ostr << v[i] << " ";
    cout << endl;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell. Throws an exception
// if bad values are passed.
{
    if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
        return value[i][j];
    else
        throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
    if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
        throw rangeError("bad value in setCell");
    return (getCell(i,j) == Blank);
}

void board::print()
// Prints the current board.
{
    for (int i = 1; i <= BoardSize; i++)
    {
        if ((i-1) % SquareSize == 0)
        {
            cout << " -";
	        for (int j = 1; j <= BoardSize; j++)
	            cout << "---";
            cout << "-";
	        cout << endl;
        }
        for (int j = 1; j <= BoardSize; j++)
        {
	        if ((j-1) % SquareSize == 0)
	            cout << "|";
            if (!isBlank(i,j))
                cout << " " << getCell(i,j) << " ";
        else
            cout << "   ";
        }
        cout << "|";
        cout << endl;
    }

    cout << " -";
    for (int j = 1; j <= BoardSize; j++)
        cout << "---";
    cout << "-";
    cout << endl;
    printConflicts();
}

bool board::checkSolved() {
    updateConflicts();

    for(int i = 0; i <= BoardSize; i++) {
        for(int j = 0; j <= BoardSize; j++) {
            if(isBlank(i, j)) {
                return false;
            }
        }
    }

    return true;
}

int main()
    {
    ifstream fin;
    // Read the sample grid from the file.
    string fileName = "sudoku.txt";
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    try
    {
        board b1(SquareSize);

        while (fin && fin.peek() != 'Z')
        {
            b1.initialize(fin);
            b1.print();
            b1.printConflicts();
        }
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}
