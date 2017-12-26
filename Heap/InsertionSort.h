//
// Created by ArthurMeng on 23/12/2017.
//

#ifndef ADVANCEDSORT_INSERTIONSORT_H
#define ADVANCEDSORT_INSERTIONSORT_H
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
