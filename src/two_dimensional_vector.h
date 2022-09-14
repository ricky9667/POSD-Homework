#pragma once

#include "point.h"

class TwoDimensionalVector
{
private:
    Point *_a;
    Point *_b;

public:
    TwoDimensionalVector(Point *a, Point *b) {}
    ~TwoDimensionalVector() {}

    Point *a() {}

    Point *b() {}

    double length() {}

    double dot(TwoDimensionalVector *vec) {}

    double cross(TwoDimensionalVector *vec) {}

    std::string info() {}
};
