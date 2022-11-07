#include "../../src/point.h"
#include "../../src/two_dimensional_vector.h"
#include "../../src/triangle.h"
#include "../../src/rectangle.h"
#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/visitor/shape_visitor.h"
#include "../../src/builder/aabb_tree_builder.h"

class AABBTreeBuilderTest : public ::testing::Test
{
protected:
    void SetUp()
    {
    }

    void TearDown()
    {
    }
};

TEST_F(AABBTreeBuilderTest, InsertTriangleShouldWorkExpectedly)
{
    AABBTreeBuilder builder;
    Point *commonPoint = new Point(0, 0);
    Point *v1Point = new Point(2, 0);
    Point *v2Point = new Point(8, 2);
    Triangle *triangle = new Triangle(
        new TwoDimensionalVector(commonPoint, v1Point),
        new TwoDimensionalVector(commonPoint, v2Point));

    builder.insertTriangle(commonPoint, v1Point, v2Point);
    ASSERT_EQ(triangle->info(), builder.getTree()->info());
}

TEST_F(AABBTreeBuilderTest, InsertCircleShouldWorkExpectedly)
{
    AABBTreeBuilder builder;
    Point *center = new Point(0, 0);
    Point *toRadius = new Point(3, 2);
    Circle *circle = new Circle(new TwoDimensionalVector(center, toRadius));

    builder.insertCircle(center, toRadius);
    ASSERT_EQ(circle->info(), builder.getTree()->info());
}

TEST_F(AABBTreeBuilderTest, InsertRectangleShouldWorkExpectedly)
{
    AABBTreeBuilder builder;
    Point *commonPoint = new Point(0, 0);
    Point *v1Point = new Point(2, 0);
    Point *v2Point = new Point(0, 8);
    Rectangle *triangle = new Rectangle(
        new TwoDimensionalVector(commonPoint, v1Point),
        new TwoDimensionalVector(commonPoint, v2Point));

    builder.insertRectangle(commonPoint, v1Point, v2Point);
    ASSERT_EQ(triangle->info(), builder.getTree()->info());
}
