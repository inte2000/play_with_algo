// Hungary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <utility>
#include <vector>

const int UNIT_COUNT = 5;

typedef struct 
{
    int edge[UNIT_COUNT][UNIT_COUNT];
    bool on_path[UNIT_COUNT];
    int path[UNIT_COUNT];
    int max_match;
}GRAPH_MATCH;

bool FindAugmentPath(GRAPH_MATCH *match, int xi)
{
    for (int yj = 0; yj < UNIT_COUNT; yj++)
    {
        if ((match->edge[xi][yj] == 1) && !match->on_path[yj])
        {
            match->on_path[yj] = true;
            if ((match->path[yj] == -1)
                || FindAugmentPath(match, match->path[yj]))
            {
                match->path[yj] = xi;
                return true;
            }
        }
    }

    return false;
}


void ClearOnPathSign(GRAPH_MATCH *match)
{
    for (int i = 0; i < UNIT_COUNT; i++)
    {
        match->on_path[i] = false;
    }
}

bool Hungary_Match(GRAPH_MATCH *match)
{
    for (int xi = 0; xi < UNIT_COUNT; xi++)
    {
        if (FindAugmentPath(match, xi))
        {
            match->max_match++;
        }

        ClearOnPathSign(match);
    }
    return (match->max_match == UNIT_COUNT);
}

void PrintResult(GRAPH_MATCH *match)
{
    for (int i = 0; i < match->max_match; i++)
    {
        std::cout << match->path[i] + 1 << "<--->" << i + 1 << std::endl;
    }
}

void InitGraph(GRAPH_MATCH *match, std::vector<std::pair<int,int>>& edges)
{
    match->max_match = 0;
    memset(match->edge, 0, UNIT_COUNT * UNIT_COUNT * sizeof(int));
    for (int i = 0; i < UNIT_COUNT; i++)
    {
        match->on_path[i] = false;
        match->path[i] = -1;
    }

    for (auto& e : edges)
    {
        match->edge[e.first - 1][e.second - 1] = 1;
    }
}

int main()
{
    GRAPH_MATCH match = { 0 };
    std::vector<std::pair<int, int>> edges = { {1, 3}, 
                                               {2, 1}, {2, 2}, 
                                               {3, 2}, {3, 3}, {3, 4},
                                               {4, 2}, {4, 3},
                                               {5, 3}, {5, 4}, {5, 5} };
    InitGraph(&match, edges);
    if (Hungary_Match(&match))
    {
        PrintResult(&match);
    }

    return 0;
}

