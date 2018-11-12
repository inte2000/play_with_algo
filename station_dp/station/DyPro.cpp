#include "stdafx.h"
#include "DyPro.h"



void fast_station_sequence(Program_T *para, Result_T *result)
{
    //初始进站化边界值
    result->f[0][0] = para->a[0][0] + para->e[0];
    result->f[1][0] = para->a[1][0] + para->e[1];

    //递推关系计算
    for(int j = 1; j < STATIONS; j++)
    {
        if((result->f[0][j - 1] + para->a[0][j]) <= (result->f[1][j - 1] + para->t[1][j] + para->a[0][j]))
        {
            result->f[0][j] = result->f[0][j - 1] + para->a[0][j];
            result->line[0][j] = 0;
        }
        else
        {
            result->f[0][j] = result->f[1][j - 1] + para->t[1][j] + para->a[0][j];
            result->line[0][j] = 1;
        }
        if((result->f[1][j - 1] + para->a[1][j]) <= (result->f[0][j - 1] + para->t[0][j] + para->a[1][j]))
        {
            result->f[1][j] = result->f[1][j - 1] + para->a[1][j];
            result->line[1][j] = 1;
        }
        else
        {
            result->f[1][j] = result->f[0][j - 1] + para->t[0][j] + para->a[1][j];
            result->line[1][j] = 0;
        }
    }
    //计算离站边界值
    if(result->f[0][STATIONS - 1] + para->x[0] <= result->f[1][STATIONS - 1] + para->x[1])
    {
        result->fs = result->f[0][STATIONS - 1] + para->x[0];
        result->ls = 0;
    }
    else
    {
        result->fs = result->f[1][STATIONS - 1] + para->x[1];
        result->ls = 1;
    }
}
