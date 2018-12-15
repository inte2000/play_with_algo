// Topological.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <queue>
#include <iostream>

const int MAX_VERTEXNODE = 20;

typedef struct 
{
    char *name;   //活动名称
    int days;     //完成活动所需时间
    int sTime;    //活动最早开始时间
    int inDeg;  //活动的前驱节点个数(入度)
    std::vector<int> adjNode; //相邻活动列表(节点索引)
}VERTEX_NODE;

typedef struct 
{
    int count; //图的顶点个数
    VERTEX_NODE vertexs[MAX_VERTEXNODE]; //图的顶点列表
}TP_GRAPH;

TP_GRAPH graph =
{
    9,
    {
        { "P1", 8, 0, 0,{ 2, 6 } },
        { "P2", 5, 0, 0,{ 2, 4 } },
        { "P3", 6, 8, 2,{ 3 } },
        { "P4", 4, 14,2,{ 5, 8 } },
        { "P5", 7, 5, 1,{ 3, 5 } },
        { "P6", 7, 18, 2,{} },
        { "P7", 4, 8, 1,{ 7 } },
        { "P8", 3, 12, 1,{ 8 } },
        { "P9", 4, 18, 2,{} }
    }
};

struct QUEUE_ITEM
{
    int node;
    int sTime;
    bool operator < (const QUEUE_ITEM &a) const
    {
        return sTime > a.sTime;//最小值优先     
    }
};

void EnQueue(std::priority_queue<QUEUE_ITEM>& q, int node, int sTime)
{
    QUEUE_ITEM item = { node, sTime };
    q.push(item);
}

int DeQueue(std::priority_queue<QUEUE_ITEM>& q)
{
    int node = q.top().node;
    q.pop();
    return node;
}

bool TopologicalSorting(TP_GRAPH *g, std::vector<int>& sortedNode)
{
    std::priority_queue<QUEUE_ITEM> nodeQueue;

    //第一步：所有入度为0的顶点入队（栈）
    for (int i = 0; i < g->count; i++)
    {
        if (g->vertexs[i].inDeg == 0)
        {
            EnQueue(nodeQueue, i, g->vertexs[i].sTime);
        }
    }
    //第二步：队列（栈）顶元素处理
    while (nodeQueue.size() != 0)
    {
        int node = DeQueue(nodeQueue); //按照开始时间优先级出队（栈）
        sortedNode.push_back(node);  //输出当前节点，按照顺序排入sortedNode数组中
        
        //遍历节点node的所有邻接点，将表示有向边inDeg值减1
        for (int adjNode : g->vertexs[node].adjNode)
        {
            g->vertexs[adjNode].inDeg--;
            //如果inDeg值为0，则该节点入队列（栈）
            if (g->vertexs[adjNode].inDeg == 0)
            {
                EnQueue(nodeQueue, adjNode, g->vertexs[adjNode].sTime);
            }
        }
    }

    return (sortedNode.size() == g->count);
}

void PrintSorting(TP_GRAPH *g, const std::vector<int>& sortedNode)
{
    for (int node : sortedNode)
    {
        std::cout << g->vertexs[node].name << std::endl;
    }
}

int main(int argc, char* argv[])
{
    std::vector<int> sortedNode;
    if (!TopologicalSorting(&graph, sortedNode))
    {
        std::cout << "Graph has circle!" << std::endl;
        return -1;
    }
    PrintSorting(&graph, sortedNode);
    return 0;
}

