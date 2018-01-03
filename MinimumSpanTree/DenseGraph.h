//
// Created by ArthurMeng on 2017/12/30.
//

#ifndef GRAPH_DENSEGRAPH_H
#define GRAPH_DENSEGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>
#include "Edge.h"

using namespace std;

template <typename Weight>
class DenseGraph
{
private:
    int n;//the number of vertex
    int m;//the number of edge
    bool directed;
    vector<vector<Edge<Weight>*>> g;

public:
    DenseGraph(int n, bool directed)
    {
        this->n = n;
        this->directed = directed;
        this->m = 0;
        for(int i = 0 ; i < n ; i++)
            g.push_back(vector<Edge<Weight>*>(n, NULL));//vector 的第二维压入 n 个空值占位
    }

    ~DenseGraph()
    {
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < n ; j++)
                if(g[i][j])//不为空值，释放空间
                    delete g[i][j];
    }

    int V(){return n;}
    int E(){return m;}

    bool hasEdge(int v, int w)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        return g[v][w] != NULL;//占位不为空即存在边
    }

    void addEdge(int v, int w, Weight weight)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        if(hasEdge(v, w))//已经存在边默认操作为删除后重新添加(与更新权值其实是一样的)
        {
            delete g[v][w];
            if(!directed)
                delete g[w][v];
            m--;//删除操作更新边值
        }


        g[v][w] = new Edge<Weight>(v, w, weight);//添加边
        if(!directed)//无向图对称添加
            g[w][v] = new Edge<Weight>(w, v, weight);
        m++;//更新边值
    }

    void show()//邻接矩阵打印展示稠密图
    {
        for(int i = 0 ; i < n ; i++)
        {
            for(int j = 0 ; j < n ; j++)
                if(g[i][j])
                    cout<<g[i][j]->wt()<<"\t";
                else
                    cout<<"NULL"<<"\t";
            cout<<endl;
        }
    }

    class adjIterator
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

        Edge<Weight>* begin()
        {
            index = -1;
            return next();
        }

        Edge<Weight>* next()
        {
            for(index++ ; index < G.V() ; index++ )
                if(G.g[v][index])
                    return G.g[v][index];
            return NULL;
        }

        bool end()
        {
            return index >= G.V();
        }
    };
};

#endif //GRAPH_DENSEGRAPH_H
