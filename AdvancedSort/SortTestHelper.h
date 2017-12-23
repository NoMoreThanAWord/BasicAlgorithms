//
// Created by ArthurMeng on 21/12/2017.
//

#ifndef SELECTIONSORT_SORTTESTHELPER_H
#define SELECTIONSORT_SORTTESTHELPER_H
#include <iostream>
#include <ctime>
#include <cassert>
using namespace std;
namespace SortTestHelper
{

    template <typename T>
    void showArray(T arr[], int n)//数组展示
    {
        for(int i = 0 ; i < n ; i++)
            cout<<arr[i]<<" ";
        cout<<endl;
    }

    int* generateRandomArray(int n, int rangeL, int rangeR)//生成随机数组，参数为个数，左右边界
    {
        assert(rangeL <= rangeR);
        int *arr = new int[n];
        srand(time(NULL));

        for(int i = 0 ; i < n ; i++)
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        return arr;
    }

    int* generateNearlyOrderArray(int n, int swapTime)//生成近乎有序数组,参数为个数，随机交换的次数
    {
        int *arr = new int[n];
        for(int i = 0 ; i < n ; i++)
            arr[i] = i;
        srand(time(NULL));

        for(int i = 0 ; i < swapTime ; i++)
        {
            int posx = rand()%n;
            int posy = rand()%n;
            swap(arr[posx],arr[posy]);
        }
        return arr;
    }

    template <typename T>
    bool isSorted(T arr[], int n)//检查数组是否有序
    {
        for(int i = 0 ; i < n ; i++)
        {
            if(arr[i] > arr[i+1])
                return false;
        }
        return true;
    }

    template <typename T>//排序算法测试
    void testSort(string sortName, void(*sort)(T[], int), T arr[], int n)//算法名称，算法指针，待排序数组，数组元素个数
    {
        clock_t startTime = clock();
        sort(arr,n);
        clock_t endTime = clock();
        //showArray(arr,n);
        cout<<sortName<<":"<<double(endTime - startTime) / CLOCKS_PER_SEC;
        cout<<endl;
        return;
    }

    int* copyIntArray(int arr[], int n)//数组拷贝
    {
        int *temp = new int[n];
        copy(arr,arr+n,temp);
        return temp;
    }
}

#endif //SELECTIONSORT_SORTTESTHELPER_H

