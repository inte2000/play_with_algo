// box.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cassert>
#include "BoxGameMap.h"
#include "BoxGame.h"

/*
const int MAP_ROW = 8;
const int MAP_COL = 8;

char map[64] = 
{
    { ' ',' ','X','X','X',' ',' ',' ' },
    { ' ',' ','X','?','X',' ',' ',' ' },
    { ' ',' ','X',' ','X','X','X','X' },
    { 'X','X','X','O',' ','O','?','X' },
    { 'X','?',' ','O','*','X','X','X' },
    { 'X','X','X','X','O','X',' ',' ' },
    { ' ',' ',' ','X','?','X',' ',' ' },
    { ' ',' ',' ','X','X','X',' ',' ' }
};
*/
/*
const int MAP_ROW = 9;
const int MAP_COL = 9;

char map[81] =
{
     'A','A','A','A','X','X','X','X','X',
     'A','A','A','A','X',' ',' ','@','X',
     'X','X','X','A','X','B','B',' ','X',
     'X','#','X','A','X',' ','B',' ','X',
     'X','#','X','X','X',' ','X','X','A',
     'X','#',' ',' ',' ',' ','X','X','A',
     'X',' ',' ','X',' ',' ',' ','X','X',
     'X','X','X','X',' ',' ',' ','X','X',
     'A','A','A','X','X','X','X','X','A' 
};
*/
/*
const int MAP_ROW = 11;
const int MAP_COL = 13;

char map[] =
{
    'A','A','A','X','X','X','X','X','X','X','A','A','A',
    'X','X','X','X',' ',' ',' ',' ',' ','X','A','A','A',
    'X',' ',' ',' ','#','X','X','X',' ','X','A','A','A',
    'X',' ','X',' ','X',' ',' ',' ',' ','X','X','A','A',
    'X',' ','X',' ','B',' ','B','X','#',' ','X','A','A',
    'X',' ','X',' ',' ','X',' ',' ','X',' ','X','A','A',
    'X',' ','#','X','B',' ','B',' ','X',' ','X','A','A',
    'X','X',' ',' ',' ',' ','X',' ','X',' ','X','X','X',
    'A','X',' ','X','X','X','#',' ',' ',' ',' ','@','X',
    'A','X',' ',' ',' ',' ',' ','X','X',' ',' ',' ','X',
    'A','X','X','X','X','X','X','X','X','X','X','X','X'
};
*/
/*
const int MAP_ROW = 5;
const int MAP_COL = 5;

char map[] =
{
    'X','X','X','X','X',
    'X','#',' ',' ','X',
    'X',' ','B',' ','X',
    'X',' ',' ','@','X',
    'X','X','X','X','X'
};
*/

const int MAP_ROW = 8;
const int MAP_COL = 10;

char map[] =
{
    'A','A','X','X','X','X','A','A','A','A',
    'A','A','X','@',' ','X','X','X','A','A',
    'A','A','X',' ','B',' ',' ','X','A','A',
    'A','X','X','X',' ','X',' ','X','X','A',
    'A','X','#','X',' ','X',' ',' ','X','A',
    'A','X','#','B',' ',' ','X',' ','X','A',
    'A','X','#',' ',' ',' ','B',' ','X','A',
    'A','X','X','X','X','X','X','X','X','A',
};



int main()
{
    try
    {
        BoxGame game;
        LARGE_INTEGER t1, t2, tc;
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        if (game.InitMap(map, MAP_ROW, MAP_COL))
        {
            game.ResolveGame();
        }
        QueryPerformanceCounter(&t2);
        std::cout << "Use Time: " << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << std::endl;

    }
    catch (...)
    {
    }
    return 0;
}

