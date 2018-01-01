//
// Created by ArthurMeng on 2017/12/30.
//

#ifndef GRAPH_SPARSEGRAPH_H
#define GRAPH_SPARSEGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
class SparseGraph
{
private:
    int n;
    int m;
    bool directed;
    vector<vector<int>> g;

public:
    SparseGraph(int n, bool directed)
    {
        this->n = n;
        this->m = 0;
        this->directed = directed;
        for(int i = 0 ; i < n ; i++)
            g.push_back(vector<int>());
    }

    ~SparseGraph()
    {
    }

    int V(){return n;}
    int E(){return m;}

    bool hasEdge(int v, int w)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        for(int i = 0 ; i < g[v].size() ; i++)
            if(g[v][i] == w)
                return true;
        return false;
    }

    void addEdge(int v, int w)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        g[v].push_back(w);
        if(!directed && v != w)
            g[w].push_back(v);

        m++;
    }

    void show()
    {
        for(int i = 0 ; i < n ; i++)
        {
            cout<<"vertex "<<i<<":\t";
            for(int j = 0 ; j < g[i].size() ; j++)
                cout<<g[i][j]<<"\t";
            cout<<endl;
        }
    }

    class adjIterator
    {
    private:
        SparseGraph &G;
        int index;
        int v;

    public:
        adjIterator(SparseGraph &graph, int v) : G(graph)
        {
            this->index = 0;
            this->v = v;
        }

        int begin()
        {
            index = 0;
            if(G.g[v].size())
                return G.g[v][index];
            return -1;
        }

        int next()
        {
            index++;
            if(index < G.g[v].size())
                return G.g[v][index];
            return -1;
        }

        bool end()
        {
            return index >= G.g[v].size();
        }
    };
};

#endif //GRAPH_SPARSEGRAPH_H
