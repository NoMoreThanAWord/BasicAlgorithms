//
// Created by ArthurMeng on 2017/12/29.
//

#ifndef UNIONFIND_OPTMIZEBYRANK_H
#define UNIONFIND_OPTMIZEBYRANK_H

#include <iostream>
#include <cassert>
/*靠分组的 size 来决定归并顺序有时候不准，极端情况下 size 很大的树可能高度很小，size 很小的树可能高度很大，根据 size 归并后可能时树的高度
增加，这时如果靠树的高度的来归并，可以时归并后的树高度不增长，从而不增加 find 跟 union 的成本*/
namespace UF4
{
    class UnionFind {
    private:
        int *parent;
        int count;
        int *rank;//舍弃了 size , rank 保存分组树的高度

    public:
        UnionFind(int n) {
            parent = new int[n];
            count = n;
            rank = new int[n];

            for (int i = 0; i < n; i++) {
                rank[i] = 1;//初始化所有节点自成一个树，高度为 1
                parent[i] = i;
            }

        }

        ~UnionFind() {
            delete[] parent;
            delete[] rank;
        }

        int find(int i) {
            assert(i >= 0 && i <= count);
            while (parent[i] != i)
                i = parent[i];

            return i;
        }

        bool isConnected(int p, int q) {

            return find(p) == find(q);
        }

        void unionElements(int p, int q) {
            int pRoot = find(p);
            int qRoot = find(q);

            if (pRoot == qRoot)
                return;

            if (rank[pRoot] > rank[qRoot])//两个树高度不相同时，把高度较低的树归并到高度较高的树上(两树高度相差 1 时，归并后子树的高度相同)
                parent[qRoot] = pRoot;

            else if(rank[qRoot] < rank[pRoot])
                parent[pRoot] = qRoot;
            else//两树高度相同时，归并会带来树高度的加一
            {
                parent[pRoot] = qRoot;
                rank[qRoot] += 1;
            }


        }
    };
}

#endif //UNIONFIND_OPTMIZEBYRANK_H
