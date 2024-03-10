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

