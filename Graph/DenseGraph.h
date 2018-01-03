//
// Created by ArthurMeng on 2017/12/30.
//

#ifndef GRAPH_DENSEGRAPH_H
#define GRAPH_DENSEGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class DenseGraph
{
private:
    int n;//the number of vertex
    int m;//the number of edge
    bool directed;//weather the graph is directed or not
    vector<vector<bool>> g;//(i,j)存在边，则 g[i][j] 为 true

public:
    DenseGraph(int n, bool directed)
    {
        this->n = n;
        this->directed = directed;
        this->m = 0;
        for(int i = 0 ; i < n ; i++)//与稀疏图不同的是，一维 vector 的大小在初始化时就都确定了，为结点个数的大小(n)，初始值都为 false，两两结点间都不存在边
            g.push_back(vector<bool>(n, false));
    }

    ~DenseGraph()
    {
    }

    int V(){return n;}
    int E(){return m;}

    bool hasEdge(int v, int w)//稠密图采用了邻接矩阵的存储方式，判断两结点存在边只需要 o1 的时间
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        return g[v][w];
    }

    void addEdge(int v, int w)//稠密图判断两结点间存在边比较高效，可以避免平行边
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        if(hasEdge(v, w))//已经存在边了，直接返回
            return;

        g[v][w] = true;
        if(!directed)//为无向图，对称添加边
            g[w][v] = true;
        m++;//更新边数
    }

    void show()//以邻接矩阵打印展示稠密图
    {
        for(int i = 0 ; i < n ; i++)
        {
            for(int j = 0 ; j < n ; j++)
                cout<<g[i][j]<<"\t";
            cout<<endl;
        }
    }

    class adjIterator//稠密图的相邻节点迭代器比起稀疏图来说速度较慢 (稀疏图的二维 vector 中存储的都是相邻节点的下标，而稠密图的二维 vector 中存储的是与所有节点是否相邻，要遍历相邻节点必须遍历判断)
    {
    private:
        DenseGraph &G;
        int v;
        int index;

    public:
        adjIterator(DenseGraph &graph, int v) : G(graph)
        {
            this->v = v;
            index = -1;
        }

        int begin()
        {
            index = -1;
            return next();
        }

        int next()
        {
            for(index++ ; index < G.V() ; index++ )//向后遍历(index++)，发现值为 true 返回
                if(G.g[v][index] == true)
                    return index;
            return -1;
        }

        bool end()
        {
            return index >= G.V();
        }
    };
};

#endif //GRAPH_DENSEGRAPH_H
