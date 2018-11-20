// MondriaanDream.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

const int MAX_STATE = 32;  //2^N
const int MAX_M = 1000 + 2;  //M
const int MAX_N = 8;  //M

int bitMask[MAX_N] = {0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080};
#if 0
void dfs(int N, long long d[][MAX_STATE], int i, int j, int state, int next)
{
    if (j == N)
    {
        d[i + 1][next] += d[i][state];
        return;
    }
    //如果这个位置已经被上一列所占用,直接跳过
    if ((bitMask[j] & state) > 0)
        dfs(N, d, i, j + 1, state, next);
    //如果这个位置是空的，尝试放一个1*2的
    if ((bitMask[j] & state) == 0)
        dfs(N, d, i, j + 1, state, next | bitMask[j]);
    //如果这个位置以及下一个位置都是空的，尝试放一个2*1的
    if (j + 1 < N && (bitMask[j] & state) == 0 && (bitMask[j + 1] & state) == 0)
        dfs(N, d, i, j + 2, state, next);
}

long long MondriaanDream(int N, int M)
{
    long long d[MAX_M][MAX_STATE];
    
    memset(d, 0, sizeof(d));
    d[1][0] = 1;

    int totalState = (1 << N);
    for (int i = 1; i <= M; i++)
    {
        for (int state = 0; state < totalState; state++)
        {
            if (d[i][state] > 0)
            {
                dfs(N, d, i, 0, state, 0);
            }
        }
    }
    
    return d[M + 1][0];
}
#endif

void update(long long d[][MAX_STATE], int N, int cur, int a, int b)//a是包含m位1进制数的老状态，b是包含m+1位1进制数的新状态
{
    
    if (b & bitMask[N])
    {
        d[cur][b ^ bitMask[N]] += d[1 - cur][a];//只有新轮廓线首位为1时才更新
    }
}

long long MondriaanDream2(int N, int M)
{
    long long d[MAX_M][MAX_STATE];

    memset(d, 0, sizeof(d));

    int totalState = (1 << N);
    int cur = 0;
    d[cur][totalState - 1] = 1;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cur ^= 1;
            memset(d[cur], 0, sizeof(d[cur]));
            for (int k = 0; k < totalState; k++)//k的二进制形式表示前一个格子的轮廓线状态
            {
                update(d, N, cur, k, k << 1);//当前格不放，直接k左移一位就表示带m+1位的新轮廓线的状态
                if (i && !(k&bitMask[N - 1])) update(d, N, cur, k, (k << 1) ^ bitMask[N] ^ 1);//上放，要求轮廓线首为0
                if (j && (!(k & 1))) update(d, N, cur, k, (k << 1) ^ 3);//左放，要求轮廓线尾0，首1
            }
        }
    }
    return d[cur][(1 << N) - 1];
}

//i：第几行，j：第几列， prev是i-1行的状态，state 是i行的状态
void state_dfs(int n, long long d[][MAX_STATE], int i, int j, int prev, int state)
{ 
    if (j == n) //j==n表示已经越界了，不需要继续递归了
    {
        d[i][state] += d[i - 1][prev]; //前i-1行的prev状态经过变化后能够变成i行的state状态
        return;
    }

    //如果这个位置已经被上一列所占用,直接跳过
    if ((bitMask[j] & state) > 0)
    {
        state_dfs(n, d, i, j + 1, prev, state);
    }
    //如果这个位置是空的，尝试放一个1 x 2的（竖排）
    if ((bitMask[j] & state) == 0)
    {
        state_dfs(n, d, i, j + 1, prev, state);
    }
    //如果这个位置以及下一个位置都是空的，尝试放一个2*1的
    if ((j < n - 1) && !(state & bitMask[j]) && !(state&bitMask[j + 1]))
    {
        state_dfs(n, d, i, j + 2, prev, state | bitMask[j] | bitMask[j + 1]);
    }
}

long long MondriaanDream(int n, int m)
{
    long long d[MAX_M][MAX_STATE];

    memset(d, 0, sizeof(d));

    int finalState = (1 << n) - 1;
   
    d[0][finalState] = 1;
    for (int i = 1; i <= m; ++i)
    {
        for (int state = 0; state < (1 << n); ++state)
        {
            if (d[i - 1][state] > 0)
            {
                state_dfs(n, d, i, 0, state, ~state & finalState);
            }
        }
    }
    return d[m][finalState];
}


int main()
{
    long long count = MondriaanDream(4, 11);
    count = MondriaanDream2(4, 11);

    count = MondriaanDream(2, 11);
    count = MondriaanDream2(2, 11);


    count = MondriaanDream(4, 2);
    count = MondriaanDream2(4, 2);

    std::cout << count << std::endl;
}

/*
1 2
1 3
1 4
2 2
2 3
2 4
2 11
4 11
0 0

Sample Output

1
0
1
2
3
5
144
51205
*/