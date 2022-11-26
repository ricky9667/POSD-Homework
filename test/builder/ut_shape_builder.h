#include <vector>
#include "../../src/builder/shape_builder.h"
#include "../../src/point.h"
#include "../../src/two_dimensional_vector.h"
#include "../../src/triangle.h"
#include "../../src/rectangle.h"
#include "../../src/circle.h"

class ShapeBuilderTest : public ::testing::Test
{
protected:
    Point *p0, *p1, *p2, *p3, *p4;
    TwoDimensionalVector *v1, *v2, *v3, *v4, *v5;
    Circle *circle;
    Triangle *triangle;
    Rectangle *rectangle;

    void SetUp()
    {
        p0 = new Point(0, 0);
        p1 = new Point(3, 2);
        p2 = new Point(2, 0);
        p3 = new Point(8, 2);
        p4 = new Point(0, 8);

        v1 = new TwoDimensionalVector(p0, p1);
        v2 = new TwoDimensionalVector(p0, p2);
        v3 = new TwoDimensionalVector(p0, p3);
        v4 = new TwoDimensionalVector(p0, p2);
        v5 = new TwoDimensionalVector(p0, p4);

        circle = new Circle(v1);
        triangle = new Triangle(v2, v3);
        rectangle = new Rectangle(v4, v5);
    }

    void TearDown()
    {
        delete p0;
        delete p1;
        delete p2;
        delete p3;
        delete p4;
        delete v1;
        delete v2;
        delete v3;
        delete v4;
        delete v5;
        delete circle;
        delete triangle;
        delete rectangle;
    }
};

TEST_F(ShapeBuilderTest, BuildCircleShouldWorkExpectedly)
{
    ShapeBuilder builder;
    builder.buildCircle(p0, p1);
    std::vector<Shape *> result = builder.getResult();
    ASSERT_EQ(circle->info(), result.at(0)->info());
}

TEST_F(ShapeBuilderTest, BuildTriangleShouldWorkExpectedly)
{
    ShapeBuilder builder;
    builder.buildTriangle(p0, p2, p3);
    std::vector<Shape *> result = builder.getResult();
    ASSERT_EQ(triangle->info(), result.at(0)->info());
}

TEST_F(ShapeBuilderTest, BuildRectangleShouldWorkExpectedly)
{
    ShapeBuilder builder;
    builder.buildRectangle(p0, p2, p4);
    std::vector<Shape *> result = builder.getResult();
    ASSERT_EQ(rectangle->info(), result.at(0)->info());
}

TEST_F(ShapeBuilderTest, BuildCompoundShapeShouldWorkExpectedly)
{
    ShapeBuilder builder;
    Shape *shapes[] = {circle, triangle, rectangle};
    CompoundShape *compoundShape = new CompoundShape(shapes, 3);

    builder.buildCompoundShape();
    builder.buildCircle(p0, p1);
    builder.buildTriangle(p0, p2, p3);
    builder.buildRectangle(p0, p2, p4);
    builder.buildCompoundEnd();

    std::vector<Shape *> result = builder.getResult();
    ASSERT_EQ(compoundShape->info(), result.at(0)->info());
}

TEST_F(ShapeBuilderTest, GetResultShouldWorkExpectedly)
{
    ShapeBuilder builder;
    Shape *shapes[] = {triangle, rectangle};
    CompoundShape *compoundShape = new CompoundShape(shapes, 2);

    builder.buildCircle(p0, p1);
    builder.buildCompoundShape();
    builder.buildTriangle(p0, p2, p3);
    builder.buildRectangle(p0, p2, p4);
    builder.buildCompoundEnd();

    std::vector<Shape *> result = builder.getResult();
    ASSERT_EQ(circle->info(), result.at(0)->info());
    ASSERT_EQ(compoundShape->info(), result.at(1)->info());
}
