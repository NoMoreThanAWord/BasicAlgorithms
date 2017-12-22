#include <iostream>
#include "SortTestHelper.h"
#include "student.h"
using namespace std;

template <typename T>
void bubbleSort(T arr[], int n)//冒泡排序每一趟从后往前通过交换挤出一个最小的，这样挤n-1次就变的有序了
{
    for(int i = 1 ; i < n ; i++)
    {
        for(int j = n-1 ; j >= i ; j--)
        {
            if(arr[j] < arr[j-1])
                swap(arr[j],arr[j-1]);
        }
    }
}

template <typename T>
void improvedBubbleSortOne(T arr[], int n)//第一种优化，对于近乎有序或者直接就是有序的数组，会执行多余的循环。进行判断，如果有序，直接退出
{
    for(int i = 1 ; i < n ; i++)
    {
        bool flag = false;
        for(int j = n-1 ; j >= i ; j--)
        {
            if(arr[j] < arr[j-1])
            {
                flag = true;
                swap(arr[j],arr[j-1]);
            }
        }
        if(flag == false)
            break;
    }
}

template <typename T>
void improvedBubbleSortTwo(T arr[], int n)//对于近乎有序的数组，记录最后一次交换的位置，交换位置之前的都为有序，借此缩小第二重循环的搜索范围
{
    int flag = 1;
    int lastSwap = 1;
    for(int i = 1 ; i < n ; i++)
    {
        flag = lastSwap;
        lastSwap = 1;
        for(int j = n-1 ; j >= flag ; j--)
        {
            if(arr[j] < arr[j-1])
            {
                swap(arr[j],arr[j-1]);
                lastSwap = j+1;
            }
        }
        if(flag == lastSwap)
            break;
    }
}

template <typename T>
void selectionSort(T arr[] , int n)//选择排序，每次从无序的部分中找出最小的放在队尾
{
    for(int i = 0 ; i < n ; i++)
    {
        int tempSmall = i;
        for(int j = i+1 ; j < n ; j++)//要找出最小，必须遍历所有无序的部分
        {
            if(arr[j] < arr[tempSmall])
            {
                tempSmall = j;
            }
        }
        swap(arr[i],arr[tempSmall]);
    }
}

template <typename T>
void improvedInsertionSort(T arr[], int n)//冒泡的交换过程改为了赋值，最后一次决定插入的最终位置
{
    for(int i = 1 ; i < n ; i++)
    {
        T temp = arr[i];
        int j;
        for(j = i ; j > 0 && arr[j-1] > temp ; j--)
            arr[j] = arr[j-1];
        arr[j] = temp;
    }
}

template <typename T>//插入排序跟选择排序都是 n*n 的排序，但是插入排序的第二重循环可以提前结束
void insertionSort(T arr[], int n)//初级插入排序，每次向一个有序的数组中插入一个新的数
{
    for(int i = 1 ; i < n ; i++)
    {
        for(int j = i ; j > 0 && arr[j] < arr[j-1]; j--)
            swap(arr[j],arr[j-1]);//用类似冒泡的方法把待插入的数放置到合适的位置，不断的交换操作影响了性能
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int n = 16;
    //int a[] = {4,3,2,1};
    int *b = SortTestHelper::generateRandomArray(n,0,n);
    //int *b = SortTestHelper::generateNearlyOrderArray(n,90);
    int *b1 = SortTestHelper::copyIntArray(b,n);
    int *b2 = SortTestHelper::copyIntArray(b,n);
    int *b3 = SortTestHelper::copyIntArray(b,n);
    int *b4 = SortTestHelper::copyIntArray(b,n);
    int *b5 = SortTestHelper::copyIntArray(b,n);    
    int *b6 = SortTestHelper::copyIntArray(b,n);



    // SortTestHelper::testSort("insertionSort",insertionSort,b1,n);
    // SortTestHelper::testSort("selectionSort",selectionSort,b2,n);
    SortTestHelper::testSort("improvedInsertionSort",improvedInsertionSort,b3,n);
    SortTestHelper::testSort("bubbleSort",bubbleSort,b4,n);
    SortTestHelper::testSort("improvedBubbleSortOne",improvedBubbleSortOne,b5,n);
    SortTestHelper::testSort("improvedBubbleSortTwo",improvedBubbleSortTwo,b6,n);

    return 0;
}