#include "../src/point.h"

TEST(PointTest, testPointGetters)
{
    Point p(-4.586, -3.471);
    ASSERT_EQ(-4.586, p.getX());
    ASSERT_EQ(-3.471, p.getY());
}
