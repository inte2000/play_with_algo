// Dijkstra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Dijkstra_alg.h"

#if 0
Problem_T pd = 
{
    6,
    {
        { INFINITE, 3, 5, INFINITE, INFINITE, INFINITE },
        { INFINITE, INFINITE, 1, 2, 2, INFINITE },
        { INFINITE, INFINITE, INFINITE, INFINITE, 4, INFINITE },
        { INFINITE, INFINITE, INFINITE, INFINITE, 2, 4 },
        { INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 2 },
        { INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE }
    },
    0
};
Problem_T pd =
{
    8,
    {
        { INFINITE, 2, INFINITE, 1, INFINITE, 3, INFINITE, INFINITE },
        { 2, INFINITE, 6, 10, 5, INFINITE, 7, INFINITE },
        { INFINITE, 6, INFINITE, INFINITE, 9, INFINITE, INFINITE, 6 },
        { 1, 10, INFINITE, INFINITE, INFINITE, 5, 2, INFINITE },
        { INFINITE, 5, 9, INFINITE, INFINITE, INFINITE, 3, 4 },
        { 3, INFINITE, INFINITE, 5, INFINITE, INFINITE, 4, INFINITE },
        { INFINITE, 7, INFINITE, 2, 3, 4, INFINITE, 8 },
        { INFINITE, INFINITE, 6, INFINITE, 4, INFINITE, 8, INFINITE }
    },
    0
};
#endif

/*≤‚ ‘ ˝æ›*/
Problem_T pd =
{
    6,
    {
        { INFINITE, 3, 5, INFINITE, INFINITE, INFINITE },
        { INFINITE, INFINITE, 1, 2, 2, INFINITE },
        { INFINITE, INFINITE, INFINITE, INFINITE, 4, INFINITE },
        { INFINITE, INFINITE, INFINITE, INFINITE, 2, 4 },
        { INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 2 },
        { INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE }
    },
    0
};

int main()
{
    Dijkstra_T dj = { 0 };

    init_dijkstra(&dj, &pd);
    dijkstra(&dj, &pd);
    
    return 0;
}

