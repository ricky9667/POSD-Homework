#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/triangle.h"

TEST(TriangleTest, test)
{
    Triangle *triangle = new Triangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(3, 0)),
        new TwoDimensionalVector(new Point(3, 4), new Point(3, 0))
    );
}
