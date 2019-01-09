// sat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>

const double RANGE_MAX = 10000.0;
const double RANGE_MIN = -10000.0;

class Point
{
public:
    double x;
    double y;
};

class Vector
{
public:
    Vector(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    Vector(const Point& pt)
    {
        this->x = pt.x;
        this->y = pt.y;
    }
    double DotProduct(const Vector& v) const
    {
        return (x * v.x + y * v.y);
    }
    Vector GetNormal()
    {
        Vector v = GetPerpendicular();
        v.Normalize(); 
            
        return v;
    }
    static Vector MakeEdge(const Point& p1, const Point& p2)
    {
        Vector u(p1); //转化成从(0, 0)起始的向量
        Vector v(p2); //转化成从(0, 0)起始的向量
        return u.Subtarct(v); //做向量的减法

        //上述代码只是为了介绍逻辑原理，其结果相当于下面一行代码
        //return Vector(p1.x - p2.x, p1.y - p2.y);
    }

protected:
    Vector Subtarct(const Vector& v) const
    {
        return Vector(x - v.x, y - v.y);
    }

    Vector GetPerpendicular() const
    {
        return Vector(y, -x);
    }
    void Normalize()
    {
        double dist = std::sqrt(x*x + y*y);
        if (dist != 0.0)
        {
            x = x / dist;
            y = y / dist;
        }
    }

private:
    double x;
    double y;
};

class Projection
{
public:
    Projection(double min, double max)
    {
        this->min = min;
        this->max = max;
    }

    bool IsOverlap(const Projection& p) const
    {
        return ((max > p.min) && (p.max > min));
    }

private:
    double min;
    double max;
};

class Polygon
{
public:
    Polygon(std::initializer_list<Point> pts)
    {
        for (auto it = pts.begin(); it != pts.end(); it++)
        {
            vertex.push_back(*it);
        }
    }

    void GetAxes(std::vector<Vector>& axes) const
    {
        for (std::size_t i = 0; i < vertex.size(); i++)
        {
/*
            Vector p1 = Vector(vertex[i]);
            Vector p2 = Vector(vertex[(i + 1) % vertex.size()]);
            Vector edge = p1.MakeEdge(p2);
*/
            Point p1 = vertex[i];
            Point p2 = vertex[(i + 1) % vertex.size()];
            Vector edge = Vector::MakeEdge(p1, p2);
            axes.push_back(edge.GetNormal());
        }
    }

    Projection GetProject(const Vector &axes) const
    {
        double min = RANGE_MAX;
        double max = RANGE_MIN;
        for (const auto& i : vertex)
        {
            Vector p = Vector(i);
            double prj = p.DotProduct(axes);
            if (prj < min)
                min = prj;

            if (prj > max)
                max = prj;
        }
        return Projection(min, max);
    }

private:
    std::vector<Point> vertex;
};

bool CollisionTest(const Polygon& pa, const Polygon& pb)
{
    std::vector<Vector> axes_a, axes_b;
    pa.GetAxes(axes_a);
    for (auto& ax : axes_a)
    {
        Projection pj1 = pa.GetProject(ax);
        Projection pj2 = pb.GetProject(ax);
        if (!pj1.IsOverlap(pj2)) /*只要有一条轴上的投影没有重叠，就说明不相交*/
        {
            return false;
        }
    }

    pb.GetAxes(axes_b);
    for (auto& ax : axes_b)
    {
        Projection pj1 = pa.GetProject(ax);
        Projection pj2 = pb.GetProject(ax);
        if (!pj1.IsOverlap(pj2)) /*只要有一条轴上的投影没有重叠，就说明不相交*/
        {
            return false;
        }
    }

    return true;
}

int main()
{
    Polygon shape1 = { {3.49, 2.34}, {3.56, 6.58}, { 8.42, 4.47 } };
    Polygon shape2 = { {10.84, 6.46}, {12.39, 3.92}, {10.86, 1.67},{7.70, 3.27} };
    Polygon shape3 = { { 3.49, 2.34 },{ 3.56, 6.58 }, { 9.31, 4.02 } };
    
    Polygon shape4 = { {2.41, 7.20}, {7.46, 7.65}, {8.23, 4.00}, {5.16, 2.20}, {1.90, 3.68} };
    Polygon shape5 = { {2.41, 7.20}, {7.46, 7.65}, {9.42, 3.94}, {5.16, 2.20}, {1.90, 3.68} };
    Polygon shape6 = { {10.08, 5.69}, {13.89, 7.86}, {16.17, 2.70}, {8.81, 1.01}, {8.52, 2.80} };

    bool result = CollisionTest(shape1, shape2);
    assert(result == false);

    result = CollisionTest(shape3, shape2);
    assert(result == true);

    result = CollisionTest(shape4, shape6);
    assert(result == false);

    result = CollisionTest(shape5, shape6);
    assert(result == true);
    
    return 0;
}

