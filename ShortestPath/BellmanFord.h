//
// Created by ArthurMeng on 2018/1/2.
//

#ifndef SHORTESTPATH_BELLMANFORD_H
#define SHORTESTPATH_BELLMANFORD_H

#include "Edge.h"
#include "SparseGraph.h"
#include "DenseGraph.h"
#include <vector>
#include <iostream>
#include <stack>

using namespace std;
//BellmanFord 算法，对所有顶点进行 V-1 轮松弛操作，即可得到所有顶点的最短路径。如果还能进行松弛操作的话，说明图中有负权边。
template <typename Graph, typename Weight>
class BellmanFord
{//不用 marked 数组来记录是否找到最短路径了，只维护 from 数组跟 disTo 数组就行了
private:
    Graph &G;
    int s;
    Weight *distTo;
    vector<Edge<Weight>*> from;
    bool hasNegativeCycle;

    bool detectNegativeCycle()//检查是否有负权环，再对所有节点进行一轮松弛操作，如果可以进行，说明存在，否则没有
    {
        for(int i = 0 ; i < G.V() ; i++)
        {
            typename Graph::adjIterator adj(G, i);
            for(Edge<Weight> *p = adj.begin() ; !adj.end() ; p = adj.next())
            {
                if(from[p->w()] == NULL || distTo[p->w()] > distTo[p->v()] + p->wt())//可以松弛
                {
                    return true;//返回真
                }
            }
        }
        return false;
    }

public:
    BellmanFord(Graph &graph, int s) : G(graph)
    {
        this->s = s;
        distTo = new Weight[G.V()];
        for(int i = 0 ; i < G.V() ; i++)
            from.push_back(NULL);
        distTo[s] = Weight();

        for(int round = 1 ; round < G.V() ; round++)// V-1 轮
        {
            for(int i = 0 ; i < G.V() ; i++)// V 个顶点
            {
                typename Graph::adjIterator adj(G, i);
                for(Edge<Weight> *p = adj.begin() ; !adj.end() ; p = adj.next())//松弛操作
                {
                    if(!from[p->w()] || distTo[p->w()] > distTo[p->v()] + p->wt())
                    {
                        distTo[p->w()] = distTo[p->v()] + p->wt();
                        from[p->w()] = p;
                    }
                }
            }

        }

        hasNegativeCycle = detectNegativeCycle();
    }

    ~BellmanFord()
    {
        delete[] distTo;
    }

    bool negativeCycle()
    {
        return hasNegativeCycle;
    }

    Weight shortestPathTo(int w)
    {
        assert(w >= 0 && w < G.V());
        assert(!hasNegativeCycle);
        return distTo[w];
    }

    bool hasPathTo(int w)
    {
        assert(w >= 0 && w < G.V());
        return from[w] != NULL;
    }

    void shortestPath(int w, vector<Edge<Weight>> &vec)
    {
        assert(w >=0 && w < G.V());
        assert(!hasNegativeCycle);

        stack<Edge<Weight>*> sta;

        Edge<Weight> *e = from[w];

        while(e->v() != this->s)
        {
            sta.push(e);
            e = from[e->v()];
        }

        sta.push(e);

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
        assert(!hasNegativeCycle);
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

#endif //SHORTESTPATH_BELLMANFORD_H
