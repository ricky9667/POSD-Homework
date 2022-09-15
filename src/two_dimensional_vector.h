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

    double dot(TwoDimensionalVector *vector)
    {
        double diffX1 = _a->x() - _b->x();
        double diffY1 = _a->y() - _b->y();
        double diffX2 = vector->a()->x() - vector->b()->x();
        double diffY2 = vector->a()->y() - vector->b()->y();
        return diffX1 * diffX2 + diffY1 * diffY2;
    }

    double cross(TwoDimensionalVector *vector)
    {
        double diffX1 = _a->x() - _b->x();
        double diffY1 = _a->y() - _b->y();
        double diffX2 = vector->a()->x() - vector->b()->x();
        double diffY2 = vector->a()->y() - vector->b()->y();
        return diffX1 * diffY2 - diffY1 * diffX2;
    }

    std::string info() 
    {
        return "Vector (" + _a->info() + ", " + _b->info() + ")";
    }
};
