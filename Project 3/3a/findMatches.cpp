#include "findMatches.h"

vector<string> findMatches(const Dictionary& dict, const Grid& grid) {
    vector<string> matches;
    vector<char> line;
    int gridDims = grid.letters.size();

    // Horizontal
    for(int r = 0; r < gridDims; r++) {
        for(int c = 0; c < gridDims; c++) {
            line.push_back(grid.letters[r][c]);
        }
    }

    wordSearch(matches, line, dict);
    // Vertical
    for(int c = 0; c < gridDims; c++) {
        for(int r = 0; r < gridDims; r++) {
            line.push_back(grid.letters[c][r]);
        }
    }
    wordSearch(matches, line, dict);
    // Diagonal Left

    // Diagonal Right

}

void wordSearch(vector<string>& matches, vector<char>& row, const Dictionary& dict) {
    /* 
    * Rotate to the right and scan from start of vector for word
    * Repeat for each character at the start
    * Reverse direction and repeat. 
    */
}