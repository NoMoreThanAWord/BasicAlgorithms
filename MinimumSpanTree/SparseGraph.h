//
// Created by ArthurMeng on 2017/12/30.
//

#ifndef GRAPH_SPARSEGRAPH_H
#define GRAPH_SPARSEGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>
#include "Edge.h"

using namespace std;
//带权稀疏图
template <typename Weight>
class SparseGraph
{
private:
    int n;
    int m;
    bool directed;
    vector<vector<Edge<Weight>*>> g;//改造后的二维 vector 中存放的不在是 bool 值，而是 Edge 的指针

public:
    SparseGraph(int n, bool directed)
    {
        this->n = n;
        this->m = 0;
        this->directed = directed;
        for(int i = 0 ; i < n ; i++)
            g.push_back(vector<Edge<Weight>*>());//需要 Edge 类的无参构造函数
    }

    ~SparseGraph()
    {
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < g[i].size() ; j++)
                delete g[i][j];
    }

    int V(){return n;}
    int E(){return m;}

    bool hasEdge(int v, int w)//查找边是否存在还是要遍历
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        for(int i = 0 ; i < g[v].size() ; i++)
            if(g[v][i]->other(v) == w)//另一端为 w，确认边存在
                return true;
        return false;
    }

    void addEdge(int v, int w, Weight weight)//同样没有处理平行边的问题
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        g[v].push_back(new Edge<Weight>(v, w, weight));
        if(!directed && v != w)//无向图添加对称边
            g[w].push_back(new Edge<Weight>(w, v, weight));

        m++;//更新边数
    }

    void show()//邻接表打印展示稀疏图
    {
        for(int i = 0 ; i < n ; i++)
        {
            cout<<"vertex "<<i<<":\t";
            for(int j = 0 ; j < g[i].size() ; j++)
                cout<<"(to:"<<g[i][j]->w()<<",wt:"<<g[i][j]->wt()<<")\t";
            cout<<endl;
        }
    }

    class adjIterator
    {
    private:
        SparseGraph &G;
        int index;
        int v;

    public:
        adjIterator(SparseGraph &graph, int v) : G(graph)
        {
            this->index = 0;
            this->v = v;
        }

        Edge<Weight>* begin()//返回值不同
        {
            index = 0;
            if(G.g[v].size())//确认 size
                return G.g[v][index];
            return NULL;
        }

        Edge<Weight>* next()
        {
            index++;
            if(index < G.g[v].size())//确定没有越界
                return G.g[v][index];
            return NULL;
        }

        bool end()
        {
            return index >= G.g[v].size();
        }
    };
};

#endif //GRAPH_SPARSEGRAPH_H
