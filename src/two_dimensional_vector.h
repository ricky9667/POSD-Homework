#pragma once

#include <cmath>
#include "point.h"

class TwoDimensionalVector
{
private:
    const Point _a;
    const Point _b;

public:
    TwoDimensionalVector(const Point a, const Point b) : _a{a}, _b{b} {}

    const Point a() const
    {
        return _a;
    }

    const Point b() const
    {
        return _b;
    }

    const bool isConnected(TwoDimensionalVector other) const
    {
        return _a == other.a() || _a == other.b() || _b == other.a() || _b == other.b();
    }

    const double length() const
    {
        double diffX = _a.x() - _b.x();
        double diffY = _a.y() - _b.y();
        return sqrt(diffX * diffX + diffY * diffY);
    }

    const double dot(TwoDimensionalVector vector) const
    {
        double diffX1 = _a.x() - _b.x();
        double diffY1 = _a.y() - _b.y();
        double diffX2 = vector.a().x() - vector.b().x();
        double diffY2 = vector.a().y() - vector.b().y();
        return diffX1 * diffX2 + diffY1 * diffY2;
    }

    const double cross(TwoDimensionalVector vector) const
    {
        double diffX1 = _a.x() - _b.x();
        double diffY1 = _a.y() - _b.y();
        double diffX2 = vector.a().x() - vector.b().x();
        double diffY2 = vector.a().y() - vector.b().y();
        return diffX1 * diffY2 - diffY1 * diffX2;
    }

    const std::string info() const
    {
        return "Vector (" + _a.info() + ", " + _b.info() + ")";
    }
};
