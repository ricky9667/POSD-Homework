#pragma once

#include <string>
#include <cmath>
#include <vector>
#include "point.h"
#include "two_dimensional_vector.h"
#include "shape.h"
#include "iterator/iterator.h"
#include "iterator/factory/iterator_factory.h"
#include "visitor/shape_visitor.h"

class Triangle : public Shape
{
private:
    TwoDimensionalVector *_v1;
    TwoDimensionalVector *_v2;
    std::set<const Point *> _points;

    const double _cos() const
    {
        return _v1->dot(_v2) / (_v1->length() * _v2->length());
    }

    const double _sin() const
    {
        return sqrt(1 - _cos() * _cos());
    }

    void _calculatePoints()
    {
        _points.insert(_v1->a());
        _points.insert(_v1->b());
        _points.insert(_v2->a());
        _points.insert(_v2->b());
    }

public:
    Triangle(TwoDimensionalVector *v1, TwoDimensionalVector *v2)
    {
        if (v1->cross(v2) == 0)
            throw std::string("Cannot initialize Triangle with parallel vectors.");

        if (!v1->isConnected(v2))
            throw std::string("Cannot initialize Triangle with disconnected vectors.");

        _v1 = v1;
        _v2 = v2;
        _calculatePoints();
    }

    double area() override
    {
        return _v1->length() * _v2->length() * _sin() / 2.0;
    }

    double perimeter() override
    {
        double height = _v1->length();
        double width = _v2->length();

        double cos = _cos();
        if (_v1->a() == _v2->b() || _v1->b() == _v2->a())
            cos = (-1) * cos;
        double side = sqrt(height * height + width * width - 2 * height * width * cos);

        return height + width + side;
    }

    std::string info() override
    {
        return "Triangle (" + _v1->info() + ", " + _v2->info() + ")";
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
        visitor->visitTriangle(this);
    }

    std::vector<double> getPointValues()
    {
        std::vector<double> pointValues;
        for (auto it : _points)
        {
            pointValues.push_back(it->x());
            pointValues.push_back(it->y());
        }
        return pointValues;
    }
};
