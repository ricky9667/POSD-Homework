#include <cmath>
#include "../src/point.h"

TEST(PointTest, Constructor)
{
    ASSERT_NO_THROW(Point(0, 0));
    ASSERT_NO_THROW(Point(-2.58, -9.99));
}

TEST(PointTest, XShouldBeCorrect)
{
    Point p1(0, 0);
    ASSERT_NEAR(p1.x(), 0, 0.001);
    Point p2(-2.58, -9.99);
    ASSERT_NEAR(p2.x(), -2.58, 0.001);
}

TEST(PointTest, YShouldBeCorrect)
{
    Point p1(0, 0);
    ASSERT_NEAR(p1.y(), 0, 0.001);
    Point p2(2.58, 2.71828);
    ASSERT_NEAR(p2.y(), 2.718, 0.001);
}

TEST(PointTest, EqualityOperatorOverridingShouldBeCorrect)
{
    Point p1(2.58811, 2.71832);
    Point p2(2.58899, 2.71800);
    ASSERT_TRUE(p1 == p2);
}

TEST(PointTest, InfoShouldBeCorrect)
{
    Point p(-4.586, -3.471);
    ASSERT_EQ("(-4.59, -3.47)", p.info());
}

// #include "../src/point.h"

// TEST(PointTest, CoordinatesShouldBeReceivedExpectedly)
// {
//     Point p(-4.586, -3.471);
//     ASSERT_EQ(-4.586, p.x());
//     ASSERT_EQ(-3.471, p.y());
// }

// TEST(PointTest, OperatorEqualShouldWorkExpectedly)
// {
//     Point p(-4.586, -3.471);
//     Point p1(-4.586, -3.471);
//     Point p2(4.586, 3.471);

//     ASSERT_TRUE(p == p1);
//     ASSERT_FALSE(p == p2);
// }

// TEST(PointTest, InfoShouldWorkExpectedly)
// {
//     Point p(-4.586, -3.471);

//     ASSERT_EQ("(-4.59, -3.47)", p.info());
// }
