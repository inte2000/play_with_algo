// investment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MAX_N 32 // 最大投资项目数目 
#define MAX_M 128 // 最大投资钱数(百万)

// 第i项投资j万元的收益 1 <= i <= n, 1 <= j <= m 
int f[MAX_N][MAX_M] = 
{
    {0, 60, 80, 105, 115, 130, 150},
    {0, 65, 85, 110, 140, 160, 175},
    {0, 75, 100, 120, 135, 150, 180}
};

void print_result(int n, int m, int max[][MAX_M])
{
    int invesment[MAX_N] = { 0 };
    
    invesment[n - 1] = max[n - 1][m];
    for (int i = n - 2; i >= 0; --i) 
    {
        int t = 0;
        for (int j = n - 1; j > i; --j) 
        {
            t += invesment[j];
        }
        invesment[i] = max[i][m - t];
    }

    for (int x = 0; x < n; x++)
    {
        printf("Invest %d for project %d\n", invesment[x], x + 1);
    }
}

// n个项目,投资m百万元 
int investment(int n, int m, int d[][MAX_M], int max[][MAX_M])
{
    //初始化（也就是只有一个项目的情况）
    for (int x = 0; x <= m; x++)
    {
        d[0][x] = f[0][x];  // 投资第一个项目 
        max[0][x] = x; //标记函数初始化
    }
    
    for(int i = 1; i < n; i++) // 投资前i个项目 
    { 
        for(int j = 0; j <= m; j++) // 前 i 个项目总投入的钱数 j 
        { 
            for(int k = 0; k <= j; k++) // 投资当前项目的钱数（第 i 个项目）
            { 
                int tmp = f[i][k] + d[i - 1][j-k]; 
                if(tmp > d[i][j]) //d[i][j]初始化都是0
                { 
                    d[i][j] = tmp; // 更新当前的最优解 
                    max[i][j] = k; // 更新标记函数 
                } 
            } 
        } 
    } 

    return d[n - 1][m];
} 

    
int main()
{
    int d[MAX_N][MAX_M] = { { 0 } }; // 投资前 i 个项目 j 百万的最大收益
    int max[MAX_N][MAX_M] = { { 0 } }; // 投资决策标记值

    int benefit = investment(3, 6, d, max);
    printf("Total benefit : %d\n", benefit);
    print_result(3, 6, max); // 打印结果 
    return 0;
}

