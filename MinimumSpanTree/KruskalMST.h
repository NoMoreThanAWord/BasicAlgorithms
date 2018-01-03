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
using namespace std;

//KruskalMST 算法，对所有边进行排序，从小到大开始取，如果围成环就跳过，没成环就继续，直到所有边都被取出(其实不用到这个地步，当生成树集合中边的个数等于点的个数减一就可以停止了)
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
        for(int i = 0 ; i < graph.V() ; i++)//把所有的边都遍历
        {
            typename Graph::adjIterator adj(graph, i);
            for(Edge<Weight> *p = adj.begin() ; !adj.end() ; p = adj.next())
            {
                if(p->v() < p->w())//同一条边都存了两遍，只取一个方向的边
                    pq.insert(*p);
            }
        }


        UF5::UnionFind uf(graph.V());
        while(!pq.isEmpty() && mst.size() < graph.V() -1)
        {
            Edge<Weight> temp = pq.extractMin();//取出最小边
            if(uf.isConnected(temp.v(), temp.w()))//成环，继续
                continue;
            else//未成环
            {
                mst.push_back(temp);//找到了，加入 mst 集合中
                uf.unionElements(temp.v(), temp.w());//并把边的两端点并入同一集合
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
