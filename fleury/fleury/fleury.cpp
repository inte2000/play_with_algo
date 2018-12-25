// fleury.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>

const int MAX_VERTEXNODE = 16;



typedef struct
{
    int vertexs;
    int edges; //图的边数
    int edge[MAX_VERTEXNODE][MAX_VERTEXNODE]; //邻接矩阵
}FE_GRAPH;


void DeleteEdge(FE_GRAPH& g, int u, int v)
{
    g.edge[u][v] = 0;
    g.edge[v][u] = 0;
}

void AddEdge(FE_GRAPH& g, int u, int v)
{
    g.edge[u][v] = 1;
    g.edge[v][u] = 1;
}

void fleury(FE_GRAPH& g, std::queue<int>& s, int cur, int start)
{
    bool flag = false;  //是否还有与cur关联的边
    s.push(cur);
    for (int i = start; i < g.vertexs; i++)
    {
        if (g.edge[cur][i] == 1)
        {
            flag = true;
            DeleteEdge(g, cur, i);
            fleury(g, s, i, 0);
            break;
        }
    }

    //没有顶点与当前节点cur相连
    if (!flag)
    {
        s.pop(); //抛弃最后入栈的那个顶点
        int m = s.front();
        AddEdge(g, cur, m);  //没有顶点与当前顶点相连，说明之前删除的是桥，先恢复这条边
        int new_start = cur + 1;
        if (s.size() == g.edges)
        { 
            s.push(cur);
        }
        else
        {
            s.pop();
            fleury(g, s, m, new_start);
        }
    }
}

int main()
{
    FE_GRAPH g = { 7, 12,
                    { { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
                    }
                };

    std::queue<int> s;

    fleury(g, s, 0, 1);

    return 0;
}

