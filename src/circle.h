#pragma once

#include <string>
#include <cmath>
#include "point.h"
#include "two_dimensional_vector.h"
#include "shape.h"
#include "iterator/iterator.h"
#include "iterator/factory/iterator_factory.h"
#include "visitor/shape_visitor.h"

class Circle : public Shape
{
private:
    TwoDimensionalVector *_radiusVec;
    std::set<const Point *> _points;

    void _calculatePoints()
    {
        double centerX = _radiusVec->a()->x(), centerY = _radiusVec->a()->y();
        double length = _radiusVec->length();
        _points.insert(new Point(centerX + length, centerY + length));
        _points.insert(new Point(centerX - length, centerY - length));
    }

public:
    Circle(TwoDimensionalVector *radiusVec)
    {
        _radiusVec = radiusVec;
        _calculatePoints();
    }

    double radius()
    {
        return _radiusVec->length();
    }

    double area() override
    {
        double radius = _radiusVec->length();
        return M_PI * radius * radius;
    }

    double perimeter() override
    {
        return 2.0 * M_PI * _radiusVec->length();
    }

    std::string info() override
    {
        return "Circle (" + _radiusVec->info() + ")";
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
        visitor->visitCircle(this);
    }
};
