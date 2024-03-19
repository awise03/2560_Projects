//
// Created by Alexander Wise and Jackymora Isa on 3/6/24.
//

#include "dictionary.cpp"
#include "grid.cpp"
#include "findMatches.cpp"
#include <iostream>

using namespace std;

int main() {
    // Dictionary object
    Dictionary dict;
    // Pass dictionary file to dictionary object
    dict.readDict("dictionary-2.txt");
    // Sort dictionary using selection sort
    dict.selectionSort();
    
    // Grid object
    Grid grid;
    // Pass grid file to grid object
    grid.fillGrid("input15-2.txt");
    // Print grid 
    grid.printGrid();

    // Vector of matches found in word search grid
    vector<string> matches = findMatches(dict, grid);

    // Print the matches
    for(int i = 0; i < matches.size(); i++) {
        cout << matches[i] << endl;
    }
    return 0;
}

