//
// Created by ArthurMeng on 2017/12/30.
//

#ifndef GRAPH_DENSEGRAPH_H
#define GRAPH_DENSEGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>
#include "Edge.h"

using namespace std;

template <typename Weight>
class DenseGraph
{
private:
    int n;//the number of vertex
    int m;//the number of edge
    bool directed;
    vector<vector<Edge<Weight>*>> g;

public:
    DenseGraph(int n, bool directed)
    {
        this->n = n;
        this->directed = directed;
        this->m = 0;
        for(int i = 0 ; i < n ; i++)
            g.push_back(vector<Edge<Weight>*>(n, NULL));
    }

    ~DenseGraph()
    {
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < n ; j++)
                if(g[i][j])
                    delete g[i][j];
    }

    int V(){return n;}
    int E(){return m;}

    bool hasEdge(int v, int w)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        return g[v][w] != NULL;
    }

    void addEdge(int v, int w, Weight weight)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        if(hasEdge(v, w))
        {
            delete g[v][w];
            if(!directed)
                delete g[w][v];
            m--;
        }


        g[v][w] = new Edge<Weight>(v, w, weight);
        if(!directed)
            g[w][v] = new Edge<Weight>(w, v, weight);
        m++;
    }

    void show()
    {
        for(int i = 0 ; i < n ; i++)
        {
            for(int j = 0 ; j < n ; j++)
                if(g[i][j])
                    cout<<g[i][j]->wt()<<"\t";
                else
                    cout<<"NULL"<<"\t";
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

        Edge<Weight>* begin()
        {
            index = -1;
            return next();
        }

        Edge<Weight>* next()
        {
            for(index++ ; index < G.V() ; index++ )
                if(G.g[v][index])
                    return G.g[v][index];
            return NULL;
        }

        bool end()
        {
            return index >= G.V();
        }
    };
};

#endif //GRAPH_DENSEGRAPH_H
