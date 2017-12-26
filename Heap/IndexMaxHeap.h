//
// Created by ArthurMeng on 2017/12/26.
//

#ifndef MAXHEAP_INDEXMAXHEAP_H
#define MAXHEAP_INDEXMAXHEAP_H

#include <iostream>
#include <assert.h>
#include <cmath>

using namespace std;

//为了让堆在维持结构的时候保持数组顺序不变，这里建立了索引数组,data存储真正的数据，shift操作是对索引数组进行的
template <typename Item>
class IndexHeap
{
private:
    Item *data;
    int *indexs;//索引数组
    int count;
    int capacity;

    void shiftUp(int k)
    {
        while(k > 1 && data[indexs[k/2]] < data[indexs[k]])//对比真实数据的值
        {
            swap(indexs[k/2],indexs[k]);//交换索引的位置
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
    IndexHeap(int capacity)
    {
        data = new Item[capacity+1];
        indexs = new int[capacity+1];//开索引数组空间
        count = 0;
        this->capacity = capacity;
    }

    IndexHeap(Item item[], int n)
    {
        data = new Item[n+1];
        capacity = n;

        for(int i = 1 ; i <= n ; i++)
            data[i] = item[i-1];
        count = n;

        for(int i = n/2 ; i >= 1 ; i--)
            shiftDown(i);
    }

    ~IndexHeap()
    {
        delete[] data;
        delete[] indexs;
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
        count++;
        shiftUp(count);
    }

    Item extraxMax()
    {
        assert(count > 0);
        Item ret = data[indexs[1]];
        swap(indexs[1], indexs[count]);
        count--;
        shiftDown(1);
        return ret;
    }

    int extraxMaxIndex()
    {
        assert(count > 0);
        int ret = indexs[1];
        swap(indexs[1],indexs[count]);
        count--;
        shiftDown(1);
        return ret;
    }

    Item getMax()
    {
        assert(count > 0);
        return data[indexs[1]];
    }

    Item getItem(int i)
    {
        return data[i+1];
    }

    void change(int i, Item newItem)//索引堆特有操作，更改某下标位置的值 (更改值之后，要对对应的索引进行尝试 shiftUp 跟shiftDown操作)
    {
        i++;
        data[i] = newItem;

        for(int j = 1 ; j <= count ; j++)//为了找到某下标对应的索引必须便利索引数组，更改成本 o N有优化空间
        {
            if(indexs[j] == i)
            {
                shiftUp(j);
                shiftDown(j);
                return;
            }
        }
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

#endif //MAXHEAP_INDEXMAXHEAP_H
