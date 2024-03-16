#include "findMatches.h"
#include "grid.h"
#include "dictionary.h"

vector<string> findMatches(const Dictionary& dictionary, const Grid& grid) {
    // Variable for the dimensions of the grid
    int dim = grid.letters.size();
    // Vector for words found in the word search
    vector<string> matches;
    
    // Iterates through each character in the grid
    for(int r = 0; r < dim; r++) {
        for(int c = 0; c < dim; c++) {
            // Does each of the 8 directional operations
            for(int op = 0; op < 8; op ++) {
                searchWord(dictionary, grid, r, c, op, matches);
            }
        }
    }
    // Return vector of matches
    return matches;
}

// Function to search for the word based on directional operation, and initial character
void searchWord(const Dictionary& dictionary, const Grid& grid, int r, int c, int op, vector<string>& matches) {
    // Array of directional operations
    int dir_r[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    int dir_c[] = {0, 0, -1, 1, 1, 1, -1, -1};

    // Initialize variables
    int s_r = r;
    int s_c = c;
    int dims = grid.letters.size();

    // Empty string to be filled with characters to form words
    string search_word = "";

    // Create a word using the first 5 characters
    for(int i = 0; i < 5; i++) {
        s_r += dir_r[op];
        s_c += dir_c[op];
        // Check to see if there is a rollover on the grid to the other side
        checkRollOver(s_r, s_c, dims, op);

        search_word += grid.letters[s_r][s_c];
    }
    // Keep adding characters until we reach a word = to the dimensions of the grid
    while(search_word.length() <= dims) {
        // Binary search for the current word made from the characters
        // Add word to the matches vector if it exists
        if (dictionary.binarySearch(search_word) != -1) {
            matches.push_back(search_word);
            //cout << "\n Word Found: " << search_word;
        }

        // Change current position based on operation passed to function
        s_r += dir_r[op];
        s_c += dir_c[op];
        checkRollOver(s_r, s_c, dims, op);
        
        // Add character to the search word
        search_word += grid.letters[s_r][s_c];
    }
}

// Function to check for a character rollover to the other side of the grid
void checkRollOver(int &r1, int &c1, int dims, int direction) {
    dims -= 1;

    // Moving up and right
    if(direction == 4 && c1 > dims){
        int temp = r1 + 1;
        r1 = c1 - 1;
        c1 = temp;
       
    } 
    // Moving down and left
    else if(direction == 7 && c1 < 0) {
        int temp = r1 - 1;
        r1 = c1 + 1;
        c1 = temp;
    } 
    // Moving Down and Right
    else if (direction == 6) {
        if(r1 < 0) {
            c1 += 1;
            r1 = dims - c1;
            c1 = dims;
        } else if(c1 < 0) {
            r1 += 1;
            c1 = dims - r1;
            r1 = dims;
        }
    // Moving Up and Left    
    } else if (direction == 5) {
        if(r1 > dims) {
            c1 -= 1;
            r1 = dims - c1;
            c1 = 0;
        } else if (c1 > dims) {
            r1 -= 1;
            c1 = dims - r1;
            r1 = 0;
        }
    }
    else{
        // Vertical roll over:
        if(r1 < 0) {
            r1 = dims;
        } else if (r1 > dims) {
            r1 = 0;
        }

        // Horizontal Roll Over:
        if (c1 < 0) {
            c1 = dims;
        } else if (c1 > dims) {
            c1 = 0;
        }
    }
}