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

    double getX()
    {
        return _x;
    }

    double getY()
    {
        return _y;
    }
};
