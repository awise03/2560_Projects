// Project 5

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"

using namespace std;

class maze { 
    public: 
        maze(ifstream &fin);
        void print (int, int, int, int);
        bool isLegal(int i, int j);

        void setMap(int i, int j, int n);
        int getMap(int i, int j) const;
        void mapMazeToGraph(maze &m, graph &g);

        int findNextNode(graph &g);
        bool findPathRecursive(graph &g, int next, int i, int j);

    private:
        int rows; // number of rows in the maze
        int cols; // number of columns in the maze
        
        matrix<bool> value;
        matrix<int> map;    // Mapping from maze (i, j) value to node index values

};

// Set mapping from maze cell (i, j) to graph node n
void maze::setMap(int i, int j, int n) {
    map[i][j] = n;
}

// Return mapping of maze cell (i, j) in the graph.
int maze::getMap(int i, int j) const {
    return map[i][j];
}

// Create a graph g that represents the legal moves in the maze m.
void maze::mapMazeToGraph(maze &m, graph &g) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (value[i][j]) {
                int nodeId = g.addNode();  // Add node for each passable cell
                setMap(i, j, nodeId);

                // Connect to right neighbor
                if (j < cols - 1 && value[i][j+1]) {
                    g.addEdge(nodeId, getMap(i, j+1));
                }

                // Connect to left neighbor
                if(j > 0 && value[i][j-1]) {
                    g.addEdge(nodeId, getMap(i, j-1));
                }

                // Connect to up neighbor
                if(i > 0 && value[i-1][j]){
                    g.addEdge(nodeId, getMap(i-1,j));
                }
                
                // Connect to down neighbor
                if (i < rows - 1 && value[i+1][j]) {
                    g.addEdge(nodeId, getMap(i+1, j));
                }
                
            }
        }
    }
}

int maze::findNextNode(graph &g) {
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            if(value[r][c] && !g.isVisited(map[r][c])) {
                return map[r][c];
            }
        }
    }
}

bool maze::findPathRecursive(graph &g, int next, int r, int c) {
    if(g.allNodesVisited()) {
        return false;
    }

    // Left direction
    
    if((c - 1) >= 0 && value[r][c-1]) {
        cout << "entered left" << endl;
        if(!g.isVisited(map[r][c], map[r][c-1])){
            
            next = map[r][c-1];
            g.visit(map[r][c], map[r][c-1]);

            if(findPathRecursive(g, next, r, c-1)) {
                cout << "Go left!" << endl;
                return true;
            }
        }
        
    }
    // Right direction
    if((c+1) >= cols && value[r][c+1]){
        cout << "entered right" << endl;
        if(!g.isVisited(map[r][c], map[r][c+1])){
            
            next = map[r][c+1];
            g.visit(map[r][c], map[r][c+1]);

            if(findPathRecursive(g, next, r, c+1)) {
                cout << "Go right!" << endl;
                return true;
            }
        }

    }

    // Up direction 
    if((r - 1) >= 0 && value[r-1][c]) {
        cout << "entered up" << endl;
        if(!g.isVisited(map[r][c], map[r-1][c])) {
            
            next = map[r-1][c];
            g.visit(map[r][c], map[r-1][c]);

            if(findPathRecursive(g, next, r-1, c)) {
                cout << "Go up!" << endl;
                return true;
            }
        }
       

    }

    // Down direction
    if((r + 1) <= rows && value[r+1][c]) {
        cout << "entered down" << endl;
        if(!g.isVisited(getMap(r,c), getMap(r+1, c)))    {
             cout << "passed down" << endl;
            next = map[r+1][c];
            g.visit(getMap(r,c), getMap(r+1, c));

            if(findPathRecursive(g, next, r+1, c)) {
                cout << "Go down!" << endl;
                return true;
            }
        }
    }
    cout << "failed" << endl;
    g.visit(map[r][c]);
    return false;
}

// Initializes a maze by reading values from fin. Assumes that the
// number of rows and columns indicated in the file are correct.
maze::maze(ifstream &fin) {
    fin >> rows;
    fin >> cols;

    char x;

    value.resize(rows,cols);
    for (int i = 0; i <= rows-1; i++)
        for (int j = 0; j <= cols-1; j++) {
            fin >> x;
            if (x == 'O')
                value[i][j] = true;
            else
                value[i][j] = false;
        }
    map.resize(rows,cols);
}

// Print out a maze, with the goal and current cells marked on the
// board.
void maze::print(int goalI, int goalJ, int currI, int currJ) {
    cout << endl;

    if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
        throw rangeError("Bad value in maze::print");

    if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
        throw rangeError("Bad value in maze::print");

    for (int i = 0; i <= rows-1; i++) {
        for (int j = 0; j <= cols-1; j++) {
            if (i == goalI && j == goalJ)
                cout << "*";
            else
                if (i == currI && j == currJ)
                    cout << "+";
                else
                    if (value[i][j])
                        cout << " ";
                    else
                        cout << "X";
        }
        cout << endl;
    }
    cout << endl;
}

// Return the value stored at the (i,j) entry in the maze.
bool maze::isLegal(int i, int j) {
    if (i < 0 || i >= rows || j < 0 || j >= cols)
        throw rangeError("Bad value in maze::isLegal");

    return value[i][j];
}



int main() {
    char x;
    ifstream fin;
    // Read the maze from the file.
    string fileName = "maze1.txt";
    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try {
        graph g;
        while (fin && fin.peek() != 'Z') {
            maze m(fin);
            m.mapMazeToGraph(m, g);
            //m.findPathRecursive(g, 0, 0, 0);
        }
        cout << g << endl;
    }

    catch (indexRangeError &ex) {
        cout << ex.what() << endl; exit(1);
    }
    catch (rangeError &ex) {
        cout << ex.what() << endl; exit(1);
    }

    
    
}