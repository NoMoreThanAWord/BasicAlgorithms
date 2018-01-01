//
// Created by ArthurMeng on 2017/12/31.
//

#ifndef GRAPH_SHORTESTPATH_H
#define GRAPH_SHORTESTPATH_H

#include <iostream>
#include <cassert>
#include "DenseGraph.h"
#include "SparseGraph.h"
#include <vector>
#include <stack>
#include <queue>
using namespace std;

template <typename Graph>
class ShortestPath
{
private:
    Graph &G;
    int s;
    int *from;
    bool *visited;
    int *distance;

    void bfs(int v)
    {
        visited[v] = true;

        typename Graph::adjIterator adj(G, v);

        for(int i = adj.begin() ; !adj.end() ; i = adj.next())
            if(!visited[i])
            {
                from[i] = v;
                bfs(i);
            }
    }

public:
    ShortestPath(Graph &graph, int s) : G(graph)
    {
        assert(s >= 0 && s < G.V());
        this->s = s;
        visited = new bool[G.V()];
        from = new int[G.V()];
        distance = new int[G.V()];

        for(int i = 0 ; i < G.V() ; i++)
        {
            visited[i] = false;
            from[i] = -1;
            distance[i] = -1;
        }

        distance[s] = 0;
        queue<int> que;
        que.push(s);
        visited[s] = true;

        while(!que.empty())
        {
            int p = que.front();
            que.pop();
            //visited[p] = true;

            typename Graph::adjIterator adj(G, p);

            for(int i = adj.begin() ; !adj.end() ; i = adj.next())
                if(!visited[i])
                {
                    from[i] = p;
                    que.push(i);
                    visited[i] = true;
                    distance[i] = distance[p] + 1;
                }
        }


    }

    ~ShortestPath()
    {
        delete[] visited;
        delete[] from;
        delete[] distance;
    }

    void shortestPath(int w, vector<int> &vec)
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

    int length(int w)
    {
        assert(hasPath(w));
        return distance[w];
    }

    void showShortestPath(int w)
    {
        assert(w >= 0 && w < G.V());
        vector<int> vec;

        shortestPath(w, vec);
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

#endif //GRAPH_SHORTESTPATH_H
