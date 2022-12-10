#include "../../src/visitor/collision_detector.h"
#include "../../src/circle.h"

#include <vector>

class CollisionDetectorTest : public ::testing::Test
{
protected:
    Point *pA, *pB, *pC, *pD, *pE, *pF, *pG, *pH, *pI, *pJ;
    TwoDimensionalVector *r1, *r2;
    TwoDimensionalVector *v1, *v2;
    TwoDimensionalVector *width, *length;
    Shape *shape;

    std::vector<Shape *> result;

    void SetUp() override
    {
        pA = new Point(26, 14);
        pB = new Point(20, 14);
        pC = new Point(24, 7.2);
        pD = new Point(22, 7.2);
        pE = new Point(30, 4);
        pF = new Point(34, 9);
        pG = new Point(34, 6);
        pH = new Point(20, 6);
        pI = new Point(21, 10);
        pJ = new Point(16, 7);
        r1 = new TwoDimensionalVector(*pA, *pB);
        r2 = new TwoDimensionalVector(*pC, *pD);
        v1 = new TwoDimensionalVector(*pE, *pF);
        v2 = new TwoDimensionalVector(*pG, *pF);
        width = new TwoDimensionalVector(*pH, *pI);
        length = new TwoDimensionalVector(*pH, *pJ);

        shape = new Circle(*r1);
    }

    void TearDown() override
    {
        delete pA;
        delete pB;
        delete pC;
        delete pD;
        delete pE;
        delete pF;
        delete pG;
        delete pH;
        delete pI;
        delete pJ;
        delete r1;
        delete r2;
        delete v1;
        delete v2;
        delete width;
        delete length;
        delete shape;
    }
};

TEST_F(CollisionDetectorTest, visitCircleShouldBeCorrect)
{
    Shape *cir = new Circle(*r2);
    CollisionDetector *visitor = new CollisionDetector(shape);

    cir->accept(visitor);
    result = visitor->collidedShapes();

    ASSERT_EQ(cir, result.at(0));

    delete visitor;
    delete cir;
}

TEST_F(CollisionDetectorTest, visitTriangleShouldBeCorrect)
{
    Shape *tri = new Triangle(*v1, *v2);
    CollisionDetector *visitor = new CollisionDetector(shape);

    tri->accept(visitor);
    result = visitor->collidedShapes();

    ASSERT_EQ(tri, result.at(0));

    delete visitor;
    delete tri;
}

TEST_F(CollisionDetectorTest, visitRectangleShouldBeCorrect)
{
    Shape *rect = new Rectangle(*width, *length);
    CollisionDetector *visitor = new CollisionDetector(shape);

    rect->accept(visitor);
    result = visitor->collidedShapes();

    ASSERT_EQ(rect, result.at(0));

    delete visitor;
    delete rect;
}

TEST_F(CollisionDetectorTest, visitCompoundShapeShouldBeCorrect1)
{
    Shape *cir = new Circle(*r2);
    Shape *tri = new Triangle(*v1, *v2);
    Shape *rect = new Rectangle(*width, *length);
    Shape *shapes[] = {cir, tri, rect};
    Shape *cs = new CompoundShape(shapes, 3);

    CollisionDetector *visitor = new CollisionDetector(shape);

    cs->accept(visitor);
    result = visitor->collidedShapes();

    ASSERT_EQ(cir, result.at(0));
    ASSERT_EQ(tri, result.at(1));
    ASSERT_EQ(rect, result.at(2));

    delete visitor;
    delete cs;
}

TEST_F(CollisionDetectorTest, visitCompoundShapeShouldBeCorrect2)
{
    Point G(-13, 7), C(-14, 6), F(-12, 6), D(-14, 4);
    TwoDimensionalVector u(D, C), v(C, F), w(G, F);
    Rectangle *rect1 = new Rectangle(u, v);
    Circle *cir1 = new Circle(w);
    Shape *s1[] = {cir1, rect1};
    CompoundShape *target1 = new CompoundShape(s1, 2);

    Point L(-9, 12), M(-8, 13), K(-10, 11), H(-10, 9), I(-8, 9);
    TwoDimensionalVector x(K, H), y(H, I), z(L, M);
    Rectangle *rect2 = new Rectangle(x, y);
    Circle *cir2 = new Circle(z);
    Shape *s2[] = {cir2, rect2};
    CompoundShape *target2 = new CompoundShape(s2, 2);

    Point R(-5, 3), N(-6, 2), Q(-4, 2), P(-4, 0);
    TwoDimensionalVector p(N, Q), q(P, Q), r(R, N);
    Rectangle *rect3 = new Rectangle(p, q);
    Circle *cir3 = new Circle(r);
    Shape *s3[] = {cir3, rect3};
    CompoundShape *target3 = new CompoundShape(s3, 2);

    Shape *st1[] = {target1, target2};
    CompoundShape *target_set1 = new CompoundShape(st1, 2);
    Shape *st2[] = {target_set1, target3};
    CompoundShape *target_set2 = new CompoundShape(st2, 2);

    Point S(-8, 6), T(-8.5, 5), U(-7.5, 5);
    TwoDimensionalVector k(S, T), h(T, U);
    Triangle bullet1(k, h);
    CollisionDetector first_shoot(&bullet1);
    target_set2->accept(&first_shoot);
    result = first_shoot.collidedShapes();
    ASSERT_TRUE(result.size() == 0);

    Point V(-9, 11.6), W(-9.4, 11), Z(-8.6, 11);
    TwoDimensionalVector a(V, Z), b(Z, W);
    Triangle bullet2(a, b);
    CollisionDetector second_shoot(&bullet2);
    target_set2->accept(&second_shoot);
    result = second_shoot.collidedShapes();
    ASSERT_TRUE(result.size() == 2);
    ASSERT_EQ(cir2, result.at(0));
    ASSERT_EQ(rect2, result.at(1));

    delete target_set2;
}

// #include "../../src/point.h"
// #include "../../src/two_dimensional_vector.h"
// #include "../../src/triangle.h"
// #include "../../src/rectangle.h"
// #include "../../src/circle.h"
// #include "../../src/compound_shape.h"
// #include "../../src/visitor/shape_visitor.h"
// #include "../../src/visitor/collision_detector.h"

// class CollisionDetectorTest : public ::testing::Test
// {
// protected:
//     Point *p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9, *p10, *p11, *p12;
//     TwoDimensionalVector *v1, *v2, *v3, *v4, *v5, *v6;
//     Triangle *t1;
//     Rectangle *r1;
//     Circle *c1, *c2;
//     CompoundShape *com1, *com2, *com3;

//     void SetUp() override
//     {
//         p0 = new Point(0, 0);
//         p1 = new Point(8, 2);
//         p2 = new Point(0, 0);
//         p3 = new Point(2, 0);
//         p4 = new Point(2, 2);
//         p5 = new Point(3, 2);
//         p6 = new Point(2, 2);
//         p7 = new Point(2, 7);
//         p8 = new Point(2, 6);
//         p9 = new Point(1, 6);
//         p10 = new Point(8, 5);
//         p11 = new Point(-1, -1);
//         v1 = new TwoDimensionalVector(p0, p1);
//         v2 = new TwoDimensionalVector(p2, p3);
//         v3 = new TwoDimensionalVector(p4, p5);
//         v4 = new TwoDimensionalVector(p6, p7);
//         v5 = new TwoDimensionalVector(p8, p9);
//         v6 = new TwoDimensionalVector(p10, p11);
//         t1 = new Triangle(v1, v2);
//         r1 = new Rectangle(v3, v4);
//         c1 = new Circle(v5);
//         c2 = new Circle(v6);

//         Shape *shapes2[] = {t1};
//         com2 = new CompoundShape(shapes2, 1);
//         Shape *shapes3[] = {r1, c1, c2};
//         com3 = new CompoundShape(shapes3, 3);
//         Shape *shapes1[] = {com2, com3};
//         com1 = new CompoundShape(shapes1, 2);
//     }

//     void TearDown() override
//     {
//         delete p0;
//         delete p1;
//         delete p2;
//         delete p3;
//         delete p4;
//         delete p5;
//         delete p6;
//         delete p7;
//         delete p8;
//         delete p9;
//         delete p10;
//         delete p11;
//         delete v1;
//         delete v2;
//         delete v3;
//         delete v4;
//         delete v5;
//         delete v6;
//         delete t1;
//         delete r1;
//         delete c1;
//         delete c2;
//         delete com2;
//         delete com3;
//         delete com1;
//     }
// };

// TEST_F(CollisionDetectorTest, ConstructorDoesNotThrowException)
// {
//     ASSERT_NO_THROW(new CollisionDetector(t1));
//     ASSERT_NO_THROW(new CollisionDetector(r1));
//     ASSERT_NO_THROW(new CollisionDetector(c1));
//     ASSERT_NO_THROW(new CollisionDetector(com2));
//     ASSERT_NO_THROW(new CollisionDetector(com1));
// }

// TEST_F(CollisionDetectorTest, VisitCircleWorksExpectedly)
// {
//     CollisionDetector *visitor = new CollisionDetector(t1);
//     visitor->visitCircle(c1);
//     std::vector<Shape *> collidedShapes = visitor->collidedShapes();
//     ASSERT_EQ(0, collidedShapes.size());
// }

// TEST_F(CollisionDetectorTest, VisitTriangleWorksExpectedly)
// {
//     CollisionDetector *visitor = new CollisionDetector(r1);
//     visitor->visitTriangle(t1);
//     std::vector<Shape *> collidedShapes = visitor->collidedShapes();
//     ASSERT_EQ(1, collidedShapes.size());
//     ASSERT_EQ(t1, collidedShapes[0]);
// }

// TEST_F(CollisionDetectorTest, VisitRectangleWorksExpectedly)
// {
//     CollisionDetector *visitor = new CollisionDetector(c1);
//     visitor->visitRectangle(r1);
//     std::vector<Shape *> collidedShapes = visitor->collidedShapes();
//     ASSERT_EQ(1, collidedShapes.size());
//     ASSERT_EQ(r1, collidedShapes[0]);
// }

// TEST_F(CollisionDetectorTest, VisitCompoundShapeWorksExpectedly)
// {
//     Shape *shape = new Circle(
//         new TwoDimensionalVector(new Point(3, 7), new Point(5, 8)));
//     CollisionDetector *visitor = new CollisionDetector(shape);
//     visitor->visitCompoundShape(com1);
//     std::vector<Shape *> collidedShapes = visitor->collidedShapes();

//     ASSERT_EQ(3, collidedShapes.size());
//     ASSERT_EQ(r1, collidedShapes[0]);
//     ASSERT_EQ(c1, collidedShapes[1]);
//     ASSERT_EQ(c2, collidedShapes[2]);
// }

// TEST_F(CollisionDetectorTest, CollidedShapesShowsResultExpectedly)
// {
//     Triangle *triangle = new Triangle(
//         new TwoDimensionalVector(new Point(-1, -1), new Point(2, -1)),
//         new TwoDimensionalVector(new Point(-1, -1), new Point(-1, 1)));
//     Circle *circle = new Circle(
//         new TwoDimensionalVector(new Point(2, 2), new Point(4, 4)));

//     CollisionDetector *visitor = new CollisionDetector(triangle);
//     visitor->visitCircle(circle);
//     std::vector<Shape *> collidedShapes = visitor->collidedShapes();
//     ASSERT_EQ(1, collidedShapes.size());
//     ASSERT_EQ(circle, collidedShapes[0]);
// }
