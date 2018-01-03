//
// Created by ArthurMeng on 2017/12/30.
//

#ifndef GRAPH_COMPONENT_H
#define GRAPH_COMPONENT_H

#include <iostream>
#include <cassert>
#include "DenseGraph.h"
#include "SparseGraph.h"
using namespace std;
/*深度优先遍历与图的联通分量,对某一结点进行深度优先遍历后，与该结点处于同一联通分量的结点就都被遍历过了。剩下没被遍历的结点就处于另外的联通分量中。对所有的结点，能进行几次深度优先遍历
图中就存在几个联通分量(深度优先遍历过的结点要被标记)*/
template <typename Graph>
class Component
{
private:
    Graph &G;
    int ccount;//联通分量计数
    int *id;//结点分类指示，在同一个联通分量的结点彼此是相连同的，拥有相同的 id 号
    bool *visited;//结点遍历指示，某节点被遍历过，把该下标的值置为 true

    void dfs(int v)//对某节点进行深度优先遍历(如果该结点的相邻节点没有被访问过的话对相邻节点进行深度优先遍历)
    {
        visited[v] = true;//标记为访问过
        id[v] = ccount;//拥有同一个ccount说明定点在同一个联通分量中

        typename Graph::adjIterator adj(G, v);

        for(int i = adj.begin() ; !adj.end() ; i = adj.next())
            if(!visited[i])
                dfs(i);
    }

public:
    Component(Graph &graph) : G(graph)
    {
        ccount = 0;
        visited = new bool[G.V()];
        id = new int[G.V()];

        for(int i = 0 ; i < G.V() ; i++)
        {
            id[i] = -1;//默认分组为 -1
            visited[i] = false;//默认所有节点初始都没有被访问过
        }


        for(int i = 0 ; i < G.V() ; i++)
        {
            if(!visited[i])
            {
                dfs(i);
                ccount++;//每进行一次 dfs 后联通分量数增加
            }
        }
    }

    ~Component()
    {
        delete[] visited;
        delete[] id;
    }

    int count()//返回联通分量个数
    {
        return ccount;
    }

    bool isConnected(int v, int w)//判断两结点是否相联通
    {
        assert(v >= 0 && v < G.V());
        assert(w >= 0 && w < G.V());

        return id[v] == id[w];//拥有同一个ccount说明定点在同一个联通分量中，即向量同
    }
};

#endif //GRAPH_COMPONENT_H
