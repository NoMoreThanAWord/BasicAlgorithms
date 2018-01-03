//
// Created by ArthurMeng on 2018/1/1.
//

#ifndef MINIMUMSPANTREE_PRIMMST_H
#define MINIMUMSPANTREE_PRIMMST_H

#include "IndexMinHeap.h"
#include <iostream>
#include "Edge.h"
#include <cassert>
#include <vector>
using namespace std;
//prim 改进了 lazyPrim 从优先队列中取出边需要二次判断的问题,最小生成树中同一点所对应的切分只保存最小的，这样在优先队列取出时不用再二次判断了
template <typename Graph, typename Weight>
class PrimMst
{
private:
    Graph &G;
    IndexMinHeap<Weight> ipq;//某边所对应的最小切边的权值
    vector<Edge<Weight>*> edgeTo;//存放到某点的权值最短边
    vector<Edge<Weight>> mst;
    bool *marked;
    Weight mstWeight;

    void visit(int v)
    {
        assert(!marked[v]);
        marked[v] = true;
        typename Graph::adjIterator adj(G, v);
        for(Edge<Weight> *p = adj.begin() ; !adj.end() ; p = adj.next())
        {
            if(marked[p->other(v)])//不是切边继续
                continue;
            else//是切边
            {
                if(edgeTo[p->other(v)] == NULL)//从未出现过的边
                {
                    edgeTo[p->other(v)] = p;
                    ipq.insert(p->other(v), p->wt());//插入
                }
                else//以前出现过的边
                {
                    if(p->wt() < ipq.getItem(p->other(v)))//比较大小，保留权值较小的边
                    {
                        edgeTo[p->other(v)] = p;
                        ipq.change(p->other(v), p->wt());
                    }
                }
            }
        }
    }

public:
    PrimMst(Graph &graph) : G(graph) , ipq(IndexMinHeap<double>(graph.V()))
    {
        marked = new bool[G.V()];
        for(int i = 0 ; i < G.V() ; i++)
        {
            marked[i] = false;
            edgeTo.push_back(NULL);
        }
        mst.clear();

        visit(0);

        while(!ipq.isEmpty())
        {
            int min = ipq.extractMinIndex();//取出时不用再进行判断
            assert(edgeTo[min]);
            Edge<Weight> temp = *edgeTo[min];
            mst.push_back(temp);
            visit(min);
        }

        mstWeight = mst[0].wt();
        for(int i = 1 ; i < mst.size() ; i++)
            mstWeight += mst[i].wt();
    }

    ~PrimMst()
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

#endif //MINIMUMSPANTREE_PRIMMST_H
