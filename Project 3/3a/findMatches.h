#include "dictionary.cpp"
#include "grid.cpp"
#include <vector>

#ifndef FINDMATCHES

#define FINDMATCHES

vector<string> findMatches(const Dictionary& dict, const Grid& grid);

void wordSearch(vector<string>& matches, vector<char>& row, const Dictionary& dict);

#endif
