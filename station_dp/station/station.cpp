// station.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "DyPro.h"
//≤‚ ‘ ˝æ›
Program_T pd =
{
    { //a
        { 7, 9, 3, 4, 8, 4 },
        { 8, 5, 6, 4, 5, 7 }
    },
    { //t
        { 0, 2, 3, 1, 3, 4 },
        { 0, 2, 1, 2, 2, 1 }
    },
    { 2, 4 }, //e
    { 3, 2 } //x
};


void print_result(Result_T *result)
{
    std::cout << "Total Time " << result->fs << std::endl;

    int i = result->ls;
    std::cout << "Station " << STATIONS << " on Line " << i + 1 << std::endl;
    for (int j = STATIONS - 1; j > 0; j--)
    {
        i = result->line[i][j];
        std::cout << "Station " << j << " on Line " << i + 1 << std::endl;
    }
}


int main()
{
    Result_T r = { 0 };

    fast_station_sequence(&pd, &r);

    print_result(&r);

    return 0;
}

