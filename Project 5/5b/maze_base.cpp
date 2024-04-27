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
        void printPath(const vector<int> &path);
        vector<int> findAdjNodes(graph &g, int n);
        void printQueue(queue<int> q);
        vector<string> createPath(vector<int> path);

        void findShortestPath1(graph &g);
        void findShortestPath2(graph &g);
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

    // Check the order: up, down, left, right
    int row = -1, col = -1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (getMap(i, j) == n) {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1) break;
    }

    // Check the adjacent nodes in the order: up, down, left, right
    if (row > 0 && g.isEdge(n, getMap(row - 1, col))) {
        adjNodes.push_back(getMap(row - 1, col)); // Up
    }
    if (row < rows - 1 && g.isEdge(n, getMap(row + 1, col))) {
        adjNodes.push_back(getMap(row + 1, col)); // Down
    }
    if (col > 0 && g.isEdge(n, getMap(row, col - 1))) {
        adjNodes.push_back(getMap(row, col - 1)); // Left
    }
    if (col < cols - 1 && g.isEdge(n, getMap(row, col + 1))) {
        adjNodes.push_back(getMap(row, col + 1)); // Right
    }

    return adjNodes;
}

//Prints the paths stored within the vector, paths
void maze::printPath(const vector<int>& path) {
    int r = 0;
    int c = 0;
    print(rows-1, cols-1, r, c);

    for (int i = 1; i < path.size(); i++) {
        int curr = path[i];

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (getMap(row, col) == curr) {
                    r = row;
                    c = col;
                    break;
                }
            }
        }

        print(rows-1, cols-1, r, c);
    }

    for (const string& direction : paths) {
        if (direction == "U") {
            cout << "Go Up! -> ";
        } else if (direction == "D") {
            cout << "Go Down! -> ";
        } else if (direction == "R") {
            cout << "Go Right! -> ";
        } else {
            cout << "Go Left! -> ";
        }
    }
    cout << "End!" << endl;
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

    vector<int> parent(g.numNodes(), -1); // Create vector of parent nodes utilized for the final path
    queue<int> q; // Intialize an empty queue
    q.push(getMap(0, 0)); // Add the first node to the queue 


    while(!q.empty()) {
        
        int curr = q.front(); // Grabs the top node in the queue

        q.pop(); // Pops this node
        g.visit(curr); // Marks this node as visited

        

        if(curr == getMap(rows-1, cols-1)){ // Checks to see if current node is the end of maze
            break;
        }

        vector<int> adjNodes = findAdjNodes(g, curr); // Finds the nodes adjacent to the current node

        for(int next : adjNodes) { // Iterates through the adjacent nodes
            if(!g.isMarked(next) && !g.isVisited(next)) { // Checks to see if the node is unvisted
                g.mark(next);   // Marks the node 
                q.push(next);   // Adds node to the queue
                parent[next] = curr;    // Adds the node to the parent vector
            }
        }
    }

    vector<int> path; // Initialize vector of the pathing
    int curr = getMap(rows-1, cols-1); // Grabs the last node in the maze
    while (curr != getMap(0,0)) { // Iterates through until we reach the start
        path.push_back(curr);   
        curr = parent[curr];
    }
    path.push_back(getMap(0,0));
    
    return path;
}

// Creates a path based on provided node visit order
vector<string> maze::createPath(vector<int> path) {
    vector<string> directions;
    int prev_r = 0, prev_c = 0;

    for (int i = 1; i < path.size(); i++) {
        int curr = path[i];

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (getMap(r, c) == curr) {
                    if (r < prev_r) directions.push_back("U");
                    else if (r > prev_r) directions.push_back("D");
                    else if (c > prev_c) directions.push_back("R");
                    else if (c < prev_c) directions.push_back("L");

                    prev_r = r;
                    prev_c = c;
                    break;
                }
            }
        }
    }

    return directions;
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
    vector<int> parent(g.numNodes(), -1);
    vector<bool> visited(g.numNodes(), false);
    int startNode = getMap(0, 0);
    int goalNode = getMap(rows - 1, cols - 1);

    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == goalNode) {
            break; // Reached the goal node
        }

        vector<int> adjNodes = findAdjNodes(g, current);

        for (int next : adjNodes) {
            if (!visited[next]) {
                parent[next] = current;
                visited[next] = true;
                q.push(next);
            }
        }
    }

    if (!visited[goalNode]) {
        cout << "No path found." << endl;
        return;
    }

    // Reconstruct the shortest path
    vector<int> path;
    int step = goalNode;
    while (step != -1) {
        path.push_back(step);
        step = parent[step];
    }
    reverse(path.begin(), path.end());

    // Output the shortest path
    cout << "Shortest path found:" << endl;
    paths = createPath(path);
    printPath(path);
}

// use of Dijkstra's algorithm
void maze::findShortestPath2(graph &g) {
    vector<int> dist(g.numNodes(), INT_MAX);
    vector<int> parent(g.numNodes(), -1);
    vector<bool> visited(g.numNodes(), false);
    int startNode = getMap(0, 0);
    int goalNode = getMap(rows - 1, cols - 1);

    dist[startNode] = 0;

    for (int i = 0; i < g.numNodes(); i++) {
        int u = -1;
        int minDist = INT_MAX;

        for (int j = 0; j < g.numNodes(); j++) {
            if (!visited[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }

        if (u == -1) {
            break;
        }

        visited[u] = true;

        if (u == goalNode) {
            break;
        }

        vector<int> adjNodes = findAdjNodes(g, u);

        for (int v : adjNodes) {
            if (!visited[v] && dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
            }
        }
    }

    if (!visited[goalNode]) {
        cout << "No path found." << endl;
        return;
    }

    vector<int> path;
    int step = goalNode;
    while (step != -1) {
        path.push_back(step);
        step = parent[step];
    }
    reverse(path.begin(), path.end());

    cout << "Shortest path found:" << endl;
    paths = createPath(path);
    printPath(path);
}

int main() {
    char x;
    ifstream fin;
    string fileName;
    int choice;

    cout << "Available mazes:" << endl;
    cout << "1. maze1.txt" << endl;
    cout << "2. maze2.txt" << endl;
    cout << "3. maze3-1.txt" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    switch (choice) {
        case 1:
            fileName = "maze1.txt";
            break;
        case 2:
            fileName = "maze2.txt";
            break;
        case 3:
            fileName = "maze3-1.txt";
            break;
        default:
            cout << "Invalid choice. Exiting." << endl;
            return 0;
    }

    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try {
        while (fin && fin.peek() != 'Z') {
            graph g;
            maze m(fin);
            m.mapMazeToGraph(m, g);

            int algorithmChoice;
            cout << "Choose the algorithm to find the shortest path:" << endl;
            cout << "1. Breadth-First Search (BFS)" << endl;
            cout << "2. Dijkstra's Algorithm" << endl;
            cout << "Enter your choice (1-2): ";
            cin >> algorithmChoice;

            switch (algorithmChoice) {
                case 1:
                    cout << "Using BFS algorithm:" << endl;
                    m.findShortestPath1(g);
                    break;
                case 2:
                    cout << "Using Dijkstra's algorithm:" << endl;
                    m.findShortestPath2(g);
                    break;
                default:
                    cout << "Invalid choice. Exiting." << endl;
                    return 0;
            }

            cout << endl;
        }
    }
    catch (indexRangeError &ex) {
        cout << ex.what() << endl;
        exit(1);
    }
    catch (rangeError &ex) {
        cout << ex.what() << endl;
        exit(1);
    }

    fin.close();

    return 0;
}