#include <vector>
#include <iostream>
#include <fstream>
using namespace std;


#ifndef GRID_H
#define GRID_H



class Grid {
    private:
        int rows, cols;

    public:
        vector<vector<char>> letters;
        void fillGrid(const string& filename);
        void printGrid();
        int getRow();
        
};

#endif 