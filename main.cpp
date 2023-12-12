#include <iostream>
#include "Graphs.h"
using namespace std;

int main() {

    Graphs x;

    x.getGraph("LISTS.txt");


    cout << "Number of Vertices: " << x.No_of_Verices() << endl;
    cout << "Number of Edges: " << x.No_of_Edges() << endl;
    x.dispGraph();
    x.dispEdges();
    cout << "DFS TRAVERSAL: " << endl;
    x.DFS();
    cout << endl;
    x.shPath(0);



}
