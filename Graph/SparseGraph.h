//
// Created by ArthurMeng on 2017/12/30.
//

#ifndef GRAPH_SPARSEGRAPH_H
#define GRAPH_SPARSEGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
class SparseGraph//稀疏图(边的条数远小于定点数)
{
private:
    int n;//点数
    int m;//边数
    bool directed;//是否为有向图
    vector<vector<int>> g;//存储每个节点相邻节点的下标(总共有 n 个向量),邻接表存储

public:
    SparseGraph(int n, bool directed)
    {
        this->n = n;
        this->m = 0;//边数初始化为零
        this->directed = directed;
        for(int i = 0 ; i < n ; i++)
            g.push_back(vector<int>());//放入 n (边数)个空向量，占位置
    }

    ~SparseGraph()
    {
    }

    int V(){return n;}// return the number of vertexs
    int E(){return m;}//return the number fo edges

    bool hasEdge(int v, int w)
    {
        assert(v >= 0 && v < n);//确保边的输入有效
        assert(w >= 0 && w < n);
        for(int i = 0 ; i < g[v].size() ; i++)//邻接表存储判断某节点的临边只能遍历该节点对应的向量。
            if(g[v][i] == w)
                return true;
        return false;
    }

    void addEdge(int v, int w)//添加边，本次实现没有考虑去除平行边的情况(为了性能考虑)
    {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        g[v].push_back(w);//有向图存一次，无向图存两次
        if(!directed && v != w)
            g[w].push_back(v);

        m++;//更新边数
    }

    void show()//以邻接表的方式打印展示稀疏图
    {
        for(int i = 0 ; i < n ; i++)
        {
            cout<<"vertex "<<i<<":\t";
            for(int j = 0 ; j < g[i].size() ; j++)
                cout<<g[i][j]<<"\t";
            cout<<endl;
        }
    }

    class adjIterator//临边节点迭代器
    {
    private:
        SparseGraph &G;//存储要迭代的图的引用
        int index;//指示当前迭代到哪个相邻节点
        int v;//要对哪个结点进行相邻节点迭代

    public:
        adjIterator(SparseGraph &graph, int v) : G(graph)//初始化列表
        {
            this->index = 0;//迭代起点为 下标零
            this->v = v;
        }

        int begin()//返回初始相邻节点
        {
            index = 0;//每次下标归零
            if(G.g[v].size())//相邻节点数不为零
                return G.g[v][index];
            return -1;
        }

        int next()//返回下一个相邻节点
        {
            index++;
            if(index < G.g[v].size())
                return G.g[v][index];
            return -1;
        }

        bool end()//是否迭代结束(把相邻节点的相邻全部遍历完毕)
        {
            return index >= G.g[v].size();
        }
    };
};

#endif //GRAPH_SPARSEGRAPH_H
