//
// Created by ArthurMeng on 23/12/2017.
//

#ifndef ADVANCEDSORT_QUICKSORT_H
#define ADVANCEDSORT_QUICKSORT_H
#include <iostream>
using namespace std;


//A.普通的单向快速排序
template <typename T>
int __partition(T arr[], int l, int r)
{
    int j = l;

    for(int p = l+1 ; p <= r ; p++)
    {
        if(arr[p] < arr[l])
        {
            swap(arr[p],arr[j+1]);
            j++;
        }
    }
    swap(arr[l],arr[j]);
    return j;
}

template <typename T>
void __quickSort(T arr[], int l, int r)
{
    if(l >= r)
        return;
    int p = __partition(arr,l,r);
    __quickSort(arr,l,p-1);
    __quickSort(arr,p+1,r);
}

template <typename T>
void quickSort(T arr[], int n)
{
    __quickSort(arr, 0, n-1);
}

//////
//////
//////



/*B.随机快速排序(普通单向快排在数组有序情况下会退化为 n*n 的算法，每次partition的标定点都取数组头部，导致切分的两部分
极度的不平衡，每次shuffle一个数作为标定点，会使得partition重新变得平衡)*/
 template <typename T>
int __shufflePartition(T arr[], int l, int r)
{
    swap(arr[l], arr[rand() % (r-l+1) + l]);
    int j = l;

    for(int p = l+1 ; p <= r ; p++)
    {
        if(arr[p] < arr[l])
        {
            swap(arr[p],arr[j+1]);
            j++;
        }
    }
    swap(arr[l],arr[j]);
    return j;
}

template <typename T>
void __shuffleQuickSort(T arr[], int l, int r)
{
    if(l >= r)
        return;
    int p = __shufflePartition(arr,l,r);
    __shuffleQuickSort(arr,l,p-1);
    __shuffleQuickSort(arr,p+1,r);
}

template <typename T>
void shuffleQuickSort(T arr[], int n)
{
    srand(time(NULL));
    __shuffleQuickSort(arr, 0, n-1);
}

////////
////////
////////


/*C.双路快排(当数组的变化范围较小的时候，shuffle也不能保证 partition切分的平衡，单向扫描的效率极为地下，有时退化
 * 为 n*n 的算法，这时采用双向扫描，同时向右跟向左扫描小于标定点与大于标定点的部分，遇到顺序不对的进行交互)*/
template <typename T>
int __partition2(T arr[], int l, int r)
{
    swap(arr[l], arr[rand() % (r-l+1) + l]);
    int i = l+1;
    int j = r;

    while(true)
    {
        while(arr[i] < arr[l] && i <= r) i++;
        while(arr[j] > arr[l] && j >= l+1) j--;

        if(i >= j) break;

        swap(arr[i], arr[j]);
        i++;
        j--;
    }
    swap(arr[l], arr[j]);
    return j;
}

template <typename T>
void __quickSort2(T arr[], int l, int r)
{
    if(l >= r)
        return;
    int p = __partition2(arr, l, r);
    __quickSort2(arr, l, p-1);
    __quickSort2(arr, p+1, r);
}

template <typename T>
void quickSort2(T arr[], int n)
{
    srand(time(NULL));
    __quickSort2(arr, 0, n-1);
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*D.三路快排(双路快排的分组是 <= arr[l] 与 >= arr[l] ，两部分分组中都包含了等于arr[l]的部分。所有当数组中出现非常多重复元素时，partiton又会变得十分低效，这时在双路的基础上再
 * 增加一个记录等于标定点的位置变量，极大的提升了效率)
 * 注意：三路快排在处理随机数组时效率略低，但由于其在处理重复元素时的稳定性，故被很多系统库所采用*/
template <typename T>
void __quickSort3(T arr[], int l, int r)
{
    if( l >= r)
        return;
    swap(arr[l], arr[rand() % (r-l+1) + l]);

    int i = l+1;
    int lt = l;
    int gt = r+1;
    int p = l;

    while(i < gt)
    {
        if(arr[i] < arr[l])
        {
            swap(arr[lt+1],arr[i]);
            lt++;
            i++;
        }

        else if(arr[i] > arr[l])
        {
            swap(arr[gt-1],arr[i]);
            gt--;
        }
        else
        {
            i++;
        }
    }

    swap(arr[l],arr[lt]);

    __quickSort3(arr, l, lt-1);
    __quickSort3(arr, gt, r);
}

template <typename T>
void quickSort3(T arr[], int n)
{
    srand(time(NULL));
    __quickSort3(arr, 0, n-1);
}


#endif //ADVANCEDSORT_QUICKSORT_H
