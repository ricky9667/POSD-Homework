#include <string>
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/rectangle.h"

TEST(RectangleTest, testRectangleGetters)
{
    TwoDimensionalVector *lengthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(1.5, 0.47));
    TwoDimensionalVector *widthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(-1.47, 4.5));
    Rectangle *rectangle = new Rectangle(lengthVector, widthVector);

    ASSERT_EQ(lengthVector->length(), rectangle->length());
    ASSERT_EQ(widthVector->length(), rectangle->width());
}

TEST(RectangleTest, testRectangleArea)
{
    TwoDimensionalVector *lengthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(1.5, 0.47));
    TwoDimensionalVector *widthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(-1.47, 4.5));
    Rectangle *rectangle = new Rectangle(lengthVector, widthVector);

    ASSERT_NEAR(12.5309, rectangle->area(), 0.001);
}

TEST(RectangleTest, testRectanglePerimeter)
{
    TwoDimensionalVector *lengthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(1.5, 0.47));
    TwoDimensionalVector *widthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(-1.47, 4.5));
    Rectangle *rectangle = new Rectangle(lengthVector, widthVector);

    ASSERT_NEAR(14.1596, rectangle->perimeter(), 0.001);
}

TEST(RectangleTest, testRectangleInfo)
{
    TwoDimensionalVector *lengthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(1.5, 0.47));
    TwoDimensionalVector *widthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(-1.47, 4.5));
    Rectangle *rectangle = new Rectangle(lengthVector, widthVector);

    std::string expectedInfo = "Rectangle (Vector ((-2.00, 1.00), (1.50, 0.47)), Vector ((-2.00, 1.00), (-1.47, 4.50)))";
    ASSERT_EQ(expectedInfo, rectangle->info());
}

TEST(RectangleTest, testRectangleNotOrthogonal)
{
    TwoDimensionalVector *lengthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(-2, 5));
    TwoDimensionalVector *widthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(-7, 2));

    ASSERT_ANY_THROW(new Rectangle(lengthVector, widthVector));
}
