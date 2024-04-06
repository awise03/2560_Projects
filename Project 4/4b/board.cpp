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
        void updateSpecificConflict(int, int, bool);
        void clearCell(int, int);
        bool findBlank();
        void setCell(int, int, int);
        bool checkSolved();
        bool isValid(int, int, int);
        ValueType getCell(int, int);
        bool solveBoard();
        int getTotalCalls();
    private:
        int recursiveCalls;
        int totalCalls = 0;
        int currRow;
        int currCol;
        // The following matrices go from 1 to BoardSize in each
        // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
        matrix<ValueType> value;
        // Matrices to store conflict in rows, columns, and sqaures
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
    // Iterate through the board and update conflicts
    for(int i = 1; i <= BoardSize; i++) {
        for (int j = 1; j <= BoardSize; j++) {

            int val = getCell(i,j);

            if (val != Blank) {
                // Add conflicts to the respective matrices
                rowConflicts[i][val] = true;
                colConflicts[j][val] = true;
                squareConflicts[squareNumber(i, j)][val] = true;
            }
        }
    }
}

void board::updateSpecificConflict(int r, int c, bool val) {
    rowConflicts[r][c] = val;
    colConflicts[r][c] = val;
    squareConflicts[squareNumber(r, c)][c] = val;
}

void board::printConflicts()
{
    cout << "Row Conflicts:" << endl;
    for (int i = 1; i <= BoardSize; i++) {
        cout << "Row " << i << ": ";
        for(int j = 1; j <= BoardSize; j++) {
            cout << rowConflicts[i][j] << endl;
        }
    }
    cout << endl;

    cout << "Column Conflicts:" << endl;
    for (int i = 1; i <= BoardSize; i++) {
        cout << "Column " << i << ": ";
        for(int j = 1; j <= BoardSize; j++) {
            cout << colConflicts[i][j] << endl;
        }
    }
    cout << endl;
    cout << "Square Conflicts:" << endl;
    for (int sq = 1; sq <= BoardSize; sq++) {
        cout << "Square " << sq << ": ";
        for(int j = 1; j <= BoardSize; j++) {
            cout << rowConflicts[sq][j] << endl;
        }
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

bool board::isValid(int r, int c, int val) {
    if(rowConflicts[r][val]){
        return false;
    }
    if(colConflicts[r][val]){
        return false;
    }
    if(squareConflicts[squareNumber(r, c)][val]) {
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

bool board::findBlank() {
    for(currRow = 1; currRow <= BoardSize; currRow++) {
        for(currCol = 1; currCol <= BoardSize; currCol++) {
            if(isBlank(currRow, currCol)) {
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
    recursiveCalls++;
    totalCalls++;


    if(checkSolved()) {
        cout << "Total Recursive Calls: " << recursiveCalls << endl;
        numSolutions++;
        print();
        return true;
    }
    
    if(findBlank()) {
        for(int val = 1; val <= BoardSize; val++) {
            if(isValid(currRow, currCol, val)) {
                setCell(currRow, currCol, val);
                updateSpecificConflict(currRow, currCol, true);

                if(solveBoard()) {
                    return true;
                }
                else {
                    clearCell(currRow, currCol);
                    updateSpecificConflict(currRow, currCol, false);
                }
            }

        }
    }
    return false;
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
    print(); 
    
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
            b1.solveBoard();
        }
        int total = b1.getTotalCalls();
        cout << "\n Total Recursive Calls: " << total << endl;
        cout << "Average calls = " << double(total/numSolutions) << endl;
        cout << "Number solved = " << numSolutions << endl;
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}