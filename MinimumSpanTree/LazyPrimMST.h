//
// Created by ArthurMeng on 2018/1/1.
//

#ifndef MINIMUMSPANTREE_LAZYPRIMMST_H
#define MINIMUMSPANTREE_LAZYPRIMMST_H

#include "MinHeap.h"
#include <iostream>
#include "Edge.h"
#include <cassert>
#include <vector>
using namespace std;

template <typename Graph, typename Weight>
class LazyPrimMST
{
private:
    Graph &G;
    MinHeap<Edge<Weight>> pq;
    bool *marked;
    vector<Edge<Weight>> mst;
    Weight mstWeight;

    void visit(int v)
    {
        assert(!marked[v]);
        marked[v] = true;

        typename Graph::adjIterator adj(G, v);
        for(Edge<Weight>* p = adj.begin() ; !adj.end() ; p = adj.next())
            if(!marked[p->other(v)])
                pq.insert(*p);
    }

public:
    LazyPrimMST(Graph &graph) : G(graph) , pq(MinHeap<Edge<Weight>>(graph.E()))
    {
        marked = new bool[G.V()];
        for(int i = 0 ; i < G.V() ; i++)
            marked[i] = false;
        mst.clear();

        visit(0);

        while(!pq.isEmpty())
        {
            Edge<Weight> temp = pq.extractMin();
            if(marked[temp.w()] == marked[temp.v()])
                continue;
            else
                mst.push_back(temp);
            if(marked[temp.v()])
                visit(temp.w());
            else
                visit(temp.v());
        }

        mstWeight = mst[0].wt();
        for(int i = 1 ; i < mst.size() ; i++)
            mstWeight += mst[i].wt();

    }

    ~LazyPrimMST()
    {
        delete[] marked;
    }

    vector<Edge<Weight>> mstEdges()
    {
        return mst;
    }

    Weight result()
    {
        return mstWeight;
    }
};


#endif //MINIMUMSPANTREE_LAZYPRIMMST_H
