#pragma once

#include <string>
#include <cmath>
#include "shape.h"
#include "two_dimensional_vector.h"

class Triangle : public Shape
{
private:
    TwoDimensionalVector *_v1;
    TwoDimensionalVector *_v2;

public:
    Triangle(TwoDimensionalVector *v1, TwoDimensionalVector *v2)
    {
        if (v1->cross(v2) == 0)
            throw std::string("Cannot initialize triangle with parallel vectors.");
        
        _v1 = v1;
        _v2 = v2;
    }

    double area() override
    {
        return _v1->length() * _v2->length() / 2.0;
    }

    double perimeter() override
    {
        double height = _v1->length();
        double width = _v2->length();
        double side = sqrt(height * height + width * width);
        return height + width + side;
    }

    std::string info() override
    {
        return "Triangle (" + _v1->info() + ", " + _v2->info() + ")";
    }
};

