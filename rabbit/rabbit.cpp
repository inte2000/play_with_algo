// rabbit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <utility>

const int LOOP_LIMIT = 1000;

std::pair<bool, double> cl_root(double a, double eps)
{
    double xi = a / 2.0;
    double xt;
    int count = 0;
    do
    {
        xt = xi;
        xi = (xt + (a / xt)) / 2.0;
        count++;
        if (count >= LOOP_LIMIT)
        {
            return {false, xi};
        }
    } while (std::fabs(xi - xt) > eps);

    return { true, xi };
}


int main()
{
    int a = 2;

    std::pair<bool, double> rtn = cl_root(a, 0.0000001);

    if (rtn.first)
    {
        std::cout << "root of " << a << " is " << rtn.second << std::endl;
    }
    else
    {
        std::cout << "fail to get the root of " << a << std::endl;
    }

    return 0;
}

