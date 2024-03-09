#include "grid.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Fills grid with characters from file
void Grid::fillGrid(const string& filename) {
    // Creates file object from filename
    ifstream file(filename);
    if(file.is_open()) {
        // Reads the first two sets of ints as the # of rows and columns
        file >> rows >> cols;

        // Resizes the 2d vector to the number of rows and columns
        letters.resize(rows, vector<char>(cols));

        // Iterates through each character
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                // Reads the next character in the grid and stores it in the vector
                file >> letters[i][j];
            }
        }
        // Closes the file after completion
        file.close();
    } else {
        cout << "Error opening file" << endl;
    }
}

// Prints the grid to the console
void Grid::printGrid() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << letters[i][j] << " ";
        }
        cout << endl;
    }
}