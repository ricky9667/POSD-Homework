#include <iostream>
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

    ASSERT_TRUE(mockSDLRenderer->isInitCalled());

    delete canvas;
}

TEST_F(SDLAdapterTest, initCalledArgsShouldBeCorrect)
{
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);

    ASSERT_EQ(1024, mockSDLRenderer->initWidth());
    ASSERT_EQ(768, mockSDLRenderer->initHeight());

    delete canvas;
}

TEST_F(SDLAdapterTest, widthAndHeightShouldBeGreaterThanZero)
{
    ASSERT_NO_THROW(SDLAdapter(1024, 768, mockSDLRenderer));
    ASSERT_ANY_THROW(SDLAdapter(-1, 768, mockSDLRenderer));
    ASSERT_ANY_THROW(SDLAdapter(1024, -1, mockSDLRenderer));
    ASSERT_ANY_THROW(SDLAdapter(-1, -1, mockSDLRenderer));
}

TEST_F(SDLAdapterTest, renderDrawCircleCalledArgsShouldBeCorrect)
{
    Point center(5, 2);
    Point edge(8, 2);
    TwoDimensionalVector vector(center, edge);
    Circle *circle = new Circle(vector);
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);

    canvas->drawCircle(circle);
    const double *calledPoints = mockSDLRenderer->renderDrawCircleCalledArgs();
    ASSERT_NEAR(5, calledPoints[0], 0.001);
    ASSERT_NEAR(2, calledPoints[1], 0.001);
    ASSERT_NEAR(3, calledPoints[2], 0.001);

    delete circle;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForNonRotatedRect)
{
    Point a(3, 7);
    Point b(5, 7);
    Point c(3, 11);
    TwoDimensionalVector widthVector(a, b);
    TwoDimensionalVector lengthVector(a, c);
    Rectangle *rectangle = new Rectangle(lengthVector, widthVector);

    Canvas *canvas = new SDLAdapter(600, 600, mockSDLRenderer);
    canvas->drawRectangle(rectangle);
    std::set<Point> points = rectangle->getPoints();
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();

    ASSERT_EQ(8, mockSDLRenderer->renderDrawLinesCalledSize());
    int index = 0;
    for (auto point : points)
    {
        ASSERT_NEAR(calledPoints[index], point.x(), 0.001);
        ASSERT_NEAR(calledPoints[index + 1], point.y(), 0.001);
        index += 2;
    }

    delete rectangle;
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForRotatedRect)
{
    Point a(3, 3);
    Point b(5, 5);
    Point c(5, 1);
    TwoDimensionalVector widthVector(a, b);
    TwoDimensionalVector lengthVector(a, c);
    Rectangle *rectangle = new Rectangle(lengthVector, widthVector);

    Canvas *canvas = new SDLAdapter(600, 600, mockSDLRenderer);
    canvas->drawRectangle(rectangle);
    std::set<Point> points = rectangle->getPoints();
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();

    ASSERT_EQ(8, mockSDLRenderer->renderDrawLinesCalledSize());
    int index = 0;
    for (auto point : points)
    {
        ASSERT_NEAR(calledPoints[index], point.x(), 0.001);
        ASSERT_NEAR(calledPoints[index + 1], point.y(), 0.001);
        index += 2;
    }

    delete rectangle;
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForTriangle)
{
    Point a(3, 3);
    Point b(3, 10);
    Point c(6, 2);
    TwoDimensionalVector v1(a, b);
    TwoDimensionalVector v2(a, c);
    Triangle *triangle = new Triangle(v1, v2);

    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
    canvas->drawTriangle(triangle);
    std::set<Point> points = triangle->getPoints();
    const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();

    ASSERT_EQ(6, mockSDLRenderer->renderDrawLinesCalledSize());
    int index = 0;
    for (auto point : points)
    {
        ASSERT_NEAR(calledPoints[index], point.x(), 0.001);
        ASSERT_NEAR(calledPoints[index + 1], point.y(), 0.001);
        index += 2;
    }

    delete triangle;
    delete[] calledPoints;
    delete canvas;
}

TEST_F(SDLAdapterTest, renderPresentShouldBeCalledWhenAdapterIsDisplayed)
{
    Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);

    ASSERT_FALSE(mockSDLRenderer->isRenderPresentCalled());
    canvas->display();
    ASSERT_TRUE(mockSDLRenderer->isRenderPresentCalled());

    delete canvas;
}
