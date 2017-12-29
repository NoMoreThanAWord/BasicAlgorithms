//
// Created by ArthurMeng on 2017/12/26.
//

#ifndef BINARYSEARCHTREE_BINARYSEARCH_H
#define BINARYSEARCHTREE_BINARYSEARCH_H
template <typename T>
T binarySearch(T arr[], int n, T target)
{
    int l = 0;//左边界
    int r = n-1;//右边界
    while(l <= r)//一直查找到左右边界相等--即区间中只有一个元素
    {
        int mid = (l+r)/2;//取区间中点
        if(arr[mid] == target)//中点值即为目标
            return mid;
        if(arr[mid] > target)//目标值比中点小，在中点值左边区间查找
            r = mid-1;
        else//目标值比中点大，在中点值右边区间查找
            l = mid+1;
    }//退出循环时还未找到，说明不存在，返回-1
    return -1;
}
#endif //BINARYSEARCHTREE_BINARYSEARCH_H
