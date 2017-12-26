//
// Created by ArthurMeng on 2017/12/25.
//

#ifndef MAXHEAP_HEAPSORT_H
#define MAXHEAP_HEAPSORT_H

#include <iostream>
#include "Heap.h"
using namespace std;

template <typename T>
void heapSort1(T arr[], int n)//插入建堆，取出排序
{
    MaxHeap<T> maxHeap = MaxHeap<T>(n);
    for(int i = 0 ; i < n ;i++)
        maxHeap.insert(arr[i]);

    for(int i = 0 ; i < n ; i++)
        arr[n-1-i] = maxHeap.extraxMax();
}

template <typename T>
void heapSort2(T arr[], int n)//heapify建堆
{
    MaxHeap<T> maxHeap = MaxHeap<T>(arr, n);

    for(int i = 0 ; i < n ; i++)
        arr[n-1-i] = maxHeap.extraxMax();
}

template <typename T>
void __shiftDown(T arr[], int n, int i)
{
    while((i*2 + 1) <= n-1)
    {
        int k = i*2+1;
        if((i*2 + 2) <= n-1)
            k = arr[k+1] > arr[k] ? k+1 : k;
        if(arr[i] >= arr[k])
            break;
        swap(arr[i], arr[k]);
        i = k;
    }
}

template <typename T>
void __shiftDown2(T arr[], int n, int i)
{
    T v = arr[i];
    while((i*2 + 1) <= n-1)
    {
        int k = i*2+1;
        if((i*2 + 2) <= n-1)
            k = arr[k+1] > arr[k] ? k+1 : k;
        if(arr[i] >= arr[k])
            break;
        arr[i] = arr[k];
        i = k;
    }
    arr[i] = v;
}

template <typename T>
void inPlaceHeapSort(T arr[], int n)//原地建堆排序(注意数组的索引从零开始了)，
{
    for(int i = (n-1)/2 ; i >=0 ; i--)
        __shiftDown2(arr, n, i);

    for(int i = n-1 ; i >= 1 ; i--)
    {
        swap(arr[0], arr[i]);
        __shiftDown(arr, i, 0);//注意 i 是数组的大小，不是数组的下标
    }

}

#endif //MAXHEAP_HEAPSORT_H
