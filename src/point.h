class Point
{
private:
    double _x;
    double _y;

public:
    Point(double x, double y)
    {
        _x = x;
        _y = y;
    }

    bool operator==(Point other)
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
};
