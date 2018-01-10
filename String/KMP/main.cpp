#include <iostream>
#include <vector>
#include <string>
using namespace std;

//生成最大前缀子串的数组 o(n)
vector<int> computePrefix(string pat){
    int m = pat.size();
    vector<int> longestPrefix(m);
    //i,k 下标所对应字符的值相等时，i 的最长前缀子串长度为 k 下标加一
    //i,k 下标所对应字符的值不相等时，且 k 不为零时，k 的值更新为 k-1 位置所对应的最长子串长度所在的下标
    for(int i = 1, k = 0; i < m; i++){
        while(k > 0 && pat[k] != pat[i]){
            k = longestPrefix[k - 1];
        }

        //从循环退出的两种情况 a.两数相等
        if(pat[i] == pat[k]){
            longestPrefix[i] = ++k;
        }
        //b. k 的值退为 0 且两数不等，
        else{
            longestPrefix[i] = j;//这里写零其实也一样
        }
    }
    return longestPrefix;
}

//匹配两串 o(m),总体 o(m+n)
int KMP(string str,string pat){
    int n = str.size();
    int m = pat.size();
    vector<int> longestPrefix = computePrefix(pat);
    for(int i = 0, k = 0; i < n; i++){
        while(k > 0 && pat[k] != str[i]){
            k = longestPrefix[k - 1];
        }
        if(str[i] == pat[k]){
            k++;
        }
        if(k == m){
            return i-m+1;
            //cout << i - m + 1 << "\n";
            //k = longestPrefix[k - 1];
        }
    }
    return -1;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    string a = "mississippi";
    string b = "issip";
    int index = KMP(a,b);
    printf("index: %d\n",index);
    return 0;
}
