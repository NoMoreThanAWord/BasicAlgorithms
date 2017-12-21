//
// Created by ArthurMeng on 21/12/2017.
//

#ifndef SELECTIONSORT_SORTTESTHELPER_H
#define SELECTIONSORT_SORTTESTHELPER_H
#include <iostream>
#include <ctime>
#include <cassert>

namespace SortTestHelper
{
    int* generateRandomArray(int n, int rangeL, int rangeR)
    {
        assert(rangeL <= rangeR);
        int *arr = new int[n];
        srand(time(NULL));

        for(int i = 0 ; i < n ; i++)
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        return arr;
    }
}

#endif //SELECTIONSORT_SORTTESTHELPER_H
