//
// Created by ArthurMeng on 2018/1/1.
//

#ifndef MINIMUMSPANTREE_KRUSKALMST_H
#define MINIMUMSPANTREE_KRUSKALMST_H

#include "MinHeap.h"
#include "RoadCompression.h"
#include <iostream>
#include <vector>
#include "Edge.h"
#include "UF.h"
using namespace std;

template <typename Graph, typename Weight>
class KruskalMST
{
private:
    vector<Edge<Weight>> mst;
    Weight mstWeight;

public:
    KruskalMST(Graph &graph)
    {
        MinHeap<Edge<Weight>> pq(graph.E());
        for(int i = 0 ; i < graph.V() ; i++)
        {
            typename Graph::adjIterator adj(graph, i);
            for(Edge<Weight> *p = adj.begin() ; !adj.end() ; p = adj.next())
            {
                if(p->v() < p->w())
                    pq.insert(*p);
            }
        }


        UF5::UnionFind uf(graph.V());
        while(!pq.isEmpty() && mst.size() < graph.V() -1)
        {
            Edge<Weight> temp = pq.extractMin();
            if(uf.isConnected(temp.v(), temp.w()))
                continue;
            else
            {
                mst.push_back(temp);
                uf.unionElements(temp.v(), temp.w());
            }

        }

        mstWeight = mst[0].wt();
        for(int i = 1 ; i < mst.size() ; i++)
            mstWeight += mst[i].wt();
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

#endif //MINIMUMSPANTREE_KRUSKALMST_H
