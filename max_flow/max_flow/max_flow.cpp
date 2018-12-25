// max_flow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <stdio.h>
#include <string.h>
#include <queue>


const int MAX_GRAPH_NODE = 16;

typedef struct
{
    int node;
    int c[MAX_GRAPH_NODE][MAX_GRAPH_NODE];
}MF_GRAPH;

bool find_augmenting_path(MF_GRAPH& g, int s, int t, int path[])
{
    std::queue<int> q;
    bool visit[MAX_GRAPH_NODE] = { false };
    
    q.push(s);
    visit[s] = true;
    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        for (int i = 1; i <= g.node; ++i)
        {
            if (!visit[i] && (g.c[current][i] > 0))
            {
                visit[i] = true;
                path[i] = current;
                q.push(i);
                if (i == t) //遍历到汇点了？得到结果
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int get_min_delta(MF_GRAPH& g, int s, int t, int path[])
{
    int delta = 0x7FFFFFFF; //通过比较求最小值时的常用伎俩

    int i = t;
    while (i != s)
    {
        if (delta > g.c[path[i]][i])
        {
            delta = g.c[path[i]][i];
        }

        i = path[i];
    }

    return delta;
}

void modify_residual_networks(MF_GRAPH& g, int s, int t, int path[], int delta)
{
    int i = t;
    while (i != s)
    {
        g.c[path[i]][i] -= delta;
        g.c[i][path[i]] += delta;
        i = path[i];
    }
}

int edmonds_karp(MF_GRAPH& g, int s, int t)
{
    int max_flow = 0;
    int path[MAX_GRAPH_NODE] = { 0 };

    while (1)
    {
        //memset(path, 0, sizeof(path)); //这里可以清0，也可以不清0
        if (!find_augmenting_path(g, s, t, path))
        {
            break;
        }
        int delta = get_min_delta(g, s, t, path);
        modify_residual_networks(g, s, t, path, delta);
        max_flow += delta;
    }

    return max_flow;
}

//源点是0，汇点是5，期望最大流是23
void init_graph(MF_GRAPH& g)
{
    memset(&g, 0, sizeof(MF_GRAPH));

    g.node = 6;
    g.c[0][1] = 16;
    g.c[0][2] = 13;
    g.c[1][2] = 10;
    g.c[2][1] = 4;
    g.c[1][3] = 12;
    g.c[3][2] = 9;
    g.c[2][4] = 14;
    g.c[4][3] = 7;
    g.c[3][5] = 20;
    g.c[4][5] = 4;
}

#if 0
//源点是0，汇点是3，期望最大流是50
void init_graph(MF_GRAPH& g)
{
    memset(&g, 0, sizeof(MF_GRAPH));

    g.node = 4;
    g.c[0][1] = 40;
    g.c[0][3] = 20;
    g.c[1][3] = 20;
    g.c[1][2] = 30;
    g.c[2][3] = 10;

}
#endif

int main()
{
    MF_GRAPH g;
    init_graph(g);

    int max_flow = edmonds_karp(g, 0, 3);

    std::cout << "max_flow = " << max_flow  << std::endl;
    
    return 0;
}
