// Path.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Dijkstra_path.h"

/*
8 
梁山 尖庄 茅台 景德镇 雄安 敦煌 龙门 方腊
0 7
15
0 1 20
0 3 10
0 5 30
1 2 60
1 4 50
2 7 60
3 1 100
3 6 20
4 2 90
4 7 40
5 3 50
5 6 40
6 1 70
6 4 30
6 7 80
*/

Problem_T pd =
{
    8,
    {
        { INFINITE, 20, INFINITE, 10, INFINITE, 30, INFINITE, INFINITE },
        { INFINITE, INFINITE, 60, INFINITE, 50, INFINITE, INFINITE, INFINITE },
        { INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 60 },
        { INFINITE, 100, INFINITE, INFINITE, INFINITE, INFINITE, 20, INFINITE },
        { INFINITE, INFINITE, 90, INFINITE, INFINITE, INFINITE, INFINITE, 40 },
        { INFINITE, INFINITE, INFINITE, 50, INFINITE, INFINITE, 40, INFINITE },
        { INFINITE, 70, INFINITE, INFINITE, 30, INFINITE, INFINITE, 80 },
        { INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE },
    },
    0
};

void print_result(Dijkstra_T *dj, int dest_vertex)
{
    if (dj->dist[dest_vertex].value == INFINITE)
    {
        std::cout << "No result!" << std::endl;
        return;
    }

    std::cout << "Total " << dj->dist[dest_vertex].value << " days" << std::endl;
    std::cout << "Path: " ;
    for (int i = 0; i < dj->dist[dest_vertex].pc; i++)
    {
        std::cout << dj->dist[dest_vertex].path[i] << " -> ";
    }
    std::cout << dest_vertex << std::endl;
}

#define ONLINE_JUDGE

int main()
{
    Dijkstra_T dj = { 0 };

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    init_dijkstra(&dj, &pd);
    dijkstra(&dj, &pd);
    print_result(&dj, 7);

#ifndef ONLINE_JUDGE
    fclose(stdin);
#endif
    return 0;
}

