//
// Created by ArthurMeng on 2017/12/31.
//

#ifndef MINIMUMSPANTREE_EDGE_H
#define MINIMUMSPANTREE_EDGE_H

#include <iostream>
#include <cassert>
using namespace std;

/*对于最小生成树问题，处理的图不再是无权图，而是有权图，这里我们构造一个边类方便之后处理关于有权图的操作*/

template <typename Weight>//模板类，权重的类型不固定
class Edge
{
private:
    int a,b;//边的始点与终点
    Weight weight;//边的权重

public:
    Edge(int a, int b, Weight weight)
    {
        this->weight = weight;
        this->a = a;
        this->b = b;
    }
    Edge(){}//万分重要的无参构造函数，没有无参构造函数无法完成图的初始化

    int v(){return a;}//获得起始点下标
    int w(){return b;}//获得终点下标

    Weight wt(){return weight;}//获得边的权重

    int other(int x)//给出边的一点，返回另一点
    {
        assert(x == a || x == b);//确保给出的确实是边中的点
        return x == a ? b : a;
    }

    friend ostream& operator<<(ostream &os, const Edge &e)//重载输出方法，“始边-终边:权重”
    {
        os<<e.a<<"-"<<e.b<<": "<<e.weight;
        return os;
    }

    //重载边的比较方法，按照权值的大小来比较
    bool operator<(Edge<Weight>& e)
    {
        return weight < e.wt();
    }

    bool operator<=(Edge<Weight>& e)
    {
        return weight <= e.wt();
    }

    bool operator>(Edge<Weight>& e)
    {
        return weight > e.wt();
    }

    bool operator>=(Edge<Weight>& e)
    {
        return weight >= e.wt();
    }

    bool operator==(Edge<Weight>& e)
    {
        return weight == e.wt();
    }
};

#endif //MINIMUMSPANTREE_EDGE_H
