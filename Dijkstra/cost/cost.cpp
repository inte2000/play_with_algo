// cost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Dijkstra_cost.h"

//²âÊÔÊý¾Ý
Problem_T pd =
{
    8,
    {
        { {INFINITE, 0}, {20,9}, {INFINITE, 0}, {10,12}, {INFINITE, 0}, {30, 21}, {INFINITE, 0}, {INFINITE, 0} },
        { {INFINITE, 0}, {INFINITE, 0}, {60,47}, {INFINITE, 0}, {50,61}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0} },
        { {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {60,29} },
        { {INFINITE, 0}, {100,65}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {20,25}, {INFINITE, 0} },
        { {INFINITE, 0}, {INFINITE, 0}, {90,65}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {40,33} },
        { {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {50,54}, {INFINITE, 0}, {INFINITE, 0}, {40,55}, {INFINITE, 0} },
        { {INFINITE, 0}, {70,45}, {INFINITE, 0}, {INFINITE, 0}, {30,15}, {INFINITE, 0}, {INFINITE, 0}, {80,57} },
        { {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0}, {INFINITE, 0} }
    },
    0
};

//12 + 25 + 15 + 33 = 85

void print_result(Dijkstra_T *dj, int dest_vertex)
{
    if (dj->dist[dest_vertex].value == INFINITE)
    {
        std::cout << "No result!" << std::endl;
        return;
    }

    std::cout << dj->dist[dest_vertex].value << "  " << dj->dist[dest_vertex].cost << std::endl;
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
