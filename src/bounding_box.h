#pragma once

#include <set>
#include <string>
#include "point.h"
#include "shape.h"
#include "two_dimensional_vector.h"

class BoundingBox
{
private:
    Point _max;
    Point _min;

public:
    BoundingBox(std::set<Point> points) : _max{Point(0, 0)}, _min{Point(0, 0)}
    {
        _max = calMaximumPoint(points);
        _min = calMinimumPoint(points);
    }

    Point calMaximumPoint(const std::set<Point> points)
    {
        if (points.size() <= 0)
            throw std::string("Cannot initialize BoundingBox with an empty set of points.");

        std::set<Point>::iterator it = points.begin();
        double maxPointX = (*it).x(), maxPointY = (*it).y();
        for (it++; it != points.end(); it++)
        {
            double x = (*it).x(), y = (*it).y();
            maxPointX = (x > maxPointX) ? x : maxPointX;
            maxPointY = (y > maxPointY) ? y : maxPointY;
        }

        return Point(maxPointX, maxPointY);
    }

    Point calMinimumPoint(const std::set<Point> points)
    {
        if (points.size() <= 0)
            throw std::string("Cannot initialize BoundingBox with an empty set of points.");

        std::set<Point>::iterator it = points.begin();
        double minPointX = (*it).x(), minPointY = (*it).y();
        for (it++; it != points.end(); it++)
        {
            double x = (*it).x(), y = (*it).y();
            minPointX = (x < minPointX) ? x : minPointX;
            minPointY = (y < minPointY) ? y : minPointY;
        }

        return Point(minPointX, minPointY);
    }

    const Point max()
    {
        return _max;
    }

    const Point min()
    {
        return _min;
    }

    bool collide(BoundingBox *box)
    {
        return !(_max.x() < box->min().x() || _min.x() > box->max().x() || _max.y() < box->min().y() || _min.y() > box->max().y());
    }

    double distance(BoundingBox *box)
    {
        TwoDimensionalVector maxPointVector = TwoDimensionalVector(_max, box->max());
        TwoDimensionalVector minPointVector = TwoDimensionalVector(_min, box->min());
        return maxPointVector.length() + minPointVector.length();
    }
};
