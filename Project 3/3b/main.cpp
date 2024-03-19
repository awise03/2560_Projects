//
// Created by Alexander Wise and Jackymora Isa on 3/17/24.
//

#include "dictionary.cpp"
#include "grid.cpp"
#include "findMatches.cpp"
#include "heap.cpp"
#include <iostream>

using namespace std;

void search() {
    // Initialize variables and objects
    int algo, grid_sel;
    Grid grid;
    Dictionary dict;

    // Reads in the unsorted dictionary
    dict.readDict("dictionary-2.txt");

    // Prompts user to select word search grid 
    cout << "Select word search grid from the list below: " << 
        "\n\t1. input15-2.txt" <<
        "\n\t2. input30-3.txt" << 
        "\n\t3. input50-1-1.txt\n";

    cin >> grid_sel;
    // Switch statement to apply the grid selection 
    switch(grid_sel) {
        case 1:
            grid.fillGrid("input15-2.txt");
            break;
        case 2:
            grid.fillGrid("input30-3.txt");
            break;
        case 3:
            grid.fillGrid("input50-1-1.txt");
            break;
        default:
            cout << "Invalid selection. Please try again." << endl;
            return;
        
    }
    // Prompts user to select sorting algorithm 
    cout << "Select Sorting Algorithm: " << 
        "\n\t1. Selection Sort" << 
        "\n\t2. Quick Sort" << 
        "\n\t3. Heap Sort\n";

    cin >> algo;
    // Prints grid 
    grid.printGrid();
    // Applies sorting algorithm 
    switch(algo) {
        case(1):
            dict.selectionSort();
            break;
        case(2): 
            dict.quicksort(0, dict.getDictSize());
            break;
        case(3):
            dict.heapsort();
            break;
        default:
            cout << "Invalid selection. Please try again";
            return;
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

