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
