//
// Created by ArthurMeng on 2017/12/25.
//

#ifndef MAXHEAP_HEAP_H
#define MAXHEAP_HEAP_H

#include <iostream>
#include <assert.h>
#include <cmath>

using namespace std;

//最大堆，由数组实现，下标索引从 1 开始，所以 0 号索引不用，开辟空间大小为 n+1
template <typename Item>
class MaxHeap
{
private:
    Item *data;//用于存放数据的指针，用构造函数根据参数开辟空间
    int count;//记录堆中元素个数
    int capacity;//堆的容量，由构造函数的参数决定

    void shiftUp(int k)
    {
        while(k > 1 && data[k/2] < data[k])//父节点比自己小，执行交换。k >1 也就是 k/2 = 1,当所有节点都已经比价过后停止
        {
            swap(data[k/2],data[k]);
            k /= 2;//不断向上比较
        }
    }

    void shiftDown(int k)//当不存在孩子节点时退出交换
    {
        while(k*2 <= count)//要是左孩子没有，右孩子根本就没有
        {
            int temp = k*2;//左孩子存在，待定交换的下标暂定为左孩子
            if(temp+1 <= count)//右孩子也存在
                temp = data[temp] > data[temp+1] ? temp : temp+1;//哪个孩子的值比较大，待交换的下标就定为该孩子
            if(data[k] > data[temp]) break;//真正确定孩子比父亲大才进行交换
            swap(data[k],data[temp]);
            k = temp;
        }
    }

public:
    MaxHeap(int capacity)//构造函数,参数为堆的容量
    {
        data = new Item[capacity+1];//开空间
        count = 0;
        this->capacity = capacity;
    }


    //把一个无序的数组变成堆，只要对所有非叶节点执行(shiftDown)，这就把所有的子树都变为了堆
    MaxHeap(Item item[], int n)//构造函数，参数为一定大小的数组
    {
        data = new Item[n+1];
        capacity = n;

        for(int i = 1 ; i <= n ; i++)//申请空间并错一位拷贝数组的值
            data[i] = item[i-1];
        count = n;

        for(int i = n/2 ; i >= 1 ; i--)//最后的叶节点除以 2 得到最后一个非叶节点
            shiftDown(i);
    }

    ~MaxHeap()
    {
        delete[] data;//析构函数，删除开辟的空间
    }

    int size()//取得堆中元素的个数
    {
        return count;
    }

    bool isEmpty()//堆是否为空
    {
        return count == 0;
    }

    void insert(Item item)//堆的插入操作
    {
        assert(count+1 <= capacity);//执行插入操作后不超出容量
        data[count+1] = item;//执行插入操作
        count++;//更新容量
        shiftUp(count);//插入操作可能导致堆的结构被破坏，进行向上交换维持结构
    }

    Item extraxMax()
    {
        assert(count > 0);//堆中元素不为空
        Item ret = data[1];//堆中最大的元素是下标为 1 的元素
        swap(data[1],data[count]);//把堆顶元素与与最后一个叶子节点进行交换
        count--;//更新容量值
        shiftDown(1);//执行交换后，堆结构发生改变，向下进行交换维持结构
        return ret;
    }


public:
    void testPrint(){

        if( size() >= 100 ){
            cout<<"Fancy print can only work for less than 100 int";
            return;
        }

        if( typeid(Item) != typeid(int) ){
            cout <<"Fancy print can only work for int item";
            return;
        }

        cout<<"The Heap size is: "<<size()<<endl;
        cout<<"data in heap: ";
        for( int i = 1 ; i <= size() ; i ++ )
            cout<<data[i]<<" ";
        cout<<endl;
        cout<<endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while( n > 0 ) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }

        int max_level_number = int(pow(2, max_level-1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for( int level = 0 ; level < max_level ; level ++ ){
            string line1 = string(max_level_number*3-1, ' ');

            int cur_level_number = min(count-int(pow(2,level))+1,int(pow(2,level)));
            bool isLeft = true;
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index ++ , index_cur_level ++ ){
                putNumberInLine( data[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
                isLeft = !isLeft;
            }
            cout<<line1<<endl;

            if( level == max_level - 1 )
                break;

            string line2 = string(max_level_number*3-1, ' ');
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
                putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
            cout<<line2<<endl;

            cur_tree_max_level_number /= 2;
        }
    }

private:
    void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if( num >= 10 ) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else{
            if( isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
        assert( offset_left + 1 < line.size() );
        int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert( offset_right < line.size() );

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }

};


#endif //MAXHEAP_HEAP_H
