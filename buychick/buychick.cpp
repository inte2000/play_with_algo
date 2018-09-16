// buychick.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

void Buy()
{
    int count = 0;

    for (int roosters = 0; roosters <= 20; roosters++)   //枚举大公鸡数量
    {
        for (int hens = 0; hens <= 33; hens++) //枚举母鸡数量
        {
            int chicks = 100 - roosters - hens;  //剩下的就是小鸡数量
            if (((chicks % 3) == 0) //小鸡个数应该是3的整数倍，算是个小小的剪枝
                && ((5 * roosters + 3 * hens + chicks / 3) == 100)) //是否凑够100个钱
            {
                count++;
                std::cout << "买法 " << count << "：公鸡 " << roosters
                                              << ", 母鸡 " << hens
                                              << ", 小鸡 " << chicks << std::endl;
            }
        }
    }

    std::cout << "共有 " << count << " 种买法" << std::endl;
}

int main()
{
    Buy();
    return 0;
}

