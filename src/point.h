#pragma once

#include <sstream>

class Point
{
private:
    double _x;
    double _y;

    std::string doubleToString(double value, int precision)
    {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(precision) << value;
        return stream.str();
    }

public:
    Point(double x, double y)
    {
        _x = x;
        _y = y;
    }

    ~Point() {}

    bool operator==(Point &other)
    {
        return _x == other.x() && _y == other.y();
    }

    double x()
    {
        return _x;
    }

    double y()
    {
        return _y;
    }

    std::string info() 
    {
        std::string strX = doubleToString(_x, 2);
        std::string strY = doubleToString(_y, 2);
        return "(" + strX + ", " + strY + ")";
    }
};
