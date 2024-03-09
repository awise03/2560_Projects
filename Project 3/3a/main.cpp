#include "dictionary.cpp"
#include "grid.cpp"
#include <iostream>

using namespace std;

int main() {
    Dictionary dict;
    dict.readDict("dictionary-2.txt");
    dict.selectionSort();
    dict.printDict();
    
    Grid grid;
    grid.fillGrid("input50-1-1.txt");
    grid.printGrid();

    findMatches(dict, grid);

    return 0;
}

void findMatches(const Dictionary& dict, const Grid& grid) {
    // Vertical Up

    // Vertical Down

    // Horizontal Left

    // Horizontal Right
    
    // Diagonal Up Right

    // Diagonal Down Right

    // Diagonal Up Left

    // Diagonal Down Left


}