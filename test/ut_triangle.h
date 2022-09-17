#include <string>
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/triangle.h"

TEST(TriangleTest, testTriangleArea)
{
    Triangle *triangle = new Triangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(3, 0)),
        new TwoDimensionalVector(new Point(3, 4), new Point(3, 0))
    );

    ASSERT_NEAR(6, triangle->area(), 0.001);
}

TEST(TriangleTest, testTrianglePerimeter)
{
    Triangle *triangle = new Triangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(3, 0)),
        new TwoDimensionalVector(new Point(3, 4), new Point(3, 0))
    );

    ASSERT_NEAR(12, triangle->perimeter(), 0.001);
}

TEST(TriangleTest, testTriangleInfo)
{
    Triangle *triangle = new Triangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(3, 0)),
        new TwoDimensionalVector(new Point(3, 4), new Point(3, 0))
    );

    std::string expectedInfo = "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))";
    ASSERT_EQ(expectedInfo, triangle->info());
}

TEST(TriangleTest, testTriangleParallel)
{
    TwoDimensionalVector *a = new TwoDimensionalVector(new Point(0, 0), new Point(3, 1));
    TwoDimensionalVector *b = new TwoDimensionalVector(new Point(0, 0), new Point(6, 2));
    
    ASSERT_ANY_THROW(new Triangle(a, b));
}

