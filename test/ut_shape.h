#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/shape.h"
#include "../src/triangle.h"
#include "../src/rectangle.h"
#include "../src/circle.h"

TEST(ShapeTest, ShapeAreaCalculationShouldBeCorrect)
{
    Shape *triangle = new Triangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(3, 0)),
        new TwoDimensionalVector(new Point(3, 4), new Point(3, 0)));
    ASSERT_NEAR(6, triangle->area(), 0.001);

    Shape *rectangle = new Rectangle(
        new TwoDimensionalVector(new Point(-2, 1), new Point(1.5, 0.47)),
        new TwoDimensionalVector(new Point(-2, 1), new Point(-1.47, 4.5)));
    ASSERT_NEAR(12.5309, rectangle->area(), 0.001);

    Shape *circle = new Circle(
        new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728)));
    ASSERT_NEAR(1.6027, circle->area(), 0.001);
}

TEST(ShapeTest, ShapePerimeterCalculationShouldBeCorrect)
{
    Shape *triangle = new Triangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(3, 0)),
        new TwoDimensionalVector(new Point(3, 4), new Point(3, 0)));
    ASSERT_NEAR(12, triangle->perimeter(), 0.001);

    Shape *rectangle = new Rectangle(
        new TwoDimensionalVector(new Point(-2, 1), new Point(1.5, 0.47)),
        new TwoDimensionalVector(new Point(-2, 1), new Point(-1.47, 4.5)));
    ASSERT_NEAR(14.1596, rectangle->perimeter(), 0.001);

    Shape *circle = new Circle(
        new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728)));
    ASSERT_NEAR(4.4877, circle->perimeter(), 0.001);
}

TEST(ShapeTest, ShapeInfoShouldWorkExpectedly)
{
    Shape *triangle = new Triangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(3, 0)),
        new TwoDimensionalVector(new Point(3, 4), new Point(3, 0)));
    std::string expectedTriangleInfo = "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))";
    ASSERT_EQ(expectedTriangleInfo, triangle->info());

    Shape *rectangle = new Rectangle(
        new TwoDimensionalVector(new Point(-2, 1), new Point(1.5, 0.47)),
        new TwoDimensionalVector(new Point(-2, 1), new Point(-1.47, 4.5)));
    std::string expectedRectangleInfo = "Rectangle (Vector ((-2.00, 1.00), (1.50, 0.47)), Vector ((-2.00, 1.00), (-1.47, 4.50)))";
    ASSERT_EQ(expectedRectangleInfo, rectangle->info());

    Shape *circle = new Circle(
        new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728)));
    std::string expectedCircleInfo = "Circle (Vector ((-4.28, 0.26), (-4.83, 0.73)))";
    ASSERT_EQ(expectedCircleInfo, circle->info());
}
