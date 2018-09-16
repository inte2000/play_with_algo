// integration.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>

double trapezium(std::function<double(double)> func, double a, double b, int n)
{
    double step = (b - a) / n;
    double sum = (func(a) + func(b)) / 2.0;

    for (int j = 1; j < n; j++)
    {
        double xj = a + j * step;
        sum = sum + func(xj);
    }

    sum *= step;

    return sum;
}

double vs_trapezium(std::function<double(double)> func, double a, double b, double eps)
{
    int n = 1;   //初始分割一个大梯形
    double t1 = (b - a) * (func(a) + func(b)) / 2.0; //计算初始梯形的面积
    double diff = eps + 1.0;
    do
    {
        n = 2 * n;    //梯形分割加倍
        double t = trapezium(func, a, b, n);
        diff = std::fabs(t1 - t);      //计算两次迭代的结果差值
        t1 = t;
    } while (diff >= eps);

    return t1;
}

double simpson(std::function<double(double)> func, double a, double b, int n)
{
    double s1, s2;
    int i;

    double step = (b - a) / n;
    s1 = s2 = 0;
    for (i = 1; i < n; i++)
    {
        s2 += func(a + step * i);   //xi求和
    }
    for (i = 1; i <= n; i++)
    {
        s1 += func(a + step * i - step / 2);  //（xi - step/2） 求和
    }

    double s = step * (func(a) + func(b) + 4 * s1 + 2 * s2) / 6.0;

    return s;
}

double vs_simpson(std::function<double(double)> func, double a, double b, double eps)
{
    int n = 1;   //初始分割一个大梯形
    double s1 = (b - a) * (func(a) + func(b) + 4 * func((a + b) / 2.0)) / 6.0; //计算初始梯形的面积
    double diff = eps + 1.0;
    do
    {
        n = 2 * n;    //梯形分割加倍
        double t = simpson(func, a, b, n);
        diff = std::fabs(s1 - t);      //计算两次迭代的结果差值
        s1 = t;
    } while (diff >= eps);

    return s1;
}

int main()
{
    auto func1 = [](double x)-> double { return sin(x)/x; };
    double result = trapezium(func1, 0.000000001, 1.0, 10000);
    std::cout << "trapezium value (10000 steps) " << std::setprecision(12) << result << std::endl;

    result = vs_trapezium(func1, 0.000000001, 1.0, 0.000000001);
    std::cout << "vs_trapezium value (EPS = 0.000000001) " << std::setprecision(12) << result << std::endl;

    result = simpson(func1, 0.000000001, 1.0, 10000);
    std::cout << "simpson value (10000 steps) " << std::setprecision(12) << result << std::endl;

    result = vs_simpson(func1, 0.000000001, 1.0, 0.000000001);
    std::cout << "vs_simpson value (EPS = 0.000000001) " << std::setprecision(12) << result << std::endl;
    return 0;
}

