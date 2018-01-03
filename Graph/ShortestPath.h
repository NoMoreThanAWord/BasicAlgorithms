//
// Created by ArthurMeng on 2017/12/31.
//

#ifndef GRAPH_SHORTESTPATH_H
#define GRAPH_SHORTESTPATH_H

#include <iostream>
#include <cassert>
#include "DenseGraph.h"
#include "SparseGraph.h"
#include <vector>
#include <stack>
#include <queue>
using namespace std;
/*无权图最短路径与广度优先遍历，广度优先类似于同心圆或水中的波纹扩散的过程，需要把每一圈的结点同时存起来，还要保证在内圈遍历结束前决不能访问外圈*/
template <typename Graph>
class ShortestPath
{
private:
    Graph &G;
    int s;//源点
    int *from;
    bool *visited;
    int *distance;//距离索引，指示从源点到某下标的距离

    void bfs(int v)
    {
        visited[v] = true;

        typename Graph::adjIterator adj(G, v);

        for(int i = adj.begin() ; !adj.end() ; i = adj.next())
            if(!visited[i])
            {
                from[i] = v;
                bfs(i);
            }
    }

public:
    ShortestPath(Graph &graph, int s) : G(graph)
    {
        assert(s >= 0 && s < G.V());
        this->s = s;
        visited = new bool[G.V()];
        from = new int[G.V()];
        distance = new int[G.V()];

        for(int i = 0 ; i < G.V() ; i++)
        {
            visited[i] = false;
            from[i] = -1;
            distance[i] = -1;//初始化从源点到所有点的距离都为 -1
        }

        distance[s] = 0;//源点到自己的距离为 0
        queue<int> que;//辅助队列
        que.push(s);//源点入队(最内层)
        visited[s] = true;//源点置于已访问

        while(!que.empty())//由队列构建内外层的结构，当结构不为空时不断的从内层取点进行遍历
        {
            int p = que.front();//最内层取点
            que.pop();
            //visited[p] = true;

            typename Graph::adjIterator adj(G, p);//遍历未被访问过邻点，放入队列，作为稍外一层

            for(int i = adj.begin() ; !adj.end() ; i = adj.next())
                if(!visited[i])
                {
                    from[i] = p;//维护 from 数组
                    que.push(i);//加入队列，成为外层
                    visited[i] = true;//加入队列时迟早要被访问，置为 true
                    distance[i] = distance[p] + 1;//新的一层距离为 内层 +1(无权图的边长默认都为 1 )
                }
        }


    }

    ~ShortestPath()
    {
        delete[] visited;
        delete[] from;
        delete[] distance;
    }

    void shortestPath(int w, vector<int> &vec)
    {
        assert(hasPath(w));
        stack<int> sta;

        int p = w;
        while(p != -1)
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

    bool hasPath(int w)
    {
        assert(w >= 0 && w < G.V());

        return visited[w];
    }

    int length(int w)//返回源点到某点的最短距离
    {
        assert(hasPath(w));
        return distance[w];
    }

    void showShortestPath(int w)//打印输出最短路径
    {
        assert(w >= 0 && w < G.V());
        vector<int> vec;

        shortestPath(w, vec);
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

#endif //GRAPH_SHORTESTPATH_H
