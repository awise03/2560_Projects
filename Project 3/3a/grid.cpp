#include "grid.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Grid::fillGrid(const string& filename) {
    ifstream file(filename);
    if(file.is_open()) {
        file >> rows >> cols;

        letters.resize(rows, vector<char>(cols));

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                file >> letters[i][j];
            }
        }
        file.close();
    } else {
        cout << "Error opening file" << endl;
    }
}

void Grid::printGrid() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << letters[i][j] << " ";
        }
        cout << endl;
    }
}