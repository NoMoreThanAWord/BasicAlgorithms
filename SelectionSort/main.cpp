#include <iostream>
#include "SortTestHelper.h"

using namespace std;

struct student
{
    string name;
    int score;

    bool operator<(const student &otherStu)
    {
        return score != otherStu.score ? score < otherStu.score : name < otherStu.name;
    }

    friend ostream&operator<<(ostream &os, const student &otherStu)
    {
        os<<"student:"<<otherStu.name<<" "<<otherStu.score;
        return os;
    }
};

template <typename T>
void showArray(T arr[], int n)
{
    for(int i = 0 ; i < n ; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

template <typename T>
void selectionSort(T arr[] , int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        int tempSmall = i;
        for(int j = i+1 ; j < n ; j++)
        {
            if(arr[j] < arr[tempSmall])
            {
                tempSmall = j;
            }
        }
        swap(arr[i],arr[tempSmall]);
    }
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    int *a = SortTestHelper::generateRandomArray(100,0,100);
    student stu[] = {{"zhangsan",60},{"lisi",60},{"wangwu",45}};
    selectionSort(a,100);
    showArray(a,100);
    delete[] a;

    return 0;
}