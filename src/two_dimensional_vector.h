#pragma once

#include "point.h"

class TwoDimensionalVector
{
private:
    Point *_a;
    Point *_b;

public:
    TwoDimensionalVector(Point *a, Point *b) 
    {
        _a = a;
        _b = b;
    }

    ~TwoDimensionalVector() {}

    Point *a() 
    {
        return _a;
    }

    Point *b() 
    {
        return _b;
    }

    double length() {}

    double dot(TwoDimensionalVector *vec) {}

    double cross(TwoDimensionalVector *vec) {}

    std::string info() {}
};
