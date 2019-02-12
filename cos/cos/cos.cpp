// cos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>

const int VN = 11;

const char *base_words[] = 
{
    "进攻", "炮弹", "射程", "榴弹炮", "发射", "口径", "迫击炮", "瞄准", "后坐力", "弹道", "目标"
};

//口径为155毫米的榴弹炮，炮弹的射程超过40公里，炮弹发射后击中目标的弹道是一条抛物线
//大口径榴弹炮射程很远且弹道弯曲，炮弹通常都不是直接对着目标瞄准，而是计算好抛物线弹道，以一定的仰角和方向发射炮弹
//我们必须统一口径，抵挡敌人发射的糖衣炮弹的进攻
//
double CosSimilarity(double *va, double *vb, int vn)
{
    double cossu = 0.0;
    double cossda = 0.0;
    double cossdb = 0.0;

    for (int i = 0; i < vn; i++)
    {
        cossu += va[i] * vb[i];
        cossda += va[i] * va[i];
        cossdb += vb[i] * vb[i];
    }


    return cossu / (std::sqrt(cossda) * std::sqrt(cossdb));
}

int main()
{
    double v1[] = { 0, 2, 1, 1, 1, 1, 0, 0, 0, 1, 1 };
    double v2[] = { 0, 2, 1, 1, 1, 1, 0, 1, 0, 2, 1 };
    double v3[] = { 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0 };

    double s1 = CosSimilarity(v1, v2, VN);
    double s2 = CosSimilarity(v1, v3, VN);
    double s3 = CosSimilarity(v2, v3, VN);

    return 0;
}

