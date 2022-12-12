#include <iostream>
#include <algorithm>
#include <vector>
#include "../point.h"
#include "canvas.h"
#include "sdl/sdl.h"

class SDLAdapter : public Canvas
{
private:
    SDL *_sdl;

public:
    SDLAdapter(int width, int height, SDL *sdl) : _sdl{sdl}
    {
        if (width <= 0 || height <= 0)
            throw std::string("Cannot initialize with non-integer width or height.");

        _sdl->init(width, height);
    }

    void drawCircle(Circle *cir) override
    {
        const Point center = cir->center();
        _sdl->renderDrawCircle(center.x(), center.y(), cir->radius());
    }

    void drawTriangle(Triangle *tri) override
    {
        const int trianglePointsSize = 6;
        std::vector<double> pointValues = tri->getPointValues();
        if (pointValues.size() != trianglePointsSize)
            throw std::string("Size of points is not correct in drawTriangle.");

        double *pointsArray = new double[trianglePointsSize];
        std::copy(pointValues.begin(), pointValues.end(), pointsArray);
        _sdl->renderDrawLines(pointsArray, trianglePointsSize);
    }

    void drawRectangle(Rectangle *rect) override
    {
        const int rectanglePointsSize = 8;
        std::vector<double> pointValues = rect->getPointValues();
        if (pointValues.size() != rectanglePointsSize)
            throw std::string("Size of points is not correct in drawRectangle.");

        double *pointsArray = new double[rectanglePointsSize];
        std::copy(pointValues.begin(), pointValues.end(), pointsArray);

        // stupid swap
        std::swap(pointsArray[4], pointsArray[6]);
        std::swap(pointsArray[5], pointsArray[7]);

        _sdl->renderDrawLines(pointsArray, rectanglePointsSize);
    }

    void display() override
    {
        _sdl->renderPresent();
    }
};
