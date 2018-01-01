//
// Created by ArthurMeng on 2017/12/30.
//

#ifndef GRAPH_PATH_H
#define GRAPH_PATH_H

#include <iostream>
#include <cassert>
#include "DenseGraph.h"
#include "SparseGraph.h"
#include <vector>
#include <stack>
using namespace std;

template <typename Graph>
class Path
{
private:
    Graph &G;
    int s;
    int *from;
    bool *visited;

    void dfs(int v)
    {
        visited[v] = true;

        typename Graph::adjIterator adj(G, v);

        for(int i = adj.begin() ; !adj.end() ; i = adj.next())
            if(!visited[i])
            {
                from[i] = v;
                dfs(i);
            }
    }

public:
    Path(Graph &graph, int s) : G(graph)
    {
        assert(s >= 0 && s < G.V());
        this->s = s;
        visited = new bool[G.V()];
        from = new int[G.V()];

        for(int i = 0 ; i < G.V() ; i++)
        {
            visited[i] = false;
            from[i] = -1;
        }

        dfs(s);

    }

    ~Path()
    {
        delete[] visited;
        delete[] from;
    }

    void path(int w, vector<int> &vec)
    {
        assert(hasPath(w));
        stack<int> sta;

        int p = w;
        while(p != -1)
        {
            sta.push(p);
            p = from[p];
        }

        vec.clear();
        while(!sta.empty())
        {
            vec.push_back(sta.top());
            sta.pop();
        }
    }

    bool hasPath(int w)
    {
        assert(w >= 0 && w < G.V());

        return visited[w];
    }

    void showPath(int w)
    {
        assert(w >= 0 && w < G.V());
        vector<int> vec;

        path(w, vec);
        for(int i = 0 ; i < vec.size() ; i++)
        {
            cout<<vec[i];
            if(i == vec.size()-1)
                cout<<endl;
            else
                cout<<" -> ";
        }
    }
};

#endif //GRAPH_PATH_H