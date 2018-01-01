//
// Created by ArthurMeng on 2017/12/30.
//

#ifndef GRAPH_COMPONENT_H
#define GRAPH_COMPONENT_H

#include <iostream>
#include <cassert>
#include "DenseGraph.h"
#include "SparseGraph.h"
using namespace std;

template <typename Graph>
class Component
{
private:
    Graph &G;
    int ccount;
    int *id;
    bool *visited;

    void dfs(int v)
    {
        visited[v] = true;
        id[v] = ccount;

        typename Graph::adjIterator adj(G, v);

        for(int i = adj.begin() ; !adj.end() ; i = adj.next())
            if(!visited[i])
                dfs(i);
    }

public:
    Component(Graph &graph) : G(graph)
    {
        ccount = 0;
        visited = new bool[G.V()];
        id = new int[G.V()];

        for(int i = 0 ; i < G.V() ; i++)
        {
            id[i] = -1;
            visited[i] = false;
        }


        for(int i = 0 ; i < G.V() ; i++)
        {
            if(!visited[i])
            {
                dfs(i);
                ccount++;
            }
        }
    }

    ~Component()
    {
        delete[] visited;
        delete[] id;
    }

    int count()
    {
        return ccount;
    }

    bool isConnected(int v, int w)
    {
        assert(v >= 0 && v < G.V());
        assert(w >= 0 && w < G.V());

        return id[v] == id[w];
    }
};

#endif //GRAPH_COMPONENT_H
