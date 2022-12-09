#include "../../src/shape.h"
#include "../../src/rectangle.h"
#include "../../src/circle.h"
#include "../../src/triangle.h"
#include "../../src/compound_shape.h"
#include "../../src/graphics/sdl_adapter.h"
#include "../../src/graphics/canvas.h"
#include "mock_sdl_renderer.h"

class SDLAdapterTest : public ::testing::Test
{
protected:
    MockSDLRenderer *mockSDLRenderer;

    void SetUp() override
    {
        mockSDLRenderer = new MockSDLRenderer();
    }

    void TearDown() override
    {
        delete mockSDLRenderer;
    }
};

TEST_F(SDLAdapterTest, initShouldBeCalledWhenAdapterIsInitialized)
{
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    // ...
    delete canvas;
}

TEST_F(SDLAdapterTest, initCalledArgsShouldBeCorrect)
{
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    // ...
    delete canvas;
}

TEST_F(SDLAdapterTest, widthAndHeightShouldBeGreaterThanZero)
{

    // ...
}

TEST_F(SDLAdapterTest, renderDrawCircleCalledArgsShouldBeCorrect)
{
    // ...
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    // ...
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForNonRotatedRect)
{

    // ...
    Canvas *canvas = new SDLAdapter(600, 600, mockSDLRenderer);
    // ...
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
    // ...
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForRotatedRect1)
{
    // ...
    Canvas *canvas = new SDLAdapter(600, 600, mockSDLRenderer);
    // ...
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
    // ...
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForRotatedRect2)
{
    // ...
    Canvas *canvas = new SDLAdapter(1, 1, mockSDLRenderer);
    // ...
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
    // ...
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForRotatedRect3)
{
    // ...
    Canvas *canvas = new SDLAdapter(123, 654, mockSDLRenderer);
    // ...
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
    // ...
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForTriangle1)
{
    // ...
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    // ...
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
    // ...
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForTriangle2)
{
    // ...
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    // ...
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
    // ...
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderPresentShouldBeCalledWhenAdapterIsDisplayed)
{
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    // ...
    delete canvas;
}
