#include "../src/point.h"

TEST(PointTest, testPointGetters)
{
    Point p(-4.586, -3.471);
    ASSERT_EQ(-4.586, p.x());
    ASSERT_EQ(-3.471, p.y());
}

TEST(PointTest, testOperatorEqual)
{
    Point p(-4.586, -3.471);
    Point p1(-4.586, -3.471);
    Point p2(4.586, 3.471);

    ASSERT_TRUE(p == p1);
    ASSERT_FALSE(p == p2);
}

TEST(PointTest, testInfo)
{
    Point p(-4.586, -3.471);
    
    ASSERT_EQ("(-4.59, -3.47)", p.info());
}
