#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include "two_dimensional_vector.h"
#include "shape.h"
#include "iterator/iterator.h"

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

    double area() const override
    {
        double radius = _radiusVec->length();
        return M_PI * radius * radius;
    }

    double perimeter() const override
    {
        return 2.0 * M_PI * _radiusVec->length();
    }

    std::string info() override
    {
        return "Circle (" + _radiusVec->info() + ")";
    }

    Iterator *createDFSIterator() override {}

    Iterator *createBFSIterator() override {}

    void addShape(Shape *shape) override {}

    void deleteShape(Shape *shape) override {}
};

