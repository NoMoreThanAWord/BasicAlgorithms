//
// Created by ArthurMeng on 2017/12/30.
//

#ifndef GRAPH_DENSEGRAPH_H
#define GRAPH_DENSEGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class DenseGraph
{
private:
    int n;//the number of vertex
    int m;//the number of edge
    bool directed;
    vector<vector<bool>> g;

public:
    DenseGraph(int n, bool directed)
    {
        this->n = n;
        this->directed = directed;
        this->m = 0;
        for(int i = 0 ; i < n ; i++)
            g.push_back(vector<bool>(n, false));
    }

    ~DenseGraph()
    {
    }

    int V(){return n;}
    int E(){return m;}

    bool hasEdge(int v, int w)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        return g[v][w];
    }

    void addEdge(int v, int w)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        if(hasEdge(v, w))
            return;

        g[v][w] = true;
        if(!directed)
            g[w][v] = true;
        m++;
    }

    void show()
    {
        for(int i = 0 ; i < n ; i++)
        {
            for(int j = 0 ; j < n ; j++)
                cout<<g[i][j]<<"\t";
            cout<<endl;
        }
    }

    class adjIterator
    {
    private:
        DenseGraph &G;
        int v;
        int index;

    public:
        adjIterator(DenseGraph &graph, int v) : G(graph)
        {
            this->v = v;
            index = -1;
        }

        int begin()
        {
            index = -1;
            return next();
        }

        int next()
        {
            for(index++ ; index < G.V() ; index++ )
                if(G.g[v][index] == true)
                    return index;
            return -1;
        }

        bool end()
        {
            return index >= G.V();
        }
    };
};

#endif //GRAPH_DENSEGRAPH_H
