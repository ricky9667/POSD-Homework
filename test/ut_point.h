#include "../src/point.h"

TEST(PointTest, testPointGetters)
{
    Point p(-4.586, -3.471);
    ASSERT_EQ(-4.586, p.getX());
    ASSERT_EQ(-3.471, p.getY());
}

TEST(PointTest, testOperatorEqual)
{
    Point p(-4.586, -3.471);
    Point p1(-4.586, -3.471);
    Point p2(4.586, 3.471);

    ASSERT_TRUE(p == p1);
    ASSERT_FALSE(p == p2);
}