#pragma once

#define  STATIONS             6
#define  LINES                2


typedef struct
{
    int a[LINES][STATIONS];
    int t[LINES][STATIONS];
    int e[LINES];
    int x[LINES];
}Program_T;

typedef struct
{
    int line[LINES][STATIONS];  //遍历过程中的最优决策
    int ls;
    int f[LINES][STATIONS];  //当前已知的决策状态
    int fs;   //最优解的值
}Result_T;



void fast_station_sequence(Program_T *para, Result_T *result);

