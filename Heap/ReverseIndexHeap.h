//
// Created by ArthurMeng on 2017/12/26.
//

#ifndef MAXHEAP_REVERSEINDEXHEAP_H
#define MAXHEAP_REVERSEINDEXHEAP_H
#include <iostream>
#include <assert.h>
#include <cmath>

using namespace std;

//由于索引堆在更改操作时，查找某下标对应的索引位置要用 o(N)的复杂度，这里新建一个反向查找数组，指向某下标对应的索引值
template <typename Item>
class ReverseIndexHeap
{
private:
    Item *data;
    int *indexs;
    int *reverse;//反向查找数组
    int count;
    int capacity;

    void shiftUp(int k)
    {
        while(k > 1 && data[indexs[k/2]] < data[indexs[k]])
        {
            swap(indexs[k/2],indexs[k]);
            k /= 2;
        }
    }

    void shiftDown(int k)
    {
        while(k*2 <= count)
        {
            int temp = k*2;
            if(temp+1 <= count)
                temp = data[indexs[temp]] > data[indexs[temp+1]] ? temp : temp+1;
            if(data[indexs[k]] > data[indexs[temp]]) break;
            swap(indexs[k],indexs[temp]);
            k = temp;
        }
    }

public:
    ReverseIndexHeap(int capacity)//初始化时堆中没有元素，所有下标都无指向，故初始化为 0 ，即指向为空
    {
        data = new Item[capacity+1];
        indexs = new int[capacity+1];
        reverse = new int[capacity+1];
        count = 0;
        for(int i = 0 ; i < capacity+1 ; i++)
            reverse[i] = 0;

        this->capacity = capacity;
    }

    ReverseIndexHeap(Item item[], int n)
    {
        data = new Item[n+1];
        capacity = n;

        for(int i = 1 ; i <= n ; i++)
            data[i] = item[i-1];
        count = n;

        for(int i = n/2 ; i >= 1 ; i--)
            shiftDown(i);
    }

    ~ReverseIndexHeap()
    {
        delete[] data;
        delete[] indexs;
        delete[] reverse;
    }

    int size()
    {
        return count;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    void insert(int i, Item item)
    {
        assert(count+1 <= capacity);
        assert(i+1 >=1 && i+1 <= capacity);
        i++;
        data[i] = item;
        indexs[count+1] = i;
        reverse[i] = count+1;//维护reverse数组
        count++;
        shiftUp(count);
    }

    Item extraxMax()
    {
        assert(count > 0);
        Item ret = data[indexs[1]];
        swap(indexs[1], indexs[count]);
        reverse[indexs[count]] = 0;//无用下标指向为空
        reverse[indexs[1]] = 1;//维护
        count--;
        shiftDown(1);
        return ret;
    }

    int extraxMaxIndex()
    {
        assert(count > 0);
        int ret = indexs[1];
        swap(indexs[1],indexs[count]);
        reverse[indexs[count]] = 0;
        reverse[indexs[1]] = 1;
        count--;
        shiftDown(1);
        return ret;
    }

    Item getMax()
    {
        assert(count > 0);
        return data[indexs[1]];
    }

    int getMaxIndex()
    {
        assert(count > 0);
        return indexs[1] - 1;

    }

    bool contain(int i)//测试堆中是否有某下标的元素
    {
        assert(i+1 >=1 && i+1 <= capacity);//是否在容量范围内
        return reverse[i+1] != 0;//反向索引指向不为空，说明存在
    }

    Item getItem(int i)
    {
        assert(contain(i));
        return data[i+1];
    }

    void change(int i, Item newItem)
    {
        assert(contain(i));//更改下标的值前检查是否存在
        i++;
        data[i] = newItem;

//        for(int j = 1 ; j <= count ; j++)
//        {
//            if(indexs[j] == i)
//            {
//                shiftUp(j);
//                shiftDown(j);
//                return;
//            }
//        }
        shiftUp(reverse[i]);//反向查找索引实现了 o1 的复杂度找到下标对应的索引
        shiftDown(reverse[i]);

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


template <typename T>
void heapSortUsingIndexMaxHeap(T arr[], int n)
{
    ReverseIndexHeap<T> reverseIndexHeap = ReverseIndexHeap<T>(n);
    for(int i = 0 ; i < n ; i++)
        reverseIndexHeap.insert(i,arr[i]);

    for(int i = n ; i >= 1 ; i--)
        arr[i-1] = reverseIndexHeap.extraxMax();
}

#endif //MAXHEAP_REVERSEINDEXHEAP_H
