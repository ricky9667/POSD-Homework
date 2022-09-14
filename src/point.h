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

    bool operator==(Point &other)
    {
        return _x == other.getX() && _y == other.getY();
    }

    double getX()
    {
        return _x;
    }

    double getY()
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
