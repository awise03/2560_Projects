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
    void updateSpecificConflict(int, int, int, bool);
    void clearCell(int &, int &);
    bool findBlank(int& r, int& c);
    void setCell(int, int, int);
    bool checkSolved();
    bool isValid(int, int, int);
    ValueType getCell(int, int);
    bool solveBoard();
    int getTotalCalls();
private:
    int recursiveCalls = 0;
    int totalCalls = 0;
    int currRow;
    int currCol;
    // The following matrices go from 1 to BoardSize in each
    // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
    matrix<ValueType> value;
    // Matrices to store conflict in rows, columns, and squares
    matrix<bool> rowConflicts;
    matrix<bool> colConflicts;
    matrix<bool> squareConflicts;
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
            setCell(i, j, Blank);
            rowConflicts[i][j] = false;
            colConflicts[i][j] = false;
            squareConflicts[i][j] = false;
        }
    }
    currRow = 1;
    currCol = 1;
    recursiveCalls = 0;
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
    recursiveCalls = 0;
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

void board::updateConflicts() {
    // Reset conflicts before updating
    for (int i = 1; i <= BoardSize; i++) {
        for (int j = 1; j <= MaxValue; j++) {
            int sqNum = squareNumber(i, j);
            rowConflicts[i][j] = colConflicts[i][j] = squareConflicts[i][j] = false;
        }
    }

    // Iterate through the board to update conflicts based on current board state
    for (int r = 1; r <= BoardSize; r++) {
        for (int c = 1; c <= BoardSize; c++) {
            int val = getCell(r, c);
            if (val != Blank) {
                rowConflicts[r][val] = true;
                colConflicts[c][val] = true;
                int sqNum = squareNumber(r, c);
                squareConflicts[sqNum][val] = true;
            }
        }
    }
}

void board::updateSpecificConflict(int r, int c, int val, bool state) {
    rowConflicts[r][val] = state;
    colConflicts[c][val] = state;
    int sqNum = squareNumber(r, c);
    squareConflicts[sqNum][val] = state;
}

void board::printConflicts()
{
    cout << "Row Conflicts:" << endl;
    for (int i = 1; i <= BoardSize; i++) {
        cout << "Row " << i << ": ";
        for(int j = 1; j <= BoardSize; j++) {
            cout << rowConflicts[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Column Conflicts:" << endl;
    for (int i = 1; i <= BoardSize; i++) {
        cout << "Column " << i << ": ";
        for(int j = 1; j <= BoardSize; j++) {
            cout << colConflicts[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Square Conflicts:" << endl;
    for (int sq = 1; sq <= BoardSize; sq++) {
        cout << "Square " << sq << ": ";
        for(int j = 1; j <= BoardSize; j++) {
            cout << squareConflicts[sq][j] << " ";
        }
        cout << endl;
    }
}

// Sets the cell at the given index to the given value
void board::setCell(int i, int j, int val) {
    value[i][j] = val;
    updateConflicts();
}

void board::clearCell(int &i, int &j) {
    value[i][j] = Blank;
    updateConflicts();
    currRow = 1;
    currCol = 1;
}

bool board::isValid(int row, int col, int val) {
    if (rowConflicts[row][val] || colConflicts[col][val] || squareConflicts[squareNumber(row, col)][val]) {
        return false;
    }
    return true;
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

bool board::findBlank(int& row, int& col) {
    for (row = currRow; row <= BoardSize; row++) {
        for (col = (row == currRow) ? currCol : 1; col <= BoardSize; col++) {
            if (isBlank(row, col)) {
                currRow = row;
                currCol = col;
                return true;
            }
        }
    }
    return false;
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
    //printConflicts();
}

bool board::solveBoard() {
    totalCalls++; // Update this to track the total number of calls

    if (checkSolved()) {
        numSolutions++; // Increment numSolutions if a solution is found
        print();
        return true;
    }

    int row, col;
    if (!findBlank(row, col)) {
        numSolutions++; // Increment numSolutions if a solution is found
        print();
        return true; // If no blank cell is found, the board is solved.
    }

    for (int val = MinValue; val <= MaxValue; val++) {
        if (isValid(row, col, val)) {
            setCell(row, col, val);
            if (solveBoard()) {
                return true;
            }
            clearCell(row, col); // Reset cell on backtrack
        }
    }

    return false; // Trigger backtracking
}


bool board::checkSolved() {
    updateConflicts();

    for(int i = 1; i <= BoardSize; i++) {
        for(int j = 1; j <= BoardSize; j++) {
            if(isBlank(i, j)) {
                return false;
            }
        }
    }

    return true;
}

int board::getTotalCalls() {
    return totalCalls;
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
            if(b1.solveBoard()) {
                cout << "Solution found:\n";
                // b1.print();
            }
        }
        int total = b1.getTotalCalls();
        cout << "\nTotal Recursive Calls: " << total << endl;
        cout << "Average calls = " << (numSolutions ? double(total) / numSolutions : 0) << endl;
        cout << "Number solved = " << numSolutions << endl;
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}
