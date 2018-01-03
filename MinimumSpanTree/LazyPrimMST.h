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
//切分定理:切边中权重最小的一定属于最小生成树。从一个点选为切分开始，选出最小的切边，把切边的另一个端点加入切分，形成新的切分，不断重复上述过程，直到所有点都加入了切分中

//lazyPrim lazy 体现在每次从优先队列中取出的边都要再次判断是否为切边，没能保证在加入到优先队列中的全部是切边
template <typename Graph, typename Weight>
class LazyPrimMST
{
private:
    Graph &G;
    MinHeap<Edge<Weight>> pq;//优先队列，用来加入切分，方便在切分中取出最小的边(之前在 Edge 类中重载的比较方法能用得上了)
    bool *marked;//标记某点已经加入切分中了
    vector<Edge<Weight>> mst;//最小生成树的边集合
    Weight mstWeight;//最小生成树的权值和

    void visit(int v)
    {
        assert(!marked[v]);//确保未被加入切分
        marked[v] = true;//加入切分

        typename Graph::adjIterator adj(G, v);
        for(Edge<Weight>* p = adj.begin() ; !adj.end() ; p = adj.next())
            if(!marked[p->other(v)])//遍历临边，寻找切边，加入优先队列
                pq.insert(*p);
    }

public:
    LazyPrimMST(Graph &graph) : G(graph) , pq(MinHeap<Edge<Weight>>(graph.E()))
    {
        marked = new bool[G.V()];
        for(int i = 0 ; i < G.V() ; i++)
            marked[i] = false;//所有点都未加入切分
        mst.clear();//清空 mst 集合

        visit(0);

        while(!pq.isEmpty())
        {
            Edge<Weight> temp = pq.extractMin();//取出优先队列中中权值最小的
            if(marked[temp.w()] == marked[temp.v()])//在不断构建新的切分的过程中，优先队列中原有的切边可能会失效，所以在取出最小边时要二次判断取出的是否为切边，如果不是，抛掉再取
                continue;
            else
                mst.push_back(temp);//找到最小切边，加入最小生成树集合
            if(marked[temp.v()])//切边横跨切分两边，把未加入切分的那一端加入切分重复上述过程
                visit(temp.w());
            else
                visit(temp.v());
        }

        mstWeight = mst[0].wt();//计算最小生成树的权值
        for(int i = 1 ; i < mst.size() ; i++)
            mstWeight += mst[i].wt();

    }

    ~LazyPrimMST()
    {
        delete[] marked;
    }

    vector<Edge<Weight>> mstEdges()//返回最小生成树边集合
    {
        return mst;
    }

    Weight result()//返回最小生成树权值
    {
        return mstWeight;
    }
};


#endif //MINIMUMSPANTREE_LAZYPRIMMST_H
