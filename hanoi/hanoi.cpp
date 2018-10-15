// hanoi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

//把一个环从from柱移到to柱，就是打印移动步骤
void move(int from, int to)
{
    std::cout << "move: " << from << " ----> " << to << std::endl;
}

void hanoi(int n, int s1, int s2, int s3)
{
    if (n == 1)
    {
        move(s1, s3);
        return;
    }

    hanoi(n - 1, s1, s3, s2);//步骤1 把第1号柱子上面的n-1个环经过3号个柱子移到2号柱子上
    move(s1, s3);             //步骤2 把1号柱子剩下的（最大的）一个盘子移到3号柱子上
    hanoi(n - 1, s2, s1, s3);//步骤3 最后把之前移到2号柱子上的n-1个环经过1号柱子移到3号柱子上
}

#if 0
void hanoi(int n, int s1, int s2, int s3)
{
    if (n == 1)
    {
        move(s1, s3);
    }
    else
    {
        hanoi(n - 1, s1, s3, s2);//步骤1 把第1号柱子上面的n-1个环经过3号个柱子移到2号柱子上
        move(s1, s3);             //步骤2 把1号柱子剩下的（最大的）一个盘子移到3号柱子上
        hanoi(n - 1, s2, s1, s3);//步骤3 最后把之前移到2号柱子上的n-1个环经过1号柱子移到3号柱子上
    }
}
#endif

int main()
{
    hanoi(3, 1, 2, 3);
    return 0;
}

