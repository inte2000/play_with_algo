// line.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

//#define DBL_MAX         1.7976931348623158e+308 /* max value */  

const double EPS = 1e-8; //定义本问题的浮点数精度范围

typedef struct
{
    double x;
    double y;
}Point;

typedef struct
{
    double k;
    std::size_t p_idx;
}Slope;

typedef struct
{
    std::size_t start_idx;
    std::size_t count;
}Slope_Rec;

bool IsEqualFloat(double v1, double v2)
{
    if (std::fabs(v1 - v2) < EPS)
        return true;

    return false;
}

double CalcSlope(const Point& p0, const Point& p1)
{
    if (IsEqualFloat(p0.x, p1.x)) //点的x坐标相等，斜率为无穷大
    {
        return DBL_MAX; //用浮点数的最大值代表无穷大，不是很严谨，但是够用
    }

    return (p1.y - p0.y) / (p1.x - p0.x);
}

bool less_slope(const Slope & s1, const Slope & s2) 
{
    return s1.k < s2.k;
}

void exchange(std::vector<Slope>& slopes, int m, int n)
{
    Slope tmp = slopes[m];
    slopes[m] = slopes[n];
    slopes[n] = tmp;
}

int partion(std::vector<Slope>& slopes, int p, int r)
{
    double x = slopes[r].k;
    int i = p;
    for (int j = p; j < r; j++)
    {
        if (slopes[j].k < x)
        {
            if (i != j)
            {
                exchange(slopes, i, j);
            }
            i++;
        }
    }
    exchange(slopes, i, r);
    return i;
}

void quick_sort(std::vector<Slope>& slopes, int p, int r)
{
    if (p < r)
    {
        int mid = partion(slopes, p, r);
        quick_sort(slopes, p, mid - 1);
        quick_sort(slopes, mid + 1, r);
    }
}

Slope_Rec GetMaxPointList(const std::vector<Slope>& slopes)
{
    std::size_t max_len = 0;
    std::size_t max_start_pos = 0;

    std::size_t len = 1;
    std::size_t start_pos = 0;
    for (std::size_t s = 1; s < slopes.size(); s++)
    {
        if (!IsEqualFloat(slopes[s].k, slopes[s - 1].k))
        {
            if (len > max_len)
            {
                max_len = len;
                max_start_pos = start_pos;
            }
            start_pos = s;
            len = 1;
        }
        else
        {
            len++;
        }
    }

    return { max_start_pos, max_len };
}

void StraightLine(const std::vector<Point>& points, std::size_t n, std::vector<int>& pts)
{
    for (std::size_t i = 0; i < n; i++)
    {
        std::vector<Slope> slopes;
        for (std::size_t j = 0; j < n; j++)
        {
            if (i == j)
                continue;

            double k = CalcSlope(points[i], points[j]);
            slopes.push_back({ k, j });
        }

/*        
        std::sort(slopes.begin(), slopes.end(), 
                  [](const Slope & s1, const Slope & s2) { return s1.k < s2.k; });
*/        
        quick_sort(slopes, 0, slopes.size() - 1);

        Slope_Rec posi = GetMaxPointList(slopes);
        if (posi.count > pts.size())
        {
            pts.clear();
            pts.push_back(i); //先将原点加入
            for (std::size_t p = posi.start_idx; p < (posi.start_idx + posi.count); p++)
            {
                pts.push_back(slopes[p].p_idx);
            }
        }
    }
}

int main()
{
    std::vector<Point> points = { {1301.0, 1256.0}, {21.0, 28.0}, {6222.0, 52.0}, {-7071.0, -6264.0}, {-6406.0, -1183.0},
                                  {-912.0, -1741.0}, {39.0, 58.0}, {3.0, -2.0}, {57.0, 88.0}, {1502.0, -7726.0},
                                  {30.0, 43.0}, {-6932.0, 363.0}, {-4422.0, -5669.0}, {12.0, 13.0}, {5874.0, -9005.0},
                                  {48.0, 73.0}, {-2358.0, 129.0}, {7703.0, 1806.0}, {-3559.0, -1078.0}, {-4808.0, -2166.0} };

    std::vector<int> pts;
    StraightLine(points, points.size(), pts);


    std::cout << "Max " << pts.size() << " points on same line." << std::endl;
    for (int idx : pts)
    {
        std::cout << "index: " << idx + 1 
                  << "    (" << points[idx].x << ", " << points[idx].y << ")" << std::endl;
    }
    return 0;
}

