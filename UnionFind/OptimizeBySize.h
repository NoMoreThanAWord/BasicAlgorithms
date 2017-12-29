//
// Created by ArthurMeng on 2017/12/29.
//

#ifndef UNIONFIND_OPTIMIZEBYSIZE_H
#define UNIONFIND_OPTIMIZEBYSIZE_H

#include <iostream>
#include <cassert>
/*树形并查集在 find 还有 union 操作上的效率都为 oLogN 但是在 union 时简单的把前一个的组的根指向后一个组的根，如果前一个组的树很大，后一个组
的树很小，其实把后一个组指向前一个组会更省时间(union操作需要寻找两个组的 root ，较小的组寻找根节点的速度比较快)*/
namespace UF3
{
    class UnionFind
    {
    private:
        int *parent;
        int count;
        int *sz;//分组元素个数数组

    public:
        UnionFind(int n)
        {
            parent = new int[n];
            count = n;
            sz = new int[n];

            for(int i = 0 ; i < n ; i++)
            {
                sz[i] = 1;//初始化所有分组元素个数为 1 (千万不能初始化为零，union 操作不会带来 sz 的增长)
                parent[i] = i;
            }

        }

        ~UnionFind()
        {
            delete[] parent;
            delete[] sz;
        }

        int find(int i)// oLogN
        {
            assert(i >= 0 && i <= count);
            while(parent[i] != i)
                i = parent[i];

            return i;
        }

        bool isConnected(int p, int q)
        {

            return find(p) == find(q);
        }

        void unionElements(int p, int q)
        {
            int pRoot = find(p);
            int qRoot = find(q);

            if(pRoot == qRoot)
                return;

            if(sz[pRoot] > sz[qRoot])//把较小的组指向较大的组
            {
                parent[qRoot] = pRoot;
                sz[pRoot] += sz[qRoot];
            }

            else
            {
                parent[pRoot] = qRoot;
                sz[qRoot] += sz[pRoot];
            }
        }
    };
}
#endif //UNIONFIND_OPTIMIZEBYSIZE_H
