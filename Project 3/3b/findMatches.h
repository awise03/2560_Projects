#include <vector>
#include <iostream>


#ifndef FINDMATCHES

#define FINDMATCHES

vector<string> findMatches(const Dictionary& dict, const Grid& grid);

void searchWord(const Dictionary& dictionary, const Grid& grid, int r, int c, int op, vector<string>& matches);

void checkRollOver(int &r1, int &c1, int dims, int direction);

#endif
