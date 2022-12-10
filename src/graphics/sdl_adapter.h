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
        const Point *center = cir->center();
        _sdl->renderDrawCircle(center->x(), center->y(), cir->radius());
    }

    void drawTriangle(Triangle *tri) override
    {
        std::vector<double> pointValues = tri->getPointValues();
        if (pointValues.size() != 6)
            throw std::string("Size of points is not correct in drawTriangle.");

        _sdl->renderDrawLines(&pointValues[0], 6);
    }

    void drawRectangle(Rectangle *rect) override
    {
        std::vector<double> pointValues = rect->getPointValues();
        if (pointValues.size() != 8)
            throw std::string("Size of points is not correct in drawRectangle.");

        _sdl->renderDrawLines(&pointValues[0], 8);
    }

    void display() override
    {
        _sdl->renderPresent();
    }
};
