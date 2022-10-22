#pragma once

#include <set>
#include <string>
#include "point.h"
#include "shape.h"

class BoundingBox
{
private:
    Point *_max;
    Point *_min;

public:
    BoundingBox(std::set<const Point *> points)
    {
        _max = calMaximumPoint(points);
        _min = calMinimumPoint(points);
    }

    Point *calMaximumPoint(const std::set<const Point *> points)
    {
        if (points.size() <= 0)
            throw std::string("Cannot initialize BoundingBox with an empty set of points.");

        std::set<const Point *>::iterator it = points.begin();
        double maxPointX = (*it)->x(), maxPointY = (*it)->y();
        for (it++; it != points.end(); it++)
        {
            double x = (*it)->x(), y = (*it)->y();
            maxPointX = (x > maxPointX) ? x : maxPointX;
            maxPointY = (y > maxPointY) ? y : maxPointY;
        }

        return new Point(maxPointX, maxPointY);
    }

    Point *calMinimumPoint(const std::set<const Point *> points)
    {
        if (points.size() <= 0)
            throw std::string("Cannot initialize BoundingBox with an empty set of points.");

        std::set<const Point *>::iterator it = points.begin();
        double minPointX = (*it)->x(), minPointY = (*it)->y();
        for (it++; it != points.end(); it++)
        {
            double x = (*it)->x(), y = (*it)->y();
            minPointX = (x < minPointX) ? x : minPointX;
            minPointY = (y < minPointY) ? y : minPointY;
        }

        return new Point(minPointX, minPointY);
    }

    const Point *max()
    {
        return _max;
    }

    const Point *min()
    {
        return _min;
    }

    bool isPointInBox(Point *point)
    {
        if (point->x() > _max->x() || point->x() < _min->x())
            return false;
        if (point->y() > _max->y() || point->y() < _min->y())
            return false;
        return true;
    }

    bool collide(BoundingBox *box)
    {
        Point *leftBottom = new Point(_min->x(), _min->y());
        Point *leftTop = new Point(_min->x(), _max->y());
        Point *rightBottom = new Point(_max->x(), _min->y());
        Point *rightTop = new Point(_max->x(), _max->y());

        Point *boundaries[] = {leftBottom, leftTop, rightBottom, rightTop};
        for (int index = 0; index < 4; index++)
        {
            Point *point = boundaries[index];
            if (box->isPointInBox(point))
                return true;
        }

        return false;
    }
};
