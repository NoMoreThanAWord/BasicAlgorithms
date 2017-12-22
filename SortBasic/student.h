//
// Created by ArthurMeng on 21/12/2017.
//

#ifndef SELECTIONSORT_STUDENT_H
#define SELECTIONSORT_STUDENT_H

#include <iostream>
using namespace std;
struct student
{
    string name;
    int score;

    bool operator<(const student &otherStu)//重载< 使得结构体 student 之间也可以比较 ,类似java中的comparable接口
    {
        return score != otherStu.score ? score < otherStu.score : name < otherStu.name;
    }

    friend ostream&operator<<(ostream &os, const student &otherStu)//友源函数，方便使用 << 进行输出 类似java 中的 toString()
    {
        os<<"student:"<<otherStu.name<<" "<<otherStu.score;
        return os;
    }
};

#endif //SELECTIONSORT_STUDENT_H
