// triangle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>   



const int INFINITE = 0x0FFFFFFF;
const int N = 6;     //凸多边形边数  

typedef struct
{
    int d[N][N];  //d[i][j]表示多边形{Vi - Vj}的最优权值
    int k[N][N];  //k[i][j]记录Vi到Vj最优三角剖分的中间点K
}RESULT;

//凸多边形的权  
int weight[N][N] = 
{
    { 0,2,2,3,1,4 },
    { 2,0,1,5,2,3 },
    { 2,1,0,2,1,4 },
    { 3,5,2,0,6,2 },
    { 1,2,1,6,0,1 },
    { 4,3,4,2,1,0 }
};

int triangle_weight(int a, int b, int c) //计算三角形权重
{
    return weight[a][b] + weight[b][c] + weight[c][a];
}

void polygon_triangulation(RESULT *result)
{
    int min_d;

    //初始化边界值
    for (int m = 1; m < N; m++)
    {
        result->d[m][m] = 0;
    }

    //开始规划
    for (int r = 2; r < N; r++) //子多边形规模遍历
    {
        for (int i = 1; i < N - r + 1; i++) //子多边形遍历，确定起始点Vi
        {
            int j = i + r - 1;  //确定Vj,r是子问题规模
            //遍历从Vi到Vj的点（不包括Vj）, 找最小权重值分割的k点
            min_d = INFINITE; 
            for (int k = i; k < j; k++)
            {
                //递推计算
                result->d[i][j] = result->d[i][k] + result->d[k + 1][j] + triangle_weight(i - 1, k, j);
                if (result->d[i][j] < min_d) 
                {
                    min_d = result->d[i][j];
                    result->k[i][j] = k;  //记下这个分割点
                }
            }
            result->d[i][j] = min_d;
        }
    }
}

void trace_result(RESULT *result, int i, int j)
{
    if (i == j)
    {
        return;
    }

    trace_result(result, i, result->k[i][j]);    //输出一个子多边形的剖分结果
    trace_result(result, result->k[i][j] + 1, j);    //输出另一个子多边形的剖分结果
    
    //输出当前三角形，k[i][j]是动态规划去搜索过程中记录下的最优剖分点
    std::cout << "triangle: { V" << i - 1 << " V" << result->k[i][j] << " V" << j << " }" << std::endl;
}



int main()
{
    RESULT result = { 0 };
    polygon_triangulation(&result);
    std::cout << "result: " << result.d[1][N - 1] << std::endl;
    trace_result(&result, 1, N-1);
    return 0;
}
