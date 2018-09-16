// eq.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrix.h"
#include <iostream>
#include <vector>

const double PRECISION = 0.000000001;

const int VEC_N = 3;
#if 0
double an[VEC_N][VEC_N] =
{
    {4.0, -1.0, 1.0},
    {4.0, -8.0, 1.0},
    {-2.0, 1.0, 5.0}
};

double bn[VEC_N] = {7.0, -21.0, 15.0};
#endif

double an[VEC_N][VEC_N] =
{
    { 5.0, 2.0, 1.0 },
    { -1.0, 4.0, 2.0 },
    { 2.0, -3.0, 10.0 }
};

double bn[VEC_N] = { -12.0, 20.0, 3.0 };

double calc_max_diff(double xt[], double x[], int n)
{
    double max_diff = std::fabs(xt[0] - x[0]);
    for (int i = 1; i < n; i++)
    {
        double diff = std::fabs(xt[i] - x[i]);
        if (diff > max_diff)
        {
            max_diff = diff;
        }
    }

    return max_diff;
}

void jacobi_eqn(double a[][VEC_N], double b[], int n, double x[])
{
    double xt[VEC_N];
    double max_diff = 0.0;
    int count = 0;
    do
    {
        for (int i = 0; i < n; i++)
        {
            double sum = 0.0;
            for (int k = 0; k < n; k++)
            {
                if (i != k)  //对角线元素不计算
                {
                    sum += a[i][k] * x[k];
                }
            }
            xt[i] = (b[i] - sum) / a[i][i];   //根据关系计算xi的新值
        }

        max_diff = calc_max_diff(xt, x, n);

        for (int j = 0; j < n; j++)
        {
            x[j] = xt[j]; //更新x，准备下一次迭代
        }
        count++;
    } while (max_diff > PRECISION);

    std::cout << count << std::endl;
}

void gauss_seidel_eqn(double a[][VEC_N], double b[], int n, double x[])
{
    double max_diff = 0.0;
    int count = 0;
    do
    {
        max_diff = 0.0;
        for (int i = 0; i < n; i++)
        {
            double sum = 0.0;
            for (int k = 0; k < n; k++)
            {
                if (i != k)  //对角线元素不计算
                {
                    sum += a[i][k] * x[k];
                }
            }
            double xt = (b[i] - sum) / a[i][i];   //根据关系计算xi的新值
            if (std::fabs(xt - x[i]) > max_diff)
            {
                max_diff = std::fabs(xt - x[i]);
            }
            x[i] = xt;
        }

        count++;
    } while (max_diff > PRECISION);

    std::cout << count << std::endl;
}


int main()
{
//    CMatrix<double> a(reinterpret_cast<double *>(an), VEC_N, VEC_N);
//    std::vector<double> b(bn, bn + VEC_N);
//    std::vector<double> x(VEC_N);
    double x[VEC_N] = { 0, 0, 0 };
    //jacobi_eqn(an, bn, VEC_N, x);
    gauss_seidel_eqn(an, bn, VEC_N, x);
    for (int i = 0; i < VEC_N; i++)
    {
        std::cout << "x[" << i + 1 << "] = " << x[i] << std::endl;
    }

    return 0;
}

