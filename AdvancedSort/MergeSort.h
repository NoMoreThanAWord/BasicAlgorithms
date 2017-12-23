//
// Created by ArthurMeng on 23/12/2017.
//

#ifndef ADVANCEDSORT_MERGESORT_H
#define ADVANCEDSORT_MERGESORT_H

#include <iostream>
#include "InsertionSort.h"
using namespace std;



//A.递归的归并排序
template <typename T>
void __merge(T arr[], int l, int mid, int r)
{
    T temp[r-l+1];

    for(int i = 0 ; i < r-l+1 ; i++)
        temp[i] = arr[l+i];

    int j = l;
    int k = mid+1;
    for(int p = l ; p <= r ; p++)
    {
        if(j > mid)
        {
            arr[p] = temp[k-l];
            k++;
        }

        else if(k > r)
        {
            arr[p] = temp[j-l];
            j++;
        }

        else if(temp[j-l] < temp[k-l])
        {
            arr[p] = temp[j-l];
            j++;
        }
        else
        {
            arr[p] = temp[k-l];
            k++;
        }

    }
}

template <typename T>
void __mergeSort(T arr[], int l, int r)
{
    if(l >= r)
        return;
    int mid = (l+r) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    if(arr[mid] > arr[mid+1])//当数组近乎有序时，可以加上这句，用来减少归并次数，注意判断也会增加开销
        __merge(arr, l, mid, r);
}

template <typename T>
void mergeSort(T arr[], int n)
{
    __mergeSort(arr,0,n-1);
}
///////////
///////////


//B.改进的归并排序(在数组小于一定程度的时候采用插入排序提升效率。当要归并的两部分已经有序时，减少无用的归并)
template <typename T>
void __improvedMergeSort(T arr[], int l, int r)
{
    if(l - r <= 15)
    {
        insertionSort(arr, l, r);
        return;
    }

    int mid = (l+r) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    if(arr[mid] > arr[mid+1])//当数组近乎有序时，可以加上这句，用来减少归并次数，注意判断也会增加开销
        __merge(arr, l, mid, r);

}

template <typename T>
void improvedMergeSort(T arr[], int n)
{
    __improvedMergeSort(arr, 0, n-1);
}

///////
///////


//C.botton up mergeSort(没有递归过程,也没有应用数组下标取数的特性，适合与对链表进行排序)
template <typename T>
void mergeSortBU(T arr[], int n)//botton up mergeSort无递归，没有应用数组按下标取值的特性，可以应用于链表，性能略低于上一版mergeSort
{
    for(int sz = 1 ; sz <= n ; sz += sz)//每轮归并的数组大小
    {
        for(int i = 0 ; i + sz < n ; i += 2*sz)//每轮归并的位置,i+sz < n 保证第二个数组的存在
            __merge(arr, i, i+sz-1, min(i+2*sz-1, n-1));//min()保证的第二个数组不满sz 的情况
    }
}


///////
//////
#endif //ADVANCEDSORT_MERGESORT_H
