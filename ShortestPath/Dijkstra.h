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
//Dijkstra 单源最短路径算法(不能存在负权边)，经由当前最短节点对其他节点进行松弛操作，不断找出最短节点
template <typename Graph, typename Weight>
class Dijkstra
{
    int s;
    Graph &G;

    Weight *distTo;//到某节点的距离
    bool *marked;
    vector<Edge<Weight>*> from;//某节点的来向边

public:
    Dijkstra(Graph &graph, int s) : G(graph)
    {
        assert(s >= 0 && s < G.V());
        this->s = s;
        distTo = new Weight[G.V()];
        marked = new bool[G.V()];

        for(int i = 0 ; i < G.V() ; i++)
        {
            distTo[i] = Weight();//到所有点的距离都初始化为默认值
            marked[i] = false;
            from.push_back(NULL);//来向边都初始化为空
        }

        IndexMinHeap<Weight> ipq(G.V());
        marked[s] = true;//标记源点为已经访问
        distTo[s] = Weight();//到源点的距离问默认值
        from[s] = new Edge<Weight>(s, s, 0);//源点从自己来
        ipq.insert(s, 0);//插入优先队列

        while(!ipq.isEmpty())
        {
            int v = ipq.extractMinIndex();//取出当前距离源点最近的节点，即为找到最短路径的节点
            marked[v] = true;//标记为已找到最短路径
            typename Graph::adjIterator adj(G, v);
            for(Edge<Weight> *p = adj.begin() ; !adj.end() ; p = adj.next())//对相邻节点进行松弛操作
            {
                if(!marked[p->w()])//未找到最短路径
                {//未曾访问或是经由最短节点后路径边短
                    if(from[p->w()] == NULL || distTo[p->w()] > (distTo[p->v()] + p->wt()) )
                    {
                        distTo[p->w()] = distTo[p->v()] + p->wt();//更新距离
                        if(!ipq.contain(p->w()))//第一次访问执行插入
                            ipq.insert(p->w(), distTo[p->w()]);
                        else//成功松弛执行更新
                            ipq.change(p->w(), distTo[p->w()]);
                        from[p->w()] = p;//记录来向边
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
