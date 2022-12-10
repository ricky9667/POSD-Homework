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
        
    }

    void drawRectangle(Rectangle *rect) override
    {
    }

    void display() override
    {
    }
};
