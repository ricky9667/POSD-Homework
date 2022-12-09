#include "canvas.h"
#include "sdl/sdl.h"

class SDLAdapter : public Canvas
{
public:
    SDLAdapter(int height, int width, SDL *sdl)
    {
    }

    void drawCircle(Circle *cir) override
    {
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
