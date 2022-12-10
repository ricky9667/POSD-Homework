#pragma once

#include <string>
#include "point.h"
#include "two_dimensional_vector.h"
#include "shape.h"
#include "iterator/iterator.h"
#include "iterator/factory/iterator_factory.h"
#include "visitor/shape_visitor.h"

class Rectangle : public Shape
{
private:
    TwoDimensionalVector *_lengthVec;
    TwoDimensionalVector *_widthVec;
    std::set<const Point *> _points;

    void _calculatePoints()
    {
        const Point *commonPoint = _commonPoint();
        _points.insert(_lengthVec->a());
        _points.insert(_lengthVec->b());
        _points.insert(_widthVec->a());
        _points.insert(_widthVec->b());

        double x = 0, y = 0;
        for (auto point : _points)
        {
            if (point == commonPoint)
                x -= point->x(), y -= point->y();
            else
                x += point->x(), y += point->y();
        }
        _points.insert(new Point(x, y));
    }

    const Point *_commonPoint() const
    {
        if (_lengthVec->a() == _widthVec->a() || _lengthVec->a() == _widthVec->b())
            return _lengthVec->a();
        else
            return _lengthVec->b();
    }

public:
    Rectangle(TwoDimensionalVector *lengthVec, TwoDimensionalVector *widthVec)
    {
        if (lengthVec->dot(widthVec) != 0)
            throw std::string("Cannot initialize Rectangle without orthogonal vectors.");

        if (!lengthVec->isConnected(widthVec))
            throw std::string("Cannot initialized Rectangle with disconnected vectors.");

        _lengthVec = lengthVec;
        _widthVec = widthVec;
        _calculatePoints();
    }

    double length()
    {
        return _lengthVec->length();
    }

    double width()
    {
        return _widthVec->length();
    }

    double area() override
    {
        return _lengthVec->length() * _widthVec->length();
    }

    double perimeter() override
    {
        return 2 * (_lengthVec->length() + _widthVec->length());
    }

    std::string info() override
    {
        return "Rectangle (" + _lengthVec->info() + ", " + _widthVec->info() + ")";
    }

    Iterator *createIterator(IteratorFactory *factory) override
    {
        return factory->createIterator();
    }

    std::set<const Point *> getPoints() override
    {
        return _points;
    }

    void accept(ShapeVisitor *visitor) override
    {
        visitor->visitRectangle(this);
    }
};
