// Euler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

const int MAX_VERTEXNODE = 20;


typedef struct
{
    bool visited;
    std::vector<int> relVertex; //相邻边顶点
}VERTEX_NODE;

typedef struct
{
    int count; //图的顶点的个数
    VERTEX_NODE vertexs[MAX_VERTEXNODE]; //图的顶点列表
}EU_GRAPH;

void DsfEnumeration(EU_GRAPH& g, int node)
{
    g.vertexs[node].visited = true; //设置当前点的访问标志
    for (int i : g.vertexs[node].relVertex)
    {
        if (!g.vertexs[i].visited) //i是node的相邻点，并且i没有被访问过
        {
            DsfEnumeration(g, i);
        }
    }
}

void BsfEnumeration(EU_GRAPH& g, int node)
{
    std::queue<int> q;
    q.push(node); //起始位置入队列

    while (!q.empty())
    {
        int cur = q.front(); //取队首元素（顶点编号）
        q.pop(); //删除队首元素
        g.vertexs[cur].visited = true; //设置访问标志
        for (int i : g.vertexs[cur].relVertex)
        {
            if (!g.vertexs[i].visited) //i是cur的相邻点，并且i没有被访问过
            {
                q.push(i); //没有被访问过的顶点入队列
            }
        }

    }
}

bool IsConnected(EU_GRAPH& g)
{
    for (int i = 0; i < g.count; i++)
    {
        if (!g.vertexs[i].visited)
        {
            return false;
        }
    }
    
    return true;
}

bool IsEuler(EU_GRAPH& g)
{
    if (!IsConnected(g))
    {
        return false;
    }

    for (int i = 0; i < g.count; i++)
    {
        int n = g.vertexs[i].relVertex.size();
        if ((n & 1) != 0)
        {
            return false;
        }
    }

    return true;
}


int main()
{
    EU_GRAPH g = {  7,
                   { { false, {3, 4} },
                     { false, {3, 4, 5, 6} },
                     { false, {5, 6} },
                     { false, {0, 1, 2, 5} },
                     { false, {0, 1, 5, 6} },
                     { false, {1, 3, 4, 6} },
                     { false, {1, 2, 4, 5} }
                   }
                 };
    //DsfEnumeration(g, 0);
    BsfEnumeration(g, 0);
    bool isConnected = IsConnected(g);
    bool isEuler = IsEuler(g);

    return 0;
}

