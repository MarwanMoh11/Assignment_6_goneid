// FILE: graphs.cpp
// Graph Library Implementation File for Asn 6

#include <fstream>		// For reading file from disk
#include <iostream>
#include <string>		// For file name
#include <iomanip>
#include "Edge.h"		// Deinition of an Edge

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
void Graphs::getGraph(string fname)		
{
   // Local data ...
	weightType wi;
	ifstream source;

	source.open(fname.c_str()); 
	source >> V;	// Read no. of verices (V)
	
	// Input weights from the file into a 2-D 
	// Adjacency Matrix of V rows and V columns
	for (int r = 0; r < V; r++)
	{
		// get V weights for row [r] from file
		// put V weights in adjacency matrix at row [r]
	}
	// close file
	
	
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
	// Implement the function here
}

// Print path (vertex names) from source (s) to destination (i)
void Graphs::printPath(int s, int i) const
{
	// Implement the function here
}

// Node Visit Function
void Graphs::visit(int k)
{ 
	// Implement the function here	
}

// Depth First Search Traversal
void Graphs::DFS()									
{ 
	// Implement the function here	
}
