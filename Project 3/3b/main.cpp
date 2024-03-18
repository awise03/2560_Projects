#include "dictionary.cpp"
#include "grid.cpp"
#include "findMatches.cpp"
#include "heap.cpp"
#include <iostream>

using namespace std;

void search() {
    int algo;
    string grid_sel;
    Grid grid;
    Dictionary dict;
    dict.readDict("dictionary-2.txt");

    cout << "Type word search grid from the list below (ex. \"input15-2.txt\"): " << 
        "\n\t1. input15-2.txt" <<
        "\n\t2. input30-3.txt" << 
        "\n\t3. input50-1-1.txt\n";
    
    cin >> grid_sel;
    grid.fillGrid(grid_sel);

    cout << "Select Sorting Algorithm: " << 
        "\n\t1. Selection Sort" << 
        "\n\t2. Quick Sort" << 
        "\n\t3. Heap Sort\n";

    cin >> algo;

    grid.printGrid();
    
    switch(algo) {
        case(1):
            dict.selectionSort();
            break;
        case(2): 
            dict.quicksort(0, dict.getDictSize());
            break;
        case(3):
            Heap h1;
            h1.buildMaxHeap(dict.getWords());

        default:
            cout << "Invalid selection. Please try again";
            break;
    }
    
    // Vector of matches found in word search grid
    vector<string> matches = findMatches(dict, grid);
    

    // Print the matches
    cout << endl;
    for(int i = 0; i < matches.size(); i++) {
        cout << matches[i] << "\t" << endl;
    }
}

int main() {
    search();
    return 0;
}

