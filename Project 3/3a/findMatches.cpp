#include "findMatches.h"
#include "grid.h"
#include "dictionary.h"

vector<string> findMatches(const Dictionary& dictionary, const Grid& grid) {
    int dim = grid.letters.size();
    vector<string> matches;

    for(int r = 0; r < dim; r++) {
        for(int c = 0; c < dim; c++) {
            for(int op = 0; op < 8; op ++) {
                searchWord(dictionary, grid, r, c, op, matches);
            }
        }
    }
    return matches;
}

void searchWord(const Dictionary& dictionary, const Grid& grid, int r, int c, int op, vector<string>& matches) {
    int dir_r[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    int dir_c[] = {0, 0, -1, 1, 1, 1, -1, -1};

    int s_r = r;
    int s_c = c;
    int dims = grid.letters.size();

    string search_word = "";

    for(int i = 0; i < 5; i++) {
        s_r += dir_r[op];
        s_c += dir_c[op];
        checkRollOver(s_r, s_c, dims, op);

        search_word += grid.letters[s_r][s_c];
    }

    while(search_word.length() <= dims) {
        if (dictionary.binarySearch(search_word) != -1) {
            matches.push_back(search_word);
            cout << "\n Word Found: " << search_word;
        }

        s_r += dir_r[op];
        s_c += dir_c[op];
        checkRollOver(s_r, s_c, dims, op);
        
        search_word += grid.letters[s_r][s_c];
    }
}

void checkRollOver(int &r1, int &c1, int dims, int direction) {
    //cout << "\nBefore Roll Over Adjustment: " <<" r1: " << r1 << " c1: " << c1;
    // Diagonal Roll Overs
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

         //cout << "\nAfter Roll Over Adjustment: " <<" r1: " << r1 << " c1: " << c1;
    }

}