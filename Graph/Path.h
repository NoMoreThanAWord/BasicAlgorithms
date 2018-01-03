//
// Created by ArthurMeng on 2017/12/30.
//

#ifndef GRAPH_PATH_H
#define GRAPH_PATH_H

#include <iostream>
#include <cassert>
#include "DenseGraph.h"
#include "SparseGraph.h"
#include <vector>
#include <stack>
using namespace std;
/*深度优先与寻路算法，以某节点一次深度遍历的过程，就把该结点所相连的所有节点都遍历了一遍，也就求出了源点到相应结点的一条路径(不保证最短)*/
template <typename Graph>
class Path
{
private:
    Graph &G;
    int s;//源点，寻路的起始点
    int *from;//溯源索引，指示某下标的结点的来向
    bool *visited;//指示某下标的结点是否已经被访问过

    void dfs(int v)
    {
        visited[v] = true;

        typename Graph::adjIterator adj(G, v);

        for(int i = adj.begin() ; !adj.end() ; i = adj.next())
            if(!visited[i])
            {
                from[i] = v;//在进入 dfs 递归前维护 from 数组
                dfs(i);
            }
    }

public:
    Path(Graph &graph, int s) : G(graph)
    {
        assert(s >= 0 && s < G.V());
        this->s = s;
        visited = new bool[G.V()];
        from = new int[G.V()];

        for(int i = 0 ; i < G.V() ; i++)
        {
            visited[i] = false;
            from[i] = -1;//初始化所有节点都没有来向 -1
        }

        dfs(s);

    }

    ~Path()
    {
        delete[] visited;
        delete[] from;
    }

    void path(int w, vector<int> &vec)//把从源点到某点的路径存在一个 vector 中
    {
        assert(hasPath(w));//先判断路径存在
        stack<int> sta;

        int p = w;
        while(p != -1)//从 from 数组倒推出到 w 源点 s 的路径
        {
            sta.push(p);
            p = from[p];
        }

        vec.clear();
        while(!sta.empty())
        {
            vec.push_back(sta.top());
            sta.pop();
        }
    }

    bool hasPath(int w)//判断从源点到某点是否有路径(只要被遍历过，肯定存在路径)
    {
        assert(w >= 0 && w < G.V());

        return visited[w];
    }

    void showPath(int w)//打印输出从源点到某点的路径
    {
        assert(w >= 0 && w < G.V());
        vector<int> vec;

        path(w, vec);
        for(int i = 0 ; i < vec.size() ; i++)
        {
            cout<<vec[i];
            if(i == vec.size()-1)
                cout<<endl;
            else
                cout<<" -> ";
        }
    }
};

#endif //GRAPH_PATH_H