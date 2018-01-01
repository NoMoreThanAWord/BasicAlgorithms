//
// Created by ArthurMeng on 2017/12/29.
//

#ifndef UNIONFIND_ROADCOMPRESSION_H
#define UNIONFIND_ROADCOMPRESSION_H

#include <iostream>
#include <cassert>
/*前面的优化大多针对了 union 操作导致树的不平衡，如果要归并的两部分本事就不平衡(如链状树)。如果能把长链拆分成一个个的单链就能有效的降低树的高度*/
namespace UF5
{
    class UnionFind {
    private:
        int *parent;
        int count;
        int *rank;

    public:
        UnionFind(int n) {
            parent = new int[n];
            count = n;
            rank = new int[n];

            for (int i = 0; i < n; i++) {
                rank[i] = 1;
                parent[i] = i;
            }

        }

        ~UnionFind() {
            delete[] parent;
            delete[] rank;
        }

        int find(int i)
        {
            assert(i >= 0 && i <= count);
//            while (parent[i] != i) //不是根节点(存在父节点)
//            {
//                parent[i] = parent[parent[i]];//子节点的父节点指向父节点的父节点的父节点(子节点直接指向了爷节点)
//                i = parent[i];//跳过了父节点，两步一跳(优化不彻底，由于有跳过部分节点)
//            }
//            return i;//i 最后为根节点

            if(parent[i] != i)//不是根节点(存在父节点)
                parent[i] = find(parent[i]);//递归压缩，不跳过任何节点
            return parent[i];//能直通根节点，路上的所有节点都指向根节点

        }

        bool isConnected(int p, int q) {

            return find(p) == find(q);
        }

        void unionElements(int p, int q) {
            int pRoot = find(p);
            int qRoot = find(q);

            if (pRoot == qRoot)
                return;

            if (rank[pRoot] > rank[qRoot])
                parent[qRoot] = pRoot;

            else if(rank[qRoot] < rank[pRoot])
                parent[pRoot] = qRoot;
            else
            {
                parent[pRoot] = qRoot;
                rank[qRoot] += 1;
            }


        }
    };
}

#endif //UNIONFIND_ROADCOMPRESSION_H
