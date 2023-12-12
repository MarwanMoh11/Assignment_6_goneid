// FILE: graphs.cpp
// Graph Library Implementation File for Asn 6

#include <fstream>		// For reading file from disk
#include <iostream>
#include <sstream>
#include <string>		// For file name
#include <iomanip>	// Deinition of an Edge
#include <vector>
#include <cctype>
#include <algorithm>
#include "Graphs.h"
#include <limits>
#include <stack>

using namespace std;

// Constructor
Graphs::Graphs()
{
    E = V = order = 0;
}

// Destructor
Graphs::~Graphs()
{
}


// Map vertex number (0,1,2,..) to (A,B,C,..)
char Graphs::Vname(const int s) const
{
    return char(s+65);
}

// Get Graph from text File (file name is stored in string fname)
// Graph is stored in adjacency matrix
void Graphs::getGraph(string fname) {
    int i =0;
    int rows = 0;
    int columns = 0;
    int wordcounter = 0;

    ifstream source1(fname); // opens file for checking number of vertices automatically

    string line1;
    while (getline(source1, line1)) {
        //Check if the line is not empty
        if (!line1.empty() && line1.find_first_not_of(" \t") != string::npos) {
            V++;
        }}

    V = V-1; // we do -1 because the "City" is not a vertex
    ifstream source(fname);

    if (!source.is_open()) {
        cerr << "Error opening file: " << fname << endl;
        return;
    }

    string line;
    while (getline(source, line)) {
        // Check if the line is not empty
        if (!line.empty() && line.find_first_not_of(" \t") != string::npos) {
            istringstream wordStream(line);
            string city;
            while (wordStream >> city) {
                if (city != "City" && !any_of(city.begin(), city.end(), ::isupper)) {
                    wordcounter++;
                    if (wordcounter % V-1 == 0) { // mod 13 to correctly get the matrix ignoring headings
                        rows++;
                        columns = 0;
                    }
                    columns++;
                    if (rows >= 1 && columns >= 1 && isNumeric(city)) {
                        // Adjust indices for zero-based indexing
                        AdjMatrix[rows-1][columns-1] = stoi(city);

                        if (stoi(city) != 0 && visitededges[stoi(city)] == false) {
                            visitededges[stoi(city)] = true;
                            edges[i].u = rows - 1;
                            edges[i].v = columns - 1;
                            edges[i].w = stoi(city);
                            i++;
                            E++;
                        }
                    }
                }
            }
        }
    }

    source.close();
}

// Display Adjacency Matrix
void Graphs::dispGraph() const
{
    int i,j;
    cout<<"Adjacency Matrix\n";

    for(i=0; i<V; i++)
    {
        for(j=0; j<V; j++)
            cout<< setw(3)<< AdjMatrix[i][j] << " ";
        cout<< endl;
    }
}

// Get Non-Zero edges from adjacency matrix
// and store them in array edges[].
void Graphs::getEdges()
{
    int r , c;
    int i = 0;
    weightType weight;

    // Only examine weights above the diagonal
    for (r = 0; r <= V-2; r++)
        for (c = r+1; c <= V-1; c++)
        {
            weight = AdjMatrix[r][c];
            if (weight > 0)
            {
                // save (r,c,weight) in edges[i]
                edges[i].u = r;
                edges[i].v = c;
                edges[i].w = weight;
                i++;
            }
        }

    E = i;		// Number of non-zero edges

}

// Get number of vertices (V)
int Graphs::No_of_Verices() const
{
    return V;
}

// Get Number of Non-zero edges (E)
int Graphs::No_of_Edges() const
{
    return E;
}

// Output an edge (e): Vertex names and weight
void Graphs::printEdge(Edge e) const
{
    cout << Vname(e.u) << " " << Vname(e.v) << " " << e.w << endl;
}

// Display Graph Edges
void Graphs::dispEdges() const
{
    cout<<"Graph Edges\n";
    for (int i = 0; i < E; i++)
        printEdge(edges[i]);
}

// Shortest paths from node s
// uses Dijkstra's Algorithm
void Graphs::shPath(int s)
{
    std::vector<int> distance(V, std::numeric_limits<int>::max());
    std::vector<int> via(V, -1);
    std::vector<bool> processed(V, false);

    distance[s] = 0;

    auto findClosestUnprocessedNode = [&]() {
        int minDistance = std::numeric_limits<int>::max();
        int closestNode = -1;

        for (int i = 0; i < V; ++i) {
            if (!processed[i] && distance[i] < minDistance) {
                minDistance = distance[i];
                closestNode = i;
            }
        }

        return closestNode;
    };

    while (true) {
        int j = findClosestUnprocessedNode();

        if (j == -1) {
            // All vertices processed
            break;
        }

        processed[j] = true;

        for (int i = 0; i < V; ++i) {
            if (!processed[i] && AdjMatrix[j][i] != 0) {
                int newDistance = distance[j] + AdjMatrix[j][i];

                if (newDistance < distance[i]) {
                    distance[i] = newDistance;
                    via[i] = j;
                }
            }
        }
    }

    // Output the results with paths
    std::cout << "Shortest Paths from Node " << Vname(s) << ":" << std::endl;
    for (int i = 0; i < V; ++i) {
        std::cout << "To Node " << Vname(i) << ": ";
        if (distance[i] == std::numeric_limits<int>::max()) {
            std::cout << "No path";
        } else {
            // Display the path
            int currentNode = i;
            std::vector<int> path;
            while (currentNode != s) {
                path.push_back(currentNode);
                currentNode = via[currentNode];
            }
            path.push_back(s);

            // Output the path in reverse order
            for (int j = path.size() - 1; j >= 0; --j) {
                char nodeName = 'A' + path[j];
                std::cout << nodeName;
            }
        }

        std::cout << " (" << distance[i] << ")" << std::endl;
    }
}


// Print path (vertex names) from source (s) to destination (i)
void Graphs::printPath(int s, int i) const
{
    // Implement the function here
}

// Node Visit Function
void Graphs::visit(int k) {
    val[k] = ++order;
    cout << k << " "; // print visited node
    for (int t = 0; t < V; ++t) {
        if (AdjMatrix[k][t] != 0 && val[t] == -1) {
            visit(t);
        }
    }
}

// Depth First Search Traversal

bool Graphs::isNumeric(const string &str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

void Graphs::DFS() {
    // Initialize all to unseen
    for (int k = 0; k < V; ++k) {
        val[k] = -1; // Assuming unseen is represented by -1
    }

    // Follow Nodes in Depth
    for (int k = 0; k < V; ++k) {
        if (val[k] == -1) {
            visit(k);
        }
    }
}

