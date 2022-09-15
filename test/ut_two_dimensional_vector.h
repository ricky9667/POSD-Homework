#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

TEST(TwoDimensionalVectorTest, testVectorGetters)
{
    Point *a = new Point(-8.42, 3.42);
    Point *b = new Point(-3.38, 4.3);
    TwoDimensionalVector vector(a, b);

    ASSERT_EQ(a, vector.a());
    ASSERT_EQ(b, vector.b());
}

