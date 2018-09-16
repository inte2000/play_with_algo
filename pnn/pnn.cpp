// pnn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <utility>

//std::string::value_type
void Swap(std::string& chList, int pos1, int pos2)
{
    if (pos1 != pos2)
    {
        auto tmp = chList[pos1]; 
        chList[pos1] = chList[pos2];
        chList[pos2] = tmp;
    }
}

//将字符串[begin, end]区间的子串全排列
void Permutation(std::string& chList, int begin, int end)
{
    if (begin == end)
    {
        std::cout << chList << std::endl;
    }

    for (int i = begin; i <= end; i++)
    {
        Swap(chList, begin, i); //把第i个字符换到begin位置，将begin+1位置看作新的子串
        Permutation(chList, begin + 1, end); //求解子问题
        Swap(chList, begin, i); //换回来
    }
}

int main()
{
    std::string cl = "abc";
    //std::string cl = "abcd";

    Permutation(cl, 0, cl.length() - 1);

    return 0;
}

