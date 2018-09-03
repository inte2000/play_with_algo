#include "stdafx.h"

/*
int ls[9] = { 0, 12, 45, 21, 78, 84, 7, 13, 65};
insert_sort(ls, 8);

int ls2[8] = { 12, 45, 21, 78, 84, 7, 13, 65};
insert_sort2(ls2, 8);

*/

//带哨兵位的插入排序，ls[0]是哨兵位
void insert_sort(int *ls, int n)
{
    for (int i = 2; i <= n; ++i)
    {
        if (ls[i] < ls[i - 1])
        {
            ls[0] = ls[i];//i位置的数存入哨兵位，因为i位置会被后面的移动数据操作覆盖
            int j = i;
            while (ls[j - 1] > ls[0])//不用再判断j是否越界，直接判断当前位置的值是否大于哨兵位
            {
                ls[j] = ls[j - 1];
                j--;
            }
            ls[j] = ls[0];
        }
    }
}

//不带哨兵位的插入排序
void insert_sort2(int *ls, int n)
{
    for (int i = 1; i < n; ++i)
    {
        if (ls[i] < ls[i - 1])
        {
            int cur = ls[i];//需要临时空间存i位置的值
            int j = i;
            while ((j > 0) && (ls[j - 1] > cur))//需要额外增加判断j是否越界
            {
                ls[j] = ls[j - 1];
                j--;
            }
            ls[j] = cur;
        }
    }
}
