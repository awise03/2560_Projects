#include "dictionary.cpp"
#include "grid.cpp"
#include "findMatches.cpp"
#include <iostream>

using namespace std;

int main() {
    // int i[] = {0, 1, 2, 3, 4, 5};
    // cout << sizeof(i)/sizeof(i[0]);

    Dictionary dict;
    dict.readDict("dictionary-2.txt");
    dict.selectionSort();
    //dict.printDict();
    
    Grid grid;
    grid.fillGrid("input15-2.txt");
    grid.printGrid();

    vector<string> matches = findMatches(dict, grid);

    for(int i = 0; i < matches.size(); i++) {
        cout << matches[i] << endl;
    }
    return 0;
}

