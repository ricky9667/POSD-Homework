#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/rectangle.h"

TEST(RectangleTest, test)
{
    Rectangle *rectangle = new Rectangle(
        new TwoDimensionalVector(new Point(-2, 1), new Point(1.5, 0.47)),
        new TwoDimensionalVector(new Point(-2, 1), new Point(-1.47, 4.5))
    );
}
