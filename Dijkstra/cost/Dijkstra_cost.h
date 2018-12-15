#pragma once

const int MAX_VERTEX = 10;
const int INFINITE = 108000; //十万八千里

typedef struct
{
    int weight;
    int cost;
}Edge_T;

typedef struct
{
    int vertexs;  //题目给出的实际顶点个数
    Edge_T w[MAX_VERTEX][MAX_VERTEX]; //图的矩阵，表示距离和开销
    int start_vertex;   //起始点编号
}Problem_T;


typedef struct
{
    int value;  
    int cost;    
    bool is_in_t;  
}Dist_T;


typedef struct
{
    int vertexs;  //题目给出的实际顶点个数
    int T[MAX_VERTEX];  //集合T
    int tc; //当前T中顶点个数
    Dist_T dist[MAX_VERTEX];  //dist数组
}Dijkstra_T;


void init_dijkstra(Dijkstra_T *dj, Problem_T *p_data);
void dijkstra(Dijkstra_T *dj, Problem_T *p_data);
