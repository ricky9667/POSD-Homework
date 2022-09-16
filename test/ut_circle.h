#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/circle.h"

TEST(CircleTest, testCircleRadius)
{
    TwoDimensionalVector *vector = new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728));
    Circle *circle = new Circle(vector);

    ASSERT_NEAR(vector->length(), circle->radius(), 0.001);
}

TEST(CircleTest, testCircleArea)
{
    TwoDimensionalVector *vector = new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728));
    Circle *circle = new Circle(vector);

    ASSERT_NEAR(1.6027, circle->area(), 0.001);
}

TEST(CircleTest, testCirclePerimeter)
{
    TwoDimensionalVector *vector = new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728));
    Circle *circle = new Circle(vector);

    ASSERT_NEAR(4.4877, circle->perimeter(), 0.001);
}

TEST(CircleTest, testCircleInfo)
{
    TwoDimensionalVector *vector = new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728));
    Circle *circle = new Circle(vector);

    std::string expectedInfo = "Circle (Vector ((-4.28, 0.26), (-4.83, 0.73)))";
    ASSERT_EQ(expectedInfo, circle->info());
}
