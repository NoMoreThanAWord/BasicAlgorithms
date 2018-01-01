#include <iostream>
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "SparseGraph.h"
#include <iomanip>
#include "LazyPrimMST.h"
#include "PrimMst.h"
#include "KruskalMST.h"
#include "Edge.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    string filename = "/Users/arthurmeng/Documents/code/cpp/c_plus_plus/MinimumSpanTree/testG1.txt";
    int V = 8;

    SparseGraph<double> g = SparseGraph<double>(V, false);
    ReadGraph<SparseGraph<double>, double> readGraph(g, filename);

    // Test Lazy Prim MST
    cout<<"Test Lazy Prim MST:"<<endl;
    LazyPrimMST<SparseGraph<double>, double> lazyPrimMST(g);
    vector<Edge<double>> mst1 = lazyPrimMST.mstEdges();
    for( int i = 0 ; i < mst1.size() ; i ++ )
        cout<<mst1[i]<<endl;
    cout<<"The MST weight is: "<<lazyPrimMST.result()<<endl;

    cout<<endl;

    cout<<"Test Prim MST:"<<endl;
    PrimMst<SparseGraph<double>, double> primMst(g);
    vector<Edge<double>> mst2 = primMst.mstEdges();
    for(int i = 0 ; i < mst2.size() ; i++)
        cout<<mst2[i]<<endl;
    cout<<"The MST weight is: "<<primMst.result()<<endl;
    cout<<endl;

    cout<<"Test for Kruskal"<<endl;
    KruskalMST<SparseGraph<double>, double> kruskalMST(g);
    vector<Edge<double>> mst3 = kruskalMST.mstEdges();
    for(int i = 0 ; i < mst3.size() ; i++)
        cout<<mst3[i]<<endl;
    cout<<"The MST weight is: "<<kruskalMST.result()<<endl;

    return 0;
}