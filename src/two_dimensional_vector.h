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

    ~TwoDimensionalVector() 
    {
        if (_a != nullptr) 
            delete[] _a;
        if (_b != nullptr)
            delete[] _b;

        _a = nullptr;
        _b = nullptr;
    }

    Point *a() 
    {
        return _a;
    }

    Point *b() 
    {
        return _b;
    }

    double length() 
    {
        double diffX = _a->x() - _b->x();
        double diffY = _a->y() - _b->y();
        return diffX * diffX + diffY * diffY;
    }

    double dot(TwoDimensionalVector *vec) {}

    double cross(TwoDimensionalVector *vec) {}

    std::string info() {}
};
