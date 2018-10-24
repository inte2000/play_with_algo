// Station.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>



#define  STATIONS         6
#define  LINES                2


typedef struct 
{
    int assemble_time[LINES][STATIONS];
    int transport_time[LINES][STATIONS];
    int enter_time[LINES];
    int exit_time[LINES];
}Program_T;

typedef struct
{
    int line[STATIONS];  //遍历过程中的当前结果记录
    int fs;
    int fline[STATIONS];  //当前已知的最优结果
    int ffs;
}Result_T;

void search_stations_sequence(Result_T *rt, Program_T *para, int line, int station)
{
    if (station == (STATIONS - 1)) //1. 完成装配，整理一次结果，退出当前递归子结构
    {
        rt->fs += para->assemble_time[line][station];
        rt->fs += para->exit_time[line];
        rt->line[station] = line;
        if (rt->fs < rt->ffs) /*当前穷举到的路径时间开销更小*/
        {
            rt->ffs = rt->fs;
            memmove(rt->fline, rt->line, STATIONS * sizeof(int));
        }
        return;
    }

    //2. 记录中间结果到line属性中
    int curCost = rt->fs + para->assemble_time[line][station];
    rt->line[station] = line;

    //3. 调整line和station参数，完成递归子结构的动作
    /*选择本装配线的下一个装配站，开销忽略不计*/
    rt->fs = curCost;
    search_stations_sequence(rt, para, line, station + 1);

    /*选择另一条装配线的下一个装配站，需要计算转移开销*/
    rt->fs = curCost;
    rt->fs += para->transport_time[line][station + 1];
    int nextline = (line + 1) % LINES;
    search_stations_sequence(rt, para, nextline, station + 1);
}

void init_result(Result_T *rt)
{
    for (int i = 0; i < STATIONS; i++)
    {
        rt->line[i] = 0;
        rt->fline[i] = 0;
    }

    rt->fs = 0;
    rt->ffs = 0x0FFFFFFF;
}

void print_result(Result_T *rt)
{
    std::cout << "Total Time " << rt->ffs << std::endl;
    for (int i = 0; i < STATIONS; i++)
    {
        std::cout << "Station " << i + 1 << " on Line " << rt->fline[i] + 1 << std::endl;
    }
}


//测试数据
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

int main()
{

    Result_T result;

    init_result(&result);

    result.fs = pd.enter_time[0];  //装配线1的进入开销
    search_stations_sequence(&result, &pd, 0, 0); //从第一条装配线开始
    result.fs = pd.enter_time[1];  //装配线2的进入开销
    search_stations_sequence(&result, &pd, 1, 0); //从第二条装配线开始

    print_result(&result);

    return 0;
}

