//
// Created by ArthurMeng on 2017/12/26.
//

#ifndef BINARYSEARCHTREE_BST_H
#define BINARYSEARCHTREE_BST_H

#include <iostream>
#include <queue>
#include <assert.h>

using namespace std;
template <typename Key, typename Value>//类似map的结构，通过key来索引，value是真正的值
class BST
{
private:
    struct Node
    {
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key key, Value value)//传值构造
        {
            this->key = key;
            this->value = value;
            this->left = NULL;
            this->right = NULL;
        }

        Node(Node *p)//复制节点，传引用构造
        {
            this->key = p->key;
            this->value = p->value;
            this->left = p->left;
            this->right = p->right;
        }
    };

    Node *root;//树的根节点
    int count;//树的节点个数

    void destory(Node *root)//递归删除以 root 为根节点的树
    {
        if(root != NULL)
        {
            destory(root->left);
            destory(root->right);
            delete root;
            count--;//删除后节点计数器减一
        }
    }

    Node* insert(Key key, Value value, Node *root)//在以某节点为根的树中插入键值对并返回新的根节点
    {
        if(root == NULL)//找到待插入的位置，新建节点并更新计数器的值
        {
            count++;
            return new Node(key, value);
        }

        if(root->key == key)//键相等，做值的替换
        {
            root->value = value;
        }

        else if(key < root->key)//左子树递归插入
            root->left = insert(key, value, root->left);
        else//右子树递归插入
            root->right = insert(key, value, root->right);
        return root;//未产生新节点的情况下，返回值与根节点相同
    }

    bool contain(Key key, Node *root)
    {
        if(root == NULL)//节点为空，返回假
            return false;
        if(root->key == key)//找到，返回真
            return true;
        else if(root->key > key)//递归查找左子树
            return contain(key, root->left);
        else//递归查找右子树
            return contain(key, root->right);
    }

    Value* search(Key key, Node *root)//面对有可能查找不到的情况，所以返回值设定为指针类型
    {
        if(root == NULL)
            return NULL;
        if(root->key == key)
            return &(root->value);
        else if(root->key > key)
            return search(key, root->left);
        else
            return search(key, root->right);
    }

    void preOrder(Node *root)
    {
        if(root != NULL)
        {
            cout<<root->key<<" ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    void inOrder(Node *root)
    {
        if(root != NULL)
        {
            inOrder(root->left);
            cout<<root->key<<" ";
            inOrder(root->right);
        }

    }

    void postOrder(Node *root)
    {
        if(root != NULL)
        {
            postOrder(root->left);
            postOrder(root->right);
            cout<<root->key<<" ";
        } 
    }

    Node* minimum(Node *root)//查找以 root 为根的树中 key 最小的节点
    {
        if(root->left == NULL)
            return root;
        return minimum(root->left);
    }

    Node* maximum(Node *root)//查找以 root 为根的树中 key 最大的节点
    {
        if(root->right == NULL)
            return root;
        return maximum(root->right);
    }

    Node* removeMin(Node *root)//移除最小的节点并返回新树的根(最小的节点没有左节点)
    {
        if(root->left == NULL)//找到最小节点
        {//最小节点的父亲节点的左孩子更新为最小节点的右孩子(右孩子存在，或者不存在的情况都可以解决)
            Node *node = root->right;//右孩子不存在时，node 为空，不用再做额外的处理
            delete root;//删除最小节点
            count--;//更新计数器
            return node;
        }

        root->left = removeMin(root->left);
        return root;//递归左查找时返回 root
    }

    Node* removeMax(Node *root)//移除最大的节点并返回新树的根(最大的节点没有右节点)
    {
        if(root->right == NULL)//找到
        {
            Node *node = root->left;
            delete root;
            count--;
            return node;
        }

        root->right = removeMax(root->right);
        return root;
    }

    Node* remove(Key key, Node *root)
    {
        if(root == NULL)
            return NULL;

        if(key < root->key)//寻找待删除节点
        {
            root->left = remove(key, root->left);
            return root;
        }

        else if(key > root->key)//寻找待删除节点
        {
            root->right = remove(key, root->left);
            return root;
        }

        else//找到待删除节点
        {
            if(root->right == NULL)//待删除节点右子树为空，只有左子树。
            {
                Node *node = root->left;
                delete root;
                count--;
                return node;
            }

            if(root->left == NULL)//只有右子树，左子树为空
            {
                Node *node = root->right;
                delete root;
                count--;
                return node;
            }

            //左右子树都为空进入第一个判断，左右子树都存在的情况下，要在子树中找一个节点代替待删除节点
            //寻找待删除的节点的后继(右子树的最小值) ps:前驱(左子树的最大值)其实也可以
            //Node *successor = minium(root->right);这样简单的指向会在后面的操作中失效
            Node *successor = new Node(minimum(root->right));//拷贝后继造出新的节点
            count++;//维护

            successor->right = removeMin(root->right);//把后继节点删除后的右子树挂到后继的右孩子上
            successor->left = root->left;//左子树挂到后继的左孩子上
            delete root;//删除待删除的节点
            count--;//维护

            return successor;//后继节点(即为删除待删除节点的新的根节点)
        }
    }


public:
    BST()//构造函数，初始化根节点指向为空，节点个数为零
    {
        root = NULL;
        count = 0;
    }

    ~BST()//析构函数，后续遍历删除所有节点(先删除所有左子树，再删除所有右子树，再删除自己)
    {
        destory(root);
    }

    int size()//取得树中节点个数
    {
        return count;
    }

    bool isEmpty()//判断树是否为空
    {
        return count == 0;
    }

    void insert(Key key, Value value)//插入键值对
    {
        root = insert(key, value, root);
    }

    bool contain(Key key)//查找某含有某键的节点是否存在
    {
        return contain(key, root);
    }

    Value* search(Key key)//查找含有某键的节点的值
    {
        return search(key, root);
    }

    void preOrder()//前序遍历
    {
        preOrder(root);
        cout<<endl;
    }

    void inOrder()//中序遍历
    {
        inOrder(root);
        cout<<endl;
    }

    void postOrder()//后序遍历
    {
        postOrder(root);
        cout<<endl;
    }

    void levelOrder()//层序遍历
    {
        queue<Node*> q;//队列
        q.push(root);//入队根节点

        while(!q.empty())//当队列不为空时循环该操作
        {
            Node *node = q.front();//从队列首取出一个元素
            cout<<node->key<<" ";
            q.pop();//删除队列首
            if(node->left)//取出元素的左右孩子节点(如果有的话)
                q.push(node->left);
            if(node->right)
                q.push(node->right);
        }
    }

    Key minimum()//寻找最小的键值
    {
        assert(count != 0);
        Node *minNode = minimum(root);
        return minNode->key;
    }

    Key maximum()//寻找最大的键值
    {
        assert(count != 0);
        Node *maxNode = maximum(root);
        return maxNode->key;
    }

    void removeMin()//删除最小值节点
    {
        if(root)
            root = removeMin(root);
    }

    void removeMax()//删除最大值节点
    {
        if(root)
            root = removeMax(root);
    }

    void remove(Key key)//删除键值为 key 的节点
    {
        root = remove(key, root);
    }

};

void shuffle( int arr[], int n ){

    srand( time(NULL) );
    for( int i = n-1 ; i >= 0 ; i -- ){
        int x = rand()%(i+1);
        swap( arr[i] , arr[x] );
    }
}
#endif //BINARYSEARCHTREE_BST_H
