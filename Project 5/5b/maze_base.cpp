// Project 5

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"
#include <queue>
#include <algorithm>

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
        vector<int> findPathNonRecursive(graph &g);
        void printPath();
        vector<int> findAdjNodes(graph &g, int n);
        void printQueue(queue<int> q);
        vector<string> createPath(vector<int> path);

        void findShortestPath1(graph &g);
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

// Finds a vector of all nodes adjacent to the given node
vector<int> maze::findAdjNodes(graph &g, int n) {
    vector<int> adjNodes;
    for(int i = 0; i < g.numNodes(); i++) {
        if(i != n && g.isEdge(n, i)) {
            adjNodes.push_back(i);
        }
    }

    return adjNodes;
}

// Function to print queue
void maze::printQueue(queue<int> q) {
    while(!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

// Finds the path using queue based BFS
vector<int> maze::findPathNonRecursive(graph &g) {
    g.clearVisit();
    g.clearMark();

    vector<int> visited;
    vector<int> parent(g.numNodes(), -1);
    queue<int> q;
    q.push(getMap(0, 0));


    while(!q.empty()) {
        //printQueue(q);
        int curr = q.front();

        q.pop();
        g.visit(curr);

        visited.push_back(curr);
        

        if(curr == getMap(rows-1, cols-1)){
            break;
        }

        vector<int> adjNodes = findAdjNodes(g, curr);

        for(int next : adjNodes) {
            if(!g.isMarked(next) && !g.isVisited(next)) {
                g.mark(next);
                q.push(next);
                parent[next] = curr;
            }
        }
    }

    vector<int> path;
    int curr = getMap(rows-1, cols-1);
    while (curr != getMap(0,0)) {
        path.push_back(curr);
        curr = parent[curr];
    }
    path.push_back(getMap(0,0));
    
    return path;
}

// Creates a path based on provided node visit order
vector<string> maze::createPath(vector<int> path) {
    paths.clear();

    int prev_r = rows-1;
    int prev_c = cols-1;

    for(int i = 1; i < path.size(); i++) {
        
        for(int curr_r = rows - 1; curr_r >= 0; curr_r--) {
            for(int curr_c = cols - 1; curr_c >= 0; curr_c--){
                if(getMap(curr_r,curr_c) == path[i] && value[curr_r][curr_c]) {
                    
                    if(curr_r < prev_r) paths.push_back("D");
                    else if(curr_r > prev_r) paths.push_back("U");
                    else if(curr_c < prev_c) paths.push_back("R");
                    else if(curr_c > prev_c) paths.push_back("L");

                    prev_r = curr_r;
                    prev_c = curr_c;
                }
            }
        }

    }

    printPath();
    return paths;
}

// Recursively solves the maze using DFS 
bool maze::findPathRecursive(graph &g, int next, int r, int c) {
    // print(rows-1, cols-1, r, c);
    if(r == rows-1 && c == cols-1) {
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
                paths.push_back("R");
                return true;
            }
        }

    }

    // Down direction
    if((r + 1) < rows && value[r+1][c]) { // Checks to see if we can move in this direction

        if(!g.isVisited(getMap(r+1, c))) { // Checks to see if the node below is unvisited 

            next = map[r+1][c];

            if(findPathRecursive(g, next, r+1, c)) { // Recursively call with a traversal down
                paths.push_back("D");
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
                paths.push_back("L");
                return true;
            }
        }
        
    }

    // Up direction 
    if((r - 1) >= 0 && value[r-1][c]) { // Checks to see if we can move in this direction

        if(!g.isVisited(getMap(r-1, c))) { // Checks to see if the node above is unvisited 
            
            next = map[r-1][c];

            if(findPathRecursive(g, next, r-1, c)) { // Recursively call with a traversal up
                paths.push_back("U");
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

void maze::findShortestPath1(graph &g) {
    queue<int> q;
    vector<bool> visited(g.numNodes(), false);
    vector<int> prev(g.numNodes(), -1);

    int startNode = getMap(0, 0); // Assuming start at top-left corner
    int endNode = getMap(rows - 1, cols - 1); // Assuming end at bottom-right corner
    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        // Loop through adjacent nodes
        for (int adjNode = 0; adjNode < g.numNodes(); ++adjNode) {
            if (g.isEdge(currentNode, adjNode) && !visited[adjNode]) {
                visited[adjNode] = true;
                prev[adjNode] = currentNode;
                q.push(adjNode);
                if (adjNode == endNode) {
                    break;
                }
            }
        }
    }

    // Reconstruct the path from endNode to startNode
    vector<int> path;
    for (int at = endNode; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    // Convert path from node indices to directions
    paths.clear(); // Clear any existing paths
    for (size_t i = 1; i < path.size(); i++) {
        int r1 = path[i-1] / cols; // Compute row index
        int c1 = path[i-1] % cols; // Compute column index
        int r2 = path[i] / cols;
        int c2 = path[i] % cols;

        if (r1 == r2 && c1 < c2)
            paths.push_back("Go right");
        else if (r1 == r2 && c1 > c2)
            paths.push_back("Go left");
        else if (c1 == c2 && r1 < r2)
            paths.push_back("Go down");
        else if (c1 == c2 && r1 > r2)
            paths.push_back("Go up");
    }

    printPath();
}


int main() {
    char x;
    ifstream fin;
    // Read the maze from the file.
    string fileName = "Project 5/5b/maze3-1.txt";
    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try {
        graph g;
        while (fin && fin.peek() != 'Z') {
            graph g; // create graph object
            maze m(fin);
            m.mapMazeToGraph(m, g);
            m.findShortestPath1(g);
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