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

        bool findPathRecursive(graph &g, int next, int i, int j);
        void findPathNonRecursive();
        void printPath();
    private:
        int rows; // number of rows in the maze
        int cols; // number of columns in the maze
        
        matrix<bool> value;
        matrix<int> map;    // Mapping from maze (i, j) value to node index values
        vector<string> paths; // Vector of pathing instructions 

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
    // Initialize map with all available spots
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(value[i][j]) {
                setMap(i, j, g.addNode());
            }
        }
    }

    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (value[i][j]) {

                // Connect to right neighbor
                if (j < cols - 1 && value[i][j+1]) {
                    g.addEdge(getMap(i, j), getMap(i, j+1));
                }

                // Connect to left neighbor
                if(j > 0 && value[i][j-1]) {
                    g.addEdge(getMap(i, j), getMap(i, j-1));
                }

                // Connect to up neighbor
                if(i > 0 && value[i-1][j]){
                    g.addEdge(getMap(i, j), getMap(i-1,j));
                }
                
                // Connect to down neighbor
                if (i < rows - 1 && value[i+1][j]) {
                    g.addEdge(getMap(i, j), getMap(i+1, j));
                }
                
            }
        }
    }
}

// Prints the paths stored within the vector, paths
void maze::printPath() {    
    for(int i = paths.size() - 1; i >= 0; i--) {
        cout << paths[i] << endl;
    }
}

// Recursively solves the maze using DFS 
bool maze::findPathRecursive(graph &g, int next, int r, int c) {
    print(rows, cols, r, c);
    if(r == rows-1 && c == cols-1) {
        cout << "finished" << endl;
        return true;
    }

    if(g.allNodesVisited()) {
        cout << "No Path Exists" << endl;
        return false;
    }

    g.visit(map[r][c]); // Mark node as visited

    // Right direction
    if((c+1) < cols && value[r][c+1]) { // Checks to see if we can move in this direction
        
        if(!g.isVisited(getMap(r, c+1))) { // Checks to see if the node to the right is unvisited 
            
            next = map[r][c+1];

            if(findPathRecursive(g, next, r, c+1)) { // Recursively call with a traversal to the right
                paths.push_back("Go right!");
                return true;
            }
        }

    }

    // Down direction
    if((r + 1) < rows && value[r+1][c]) { // Checks to see if we can move in this direction

        if(!g.isVisited(getMap(r+1, c))) { // Checks to see if the node below is unvisited 

            next = map[r+1][c];

            if(findPathRecursive(g, next, r+1, c)) { // Recursively call with a traversal down
                paths.push_back("Go down!");
                return true;
            }
        }
    }

    // Left direction
    if((c - 1) >= 0 && value[r][c-1]) { // Checks to see if we can move in this direction
        //cout << "entered left" << endl;
        if(!g.isVisited(getMap(r, c-1))){ // Checks to see if the node to the left is unvisited 
            
            next = map[r][c-1];

            if(findPathRecursive(g, next, r, c-1)) { // Recursively call with a traversal to the left
                paths.push_back("Go left!");
                return true;
            }
        }
        
    }

    // Up direction 
    if((r - 1) >= 0 && value[r-1][c]) { // Checks to see if we can move in this direction

        if(!g.isVisited(getMap(r-1, c))) { // Checks to see if the node above is unvisited 
            
            next = map[r-1][c];

            if(findPathRecursive(g, next, r-1, c)) { // Recursively call with a traversal up
                paths.push_back("Go up!");
                return true;
            }
        }
       

    }


    
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
    string fileName = "Project 5/5a/maze1.txt";
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
            m.findPathRecursive(g, 0, 0, 0);
            m.printPath();
        }
        //cout << g << endl;
    }

    catch (indexRangeError &ex) {
        cout << ex.what() << endl; exit(1);
    }
    catch (rangeError &ex) {
        cout << ex.what() << endl; exit(1);
    }

    
    
}