// equation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>

const double PRECISION = 0.000000001;
const double INVALID_VALUE = 1800000.0;
const int MAX_RUN_LOOP = 20;

typedef double (*FunctionPtr)(double);

double binFunc(double x)
{
    return (2.0*x*x + 3.2*x - 1.8);
}

double DichotomyEquation(double a, double b, FunctionPtr f)
{
    double mid = (a + b) / 2.0;
    while((b - a) > PRECISION)
    {
        if(f(a) * f(mid) < 0.0)
        {
            b = mid;
        }
        else
        {
            a = mid;
        }
        mid = (a + b) / 2.0;
    }

    return mid;
}

double CalcDerivative(FunctionPtr f, double x)
{
    return (f(x + 0.000005) - f(x - 0.000005)) / 0.00001;
}



double NewtonRaphson(FunctionPtr f, double x0) 
{
    double x = INVALID_VALUE;
    int count = 0;
    do
    {
        double x1 = x0 - f(x0) / CalcDerivative(f, x0); //应用迭代公式
        if (fabs(x1 - x0) < PRECISION)
        {
            x = x1;
            break;
        }
        x0 = x1;  //更新迭代变量
        count++;
    } while (count < MAX_RUN_LOOP);

    return x;
}

int main(int argc, char* argv[])
{
    double s = binFunc(-0.8);
    double t = binFunc(8);
    double k = binFunc(0.44096736423671234);
    double m = binFunc(-2.040967365);
                      

    double x = DichotomyEquation(-0.8, 12.0, binFunc);
    double y = NewtonRaphson(binFunc, 8.0);
    double z = NewtonRaphson(binFunc, -8.0);
	return 0;
}

