#include <iostream>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Component.h"
#include "Path.h"
#include "ShortestPath.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;



    string filename2 = "/Users/arthurmeng/Documents/code/cpp/c_plus_plus/Graph/testG2.txt";
    SparseGraph g2 = SparseGraph(7, false);
    ReadGraph<SparseGraph> readGraph2(g2, filename2);
    Component<SparseGraph> component2(g2);
    cout<<"TestG2.txt , component count:"<<component2.count()<<endl;
    cout<<endl;
    ShortestPath<SparseGraph> path2(g2, 0);
    path2.showShortestPath(4);

    return 0;
}