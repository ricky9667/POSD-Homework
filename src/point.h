#pragma once

#include <sstream>
#include <iomanip>

class Point
{
private:
    const double _x;
    const double _y;

    const std::string doubleToString(double value, int precision) const
    {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(precision) << value;
        return stream.str();
    }

public:
    Point(const double x, const double y) : _x{x}, _y{y} {}

    const bool operator==(const Point &other) const
    {
        return doubleToString(_x, 2) == doubleToString(other.x(), 2) && doubleToString(_y, 2) == doubleToString(other.y(), 2);
    }

    const double x() const
    {
        return _x;
    }

    const double y() const
    {
        return _y;
    }

    const std::string info() const
    {
        std::string strX = doubleToString(_x, 2);
        std::string strY = doubleToString(_y, 2);
        return "(" + strX + ", " + strY + ")";
    }
};
