#include <vector>
#include <iostream>
#include <fstream>
using namespace std;


#ifndef GRID_H
#define GRID_H



class Grid {
    private:
        vector<vector<char>> letters;
        int rows, cols;

    public:
        void fillGrid(const string& filename);
        void printGrid();

};

#endif 