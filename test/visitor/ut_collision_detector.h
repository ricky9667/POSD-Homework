#include "../../src/point.h"
#include "../../src/two_dimensional_vector.h"
#include "../../src/triangle.h"
#include "../../src/rectangle.h"
#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/visitor/shape_visitor.h"
#include "../../src/visitor/collision_detector.h"

class CollisionDetectorTest : public ::testing::Test
{
protected:
    Point *p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9, *p10, *p11, *p12;
    TwoDimensionalVector *v1, *v2, *v3, *v4, *v5, *v6;
    Triangle *t1;
    Rectangle *r1;
    Circle *c1, *c2;
    CompoundShape *com1, *com2, *com3;

    void SetUp() override
    {
        p0 = new Point(0, 0);
        p1 = new Point(8, 2);
        p2 = new Point(0, 0);
        p3 = new Point(2, 0);
        p4 = new Point(2, 2);
        p5 = new Point(3, 2);
        p6 = new Point(2, 2);
        p7 = new Point(2, 7);
        p8 = new Point(2, 6);
        p9 = new Point(1, 6);
        p10 = new Point(8, 5);
        p11 = new Point(-1, -1);
        v1 = new TwoDimensionalVector(p0, p1);
        v2 = new TwoDimensionalVector(p2, p3);
        v3 = new TwoDimensionalVector(p4, p5);
        v4 = new TwoDimensionalVector(p6, p7);
        v5 = new TwoDimensionalVector(p8, p9);
        v6 = new TwoDimensionalVector(p10, p11);
        t1 = new Triangle(v1, v2);
        r1 = new Rectangle(v3, v4);
        c1 = new Circle(v5);
        c2 = new Circle(v6);

        Shape *shapes2[] = {t1};
        com2 = new CompoundShape(shapes2, 1);
        Shape *shapes3[] = {r1, c1, c2};
        com3 = new CompoundShape(shapes3, 3);
        Shape *shapes1[] = {com2, com3};
        com1 = new CompoundShape(shapes1, 2);
    }

    void TearDown() override
    {
        delete p0;
        delete p1;
        delete p2;
        delete p3;
        delete p4;
        delete p5;
        delete p6;
        delete p7;
        delete p8;
        delete p9;
        delete p10;
        delete p11;
        delete v1;
        delete v2;
        delete v3;
        delete v4;
        delete v5;
        delete v6;
        delete t1;
        delete r1;
        delete c1;
        delete c2;
        delete com2;
        delete com3;
        delete com1;
    }
};

TEST_F(CollisionDetectorTest, ConstructorDoesNotThrowException)
{
    ASSERT_NO_THROW(new CollisionDetector(t1));
    ASSERT_NO_THROW(new CollisionDetector(r1));
    ASSERT_NO_THROW(new CollisionDetector(c1));
    ASSERT_NO_THROW(new CollisionDetector(com2));
    ASSERT_NO_THROW(new CollisionDetector(com1));
}

TEST_F(CollisionDetectorTest, VisitCircleWorksExpectedly)
{
    CollisionDetector *visitor = new CollisionDetector(t1);
    visitor->visitCircle(c1);
    std::vector<Shape *> collidedShapes = visitor->collidedShapes();
    ASSERT_EQ(0, collidedShapes.size());
}

TEST_F(CollisionDetectorTest, VisitTriangleWorksExpectedly)
{
    CollisionDetector *visitor = new CollisionDetector(r1);
    visitor->visitTriangle(t1);
    std::vector<Shape *> collidedShapes = visitor->collidedShapes();
    ASSERT_EQ(1, collidedShapes.size());
    ASSERT_EQ(t1, collidedShapes[0]);
}

TEST_F(CollisionDetectorTest, VisitRectangleWorksExpectedly)
{
    CollisionDetector *visitor = new CollisionDetector(c1);
    visitor->visitRectangle(r1);
    std::vector<Shape *> collidedShapes = visitor->collidedShapes();
    ASSERT_EQ(1, collidedShapes.size());
    ASSERT_EQ(r1, collidedShapes[0]);
}

TEST_F(CollisionDetectorTest, VisitCompoundShapeWorksExpectedly)
{
    Shape *shape = new Circle(
        new TwoDimensionalVector(new Point(3, 7), new Point(5, 8)));
    CollisionDetector *visitor = new CollisionDetector(shape);
    visitor->visitCompoundShape(com1);
    std::vector<Shape *> collidedShapes = visitor->collidedShapes();

    ASSERT_EQ(3, collidedShapes.size());
    ASSERT_EQ(r1, collidedShapes[0]);
    ASSERT_EQ(c1, collidedShapes[1]);
    ASSERT_EQ(c2, collidedShapes[2]);
}

TEST_F(CollisionDetectorTest, CollidedShapesShowsResultExpectedly)
{
    Triangle *triangle = new Triangle(
        new TwoDimensionalVector(new Point(-1, -1), new Point(2, -1)),
        new TwoDimensionalVector(new Point(-1, -1), new Point(-1, 1)));
    Circle *circle = new Circle(
        new TwoDimensionalVector(new Point(2, 2), new Point(4, 4)));

    CollisionDetector *visitor = new CollisionDetector(triangle);
    visitor->visitCircle(circle);
    std::vector<Shape *> collidedShapes = visitor->collidedShapes();
    ASSERT_EQ(1, collidedShapes.size());
    ASSERT_EQ(circle, collidedShapes[0]);
}
