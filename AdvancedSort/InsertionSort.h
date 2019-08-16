//
// Created by ArthurMeng on 23/12/2017.
//

#ifndef ADVANCEDSORT_INSERTIONSORT_H
#define ADVANCEDSORT_INSERTIONSORT_H

// 用于在归并排序中调用
// 当数组大小比较小时，趋向于有序，这时使用插入排序会比归并更快
template <typename T>
void insertionSort(T arr[], int l, int r)
{
    for(int i = l+1 ; i <= r ; i++)
    {
        T temp = arr[i];
        int j;
        for(j = i ; j > 0 && arr[j-1] > temp ; j--)
            arr[j] = arr[j-1];
        arr[j] = temp;
    }
    return;
}
#endif //ADVANCEDSORT_INSERTIONSORT_H
