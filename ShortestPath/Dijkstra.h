//
// Created by ArthurMeng on 2018/1/2.
//

#ifndef SHORTESTPATH_DIJKSTRA_H
#define SHORTESTPATH_DIJKSTRA_H

#include <iostream>
#include "Edge.h"
#include <stack>
#include <vector>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "IndexMinHeap.h"
using namespace std;

template <typename Graph, typename Weight>
class Dijkstra
{
    int s;
    Graph &G;

    Weight *distTo;
    bool *marked;
    vector<Edge<Weight>*> from;

public:
    Dijkstra(Graph &graph, int s) : G(graph)
    {
        assert(s >= 0 && s < G.V());
        this->s = s;
        distTo = new Weight[G.V()];
        marked = new bool[G.V()];

        for(int i = 0 ; i < G.V() ; i++)
        {
            distTo[i] = Weight();
            marked[i] = false;
            from.push_back(NULL);
        }

        IndexMinHeap<Weight> ipq(G.V());
        marked[s] = true;
        distTo[s] = Weight();
        from[s] = new Edge<Weight>(s, s, 0);
        ipq.insert(s, 0);

        while(!ipq.isEmpty())
        {
            int v = ipq.extractMinIndex();
            marked[v] = true;
            typename Graph::adjIterator adj(G, v);
            for(Edge<Weight> *p = adj.begin() ; !adj.end() ; p = adj.next())
            {
                if(!marked[p->w()])
                {
                    if(from[p->w()] == NULL || distTo[p->w()] > (distTo[p->v()] + p->wt()) )
                    {
                        distTo[p->w()] = distTo[p->v()] + p->wt();
                        if(!ipq.contain(p->w()))
                            ipq.insert(p->w(), distTo[p->w()]);
                        else
                            ipq.change(p->w(), distTo[p->w()]);
                        from[p->w()] = p;
                    }
                }
            }
        }

    }

    ~Dijkstra()
    {
        delete[] distTo;
        delete[] marked;
    }

    Weight shortestPathTo(int w)
    {
        return distTo[w];
    }

    bool hasPathTo(int w)
    {
        return marked[w];
    }

    void shortestPath(int w, vector<Edge<Weight>> &vec)
    {
//        stack<Edge<Weight>> sta;
//        while(from[w])
//        {
//            sta.push(*from[w]);
//            w = from[w];
//        }
//
//        while(!sta.empty())
//        {
//            Edge<Weight> temp = sta.top();
//            vec.push_back(temp);
//            sta.pop();
//        }

        stack<Edge<Weight>*> sta;
        Edge<Weight> *e = from[w];
        while(e->v() != e->w())
        {
            sta.push(e);
            e = from[e->v()];
        }

        while(!sta.empty())
        {
            e = sta.top();
            vec.push_back(*e);
            sta.pop();
        }
    }

    void showPath(int w)
    {
        assert(w >= 0 && w < G.V());
        vector<Edge<Weight>> vec;
         shortestPath(w,vec);
        for(int i = 0 ; i < vec.size() ; i++)
        {
            cout<<vec[i].v()<<" -> ";
            if(i == vec.size()-1)
                cout<<vec[i].w()<<endl;
        }
    }
};

#endif //SHORTESTPATH_DIJKSTRA_H
