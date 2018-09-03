// base.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


void sign_unsign()
{
    int i = -10;
    unsigned int u = 5;

    int a1 = i + u;
    unsigned int a2 = i + u;

    std::cout << i + u << std::endl;
    std::cout << a2 << std::endl;

    if (u > i)
    {
        std::cout << "Alice" << std::endl;
    }
    else
    {
        std::cout << "Bob" << std::endl;
    }
}

const int MAX_TREE_NODE = 18;

void pre_order(char array_tree[], int root)
{
    if ((root >= MAX_TREE_NODE) || (array_tree[root] == -1))
    {
        return;
    }

    std::cout << array_tree[root];
    pre_order(array_tree, 2 * root + 1);
    pre_order(array_tree, 2 * root + 2);
}

unsigned int bkdr_hash(const char *str)
{
    unsigned int hash = 0;
    while (*str != 0)
    {
        int ch = (int)*str++;
        hash = hash * 31 + ch;   // 乘法因子还可以是 131、1313、13131、131313... 
    }

    return hash;
}

unsigned int knuth_hash(const char *str)
{
    unsigned int hash = 1315423911;
    while (*str != 0)
    {
        int ch = (int)*str++;
        hash = ((hash << 5) ^ (hash >> 27)) ^ ch;
    }

    return hash;
}

unsigned int fnv_hash(const char *str)
{
    unsigned int hash = 2166136261;
    while (*str != 0)
    {
        int ch = (int)*str++;
        hash *= 16777619;
        hash ^= ch;
    }

    return hash;
}

int main()
{
    sign_unsign();

    char array_tree[MAX_TREE_NODE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', -1, -1, -1};

    pre_order(array_tree, 0);

    return 0;
}

