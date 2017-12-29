//
// Created by ArthurMeng on 2017/12/29.
//

#ifndef UNIONFIND_ARRAYUNIONFIND_H
#define UNIONFIND_ARRAYUNIONFIND_H

#include <iostream>
#include <cassert>
//由数组实现的并查集，在同一个集合的元素有相同的分组号
namespace UF1
{
    class UnionFind
    {
    private:
        int *id;//分组号数组
        int count;//并查集大小

    public:
        UnionFind(int n)
        {
            id = new int[n];//开空间
            count = n;

            for(int i = 0 ; i < n ; i++)
                id[i] = i;//初始化时所有元素的分组都不同，各自为一组
        }

        ~UnionFind()
        {
            delete[] id;
        }

        int find(int i)// 查操作 o1 时间
        {
            assert(i >= 0 && i <= count);
            return id[i];//返回元素所在的分组
        }

        bool isConnected(int p, int q)//两元素是否在一组
        {

            return find(p) == find(q);//分组号是否相同，相同即为一组
        }

        void unionElements(int p, int q)//并操作 oN 时间
        {
            int pId = find(p);
            int qId = find(q);

            if(pId == qId)//分组相同就退出
                return;

            for(int i = 0 ; i < count ; i++)//分组同化(同化操作的遍历降低了效率)
            {
                if(id[i] == pId)
                    id[i] = qId;
            }
        }
    };
}

#endif //UNIONFIND_ARRAYUNIONFIND_H
