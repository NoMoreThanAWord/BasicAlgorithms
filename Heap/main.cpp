#include <iostream>
#include "Heap.h"
#include "SortTestHelper.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "ReverseIndexHeap.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    int n = 40;
    //int a[] = {4,3,2,1};
    int *b = SortTestHelper::generateRandomArray(n,0,n);
    //int *b = SortTestHelper::generateRandomArray(n,0,10);
    //int *b = SortTestHelper::generateNearlyOrderArray(n,0);
    int *b1 = SortTestHelper::copyIntArray(b,n);
    int *b2 = SortTestHelper::copyIntArray(b,n);
    int *b3 = SortTestHelper::copyIntArray(b,n);
    int *b4 = SortTestHelper::copyIntArray(b,n);
    int *b5 = SortTestHelper::copyIntArray(b,n);
    int *b6 = SortTestHelper::copyIntArray(b,n);
    int *b7 = SortTestHelper::copyIntArray(b,n);
    int *b8 = SortTestHelper::copyIntArray(b,n);
    int *b9 = SortTestHelper::copyIntArray(b,n);
    int *b10 = SortTestHelper::copyIntArray(b,n);
    int *b11 = SortTestHelper::copyIntArray(b,n);


    SortTestHelper::testSort("mergeSort",mergeSort,b1,n);
    SortTestHelper::testSort("improvedMergeSort",improvedMergeSort,b2,n);
    SortTestHelper::testSort("mergeSortBU",mergeSortBU,b3,n);
    SortTestHelper::testSort("quickSort",quickSort,b4,n);
    SortTestHelper::testSort("shuffleQuickSort",shuffleQuickSort,b5,n);
    SortTestHelper::testSort("quickSort2", quickSort2, b6, n);
    SortTestHelper::testSort("quickSort3", quickSort3, b7, n);
    SortTestHelper::testSort("heapSort1", heapSort1, b8, n);
    SortTestHelper::testSort("heapSort2", heapSort2, b9, n);
    SortTestHelper::testSort("inPlaceHeapSort", inPlaceHeapSort, b10, n);
    SortTestHelper::testSort("heapSortUsingIndexMaxHeap", heapSortUsingIndexMaxHeap, b11, n);


    cout<<"\nhello world again!\n";
    return 0;
}