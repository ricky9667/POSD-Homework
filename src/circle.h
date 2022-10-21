#pragma once

#include <string>
#include <cmath>
#include "two_dimensional_vector.h"
#include "shape.h"
#include "iterator/iterator.h"
#include "iterator/factory/iterator_factory.h"

class Circle : public Shape
{
private:
    TwoDimensionalVector *_radiusVec;

public:
    Circle(TwoDimensionalVector *radiusVec)
    {
        _radiusVec = radiusVec;
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
};
