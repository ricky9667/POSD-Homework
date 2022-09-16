#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

TEST(TwoDimensionalVectorTest, testVectorGetters)
{
    Point *a = new Point(-8.42, 3.42);
    Point *b = new Point(-3.38, 4.3);
    TwoDimensionalVector *vector = new TwoDimensionalVector(a, b);

    ASSERT_EQ(a, vector->a());
    ASSERT_EQ(b, vector->b());
}

TEST(TwoDimensionalVectorTest, testVectorLength)
{
    Point *a = new Point(-8.42, 3.42);
    Point *b = new Point(-3.38, 4.3);
    TwoDimensionalVector *vector = new TwoDimensionalVector(a, b);

    ASSERT_NEAR(5.116, vector->length(), 0.001);
}

TEST(TwoDimensionalVectorTest, testVectorDot)
{
    Point *a = new Point(-8.42, 3.42);
    Point *b = new Point(-3.38, 4.3);
    TwoDimensionalVector *vector1 = new TwoDimensionalVector(a, b);
    Point *c = new Point(-2.48, 2.43);
    Point *d = new Point(-8.33, 3.4);
    TwoDimensionalVector *vector2 = new TwoDimensionalVector(c, d);

    ASSERT_NEAR(-28.6304, vector1->dot(vector2), 0.01);
}

TEST(TwoDimensionalVectorTest, testVectorCross)
{
    Point *a = new Point(-8.42, 3.42);
    Point *b = new Point(-3.38, 4.3);
    TwoDimensionalVector *vector1 = new TwoDimensionalVector(a, b);
    Point *c = new Point(-2.48, 2.43);
    Point *d = new Point(-8.33, 3.4);
    TwoDimensionalVector *vector2 = new TwoDimensionalVector(c, d);

    ASSERT_NEAR(10.0368, vector1->cross(vector2), 0.01);
}

TEST(TwoDimensionalVectorTest, testVectorInfo)
{
    Point *a = new Point(-8.42, 3.42);
    Point *b = new Point(-3.38, 4.3);
    TwoDimensionalVector *vector = new TwoDimensionalVector(a, b);
    
    ASSERT_EQ("Vector ((-8.42, 3.42), (-3.38, 4.30))", vector->info());
}

