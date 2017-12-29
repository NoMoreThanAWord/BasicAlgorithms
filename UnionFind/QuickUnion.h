//
// Created by ArthurMeng on 2017/12/29.
//

#ifndef UNIONFIND_QUICKUNION_H
#define UNIONFIND_QUICKUNION_H
#include <iostream>
#include <cassert>
//采用了树形结构的并查集，每个节点都指向其父节点，根节点的父节点为自己。不同的根节点上的点为不同的分组。根节点的下标为分组的组号
namespace UF2
{
    class UnionFind
    {
    private:
        int *parent;
        int count;

    public:
        UnionFind(int n)
        {
            parent = new int[n];
            count = n;

            for(int i = 0 ; i < n ; i++)
                parent[i] = i;//初始化每个节点的父节点都为自己，各成一组
        }

        ~UnionFind()
        {
            delete[] parent;
        }

        int find(int i)//查操作 oLogN (返回分组所在的根节点的下标)
        {
            assert(i >= 0 && i <= count);
            while(parent[i] != i)//非根判断
                i = parent[i];//顺着父节点不断向上找根

            return i;
        }

        bool isConnected(int p, int q)
        {

            return find(p) == find(q);//看根节点是否相同
        }

        void unionElements(int p, int q)//并操作 oLogN
        {
            int pRoot = find(p);
            int qRoot = find(q);

            if(pRoot == qRoot)
                return;

            parent[pRoot] = qRoot;//更改根父亲节点的指向
        }
    };
}
#endif //UNIONFIND_QUICKUNION_H
