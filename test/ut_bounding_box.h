#include <vector>
#include <set>
#include "../src/rectangle.h"
#include "../src/bounding_box.h"

class CollisionTest : public ::testing::Test
{
protected:
    Point *G, *F, *E, *D, *A, *B, *C, *H, *I, *J;
    Point *R, *S, *T, *U, *K, *M, *N, *O, *P, *Q;
    std::vector<Rectangle *> recs;
    std::vector<BoundingBox *> boxes;

    void SetUp() override
    {
        G = new Point(-3, 3);
        F = new Point(-1, 3);
        E = new Point(-3, 1);
        D = new Point(-1, 1);

        A = new Point(-1, -1);
        B = new Point(1, -1);
        C = new Point(1, 1);

        H = new Point(3, 1);
        I = new Point(3, 3);
        J = new Point(1, 3);

        R = new Point(-2, -1);
        S = new Point(-3, -2);
        T = new Point(-2, -3);
        U = new Point(-1, -2);

        K = new Point(0, -1);
        M = new Point(0, -3);
        N = new Point(1, -2);

        O = new Point(2, -1);
        P = new Point(2, -3);
        Q = new Point(3, -2);

        TwoDimensionalVector u(*G, *F), v(*F, *D); // 0
        TwoDimensionalVector n(*D, *C), m(*D, *A); // 1
        TwoDimensionalVector p(*C, *J), q(*I, *J); // 2
        TwoDimensionalVector r(*R, *S), t(*S, *T); // 3
        TwoDimensionalVector g(*M, *U), h(*M, *N); // 4
        TwoDimensionalVector k(*Q, *O), l(*P, *Q); // 5

        recs = {
            new Rectangle(u, v), // 0
            new Rectangle(n, m), // 1
            new Rectangle(p, q), // 2
            new Rectangle(r, t), // 3
            new Rectangle(g, h), // 4
            new Rectangle(k, l)  // 5
        };

        boxes = {
            new BoundingBox(recs[0]->getPoints()),
            new BoundingBox(recs[1]->getPoints()),
            new BoundingBox(recs[2]->getPoints()),
            new BoundingBox(recs[3]->getPoints()),
            new BoundingBox(recs[4]->getPoints()),
            new BoundingBox(recs[5]->getPoints()),
        };
    }
    void TearDown() override
    {
        delete G;
        delete F;
        delete E;
        delete D;

        delete A;
        delete B;
        delete C;

        delete H;
        delete I;
        delete J;

        delete R;
        delete S;
        delete T;
        delete U;

        delete K;
        delete M;
        delete N;

        delete O;
        delete P;
        delete Q;

        for (std::vector<Rectangle *>::iterator it = recs.begin(); it != recs.end(); it++)
            delete (*it);
        for (std::vector<BoundingBox *>::iterator it = boxes.begin(); it != boxes.end(); it++)
            delete (*it);
    }
};

// TEST_F(CollisionTest, CalMaximumPointShouldBeCorrect)
// {
//     BoundingBox bb1(
//         std::set<const Point *>{G, F, D, E});
//     ASSERT_TRUE(*(bb1.max()) == *F);
//     BoundingBox bb2(
//         std::set<const Point *>{A, B, C, D});
//     ASSERT_TRUE(*(bb2.max()) == *C);
//     BoundingBox bb3(
//         std::set<const Point *>{R, S, T, U});
//     ASSERT_TRUE(*(bb3.max()) == *A);
// }

// TEST_F(CollisionTest, CalMinimumPointShouldBeCorrect)
// {
//     BoundingBox bb1(
//         std::set<const Point *>{G, F, D, E});
//     ASSERT_TRUE(*(bb1.min()) == *E);
//     BoundingBox bb2(
//         std::set<const Point *>{A, B, C, D});
//     ASSERT_TRUE(*(bb2.min()) == *A);
//     BoundingBox bb3(
//         std::set<const Point *>{R, S, T, U});
//     ASSERT_TRUE(*(bb3.min()) == Point(-3, -3));
// }

TEST_F(CollisionTest, BoundingBoxOfRectangleShouldBeCorrect)
{
    ASSERT_TRUE(boxes.at(0)->max() == *F);
    ASSERT_TRUE(boxes.at(0)->min() == *E);
    ASSERT_TRUE(boxes.at(1)->max() == *C);
    ASSERT_TRUE(boxes.at(1)->min() == *A);
    ASSERT_TRUE(boxes.at(2)->max() == *I);
    ASSERT_TRUE(boxes.at(2)->min() == *C);

    ASSERT_TRUE(boxes.at(3)->max() == *A);
    ASSERT_TRUE(boxes.at(3)->min() == Point(-3, -3));
    ASSERT_TRUE(boxes.at(4)->max() == *B);
    ASSERT_TRUE(boxes.at(4)->min() == Point(-1, -3));
    ASSERT_TRUE(boxes.at(5)->max() == Point(3, -1));
    ASSERT_TRUE(boxes.at(5)->min() == Point(1, -3));
}

TEST_F(CollisionTest, BoundingBoxOfCircleShouldBeCorrect)
{
    Point X(0, -2);
    TwoDimensionalVector o(X, *N);
    Circle cir1(o);
    BoundingBox box1(cir1.getPoints());
    ASSERT_TRUE(box1.max() == *B);
    ASSERT_TRUE(box1.min() == Point(-1, -3));

    Point I(0, 0), L(0, 1);
    TwoDimensionalVector p(I, L);
    Circle cir2(p);
    BoundingBox box2(cir2.getPoints());
    ASSERT_TRUE(box2.max() == *C);
    ASSERT_TRUE(box2.min() == *A);
}

TEST_F(CollisionTest, BoundingBoxOfTriangleShouldBeCorrect)
{
    TwoDimensionalVector u(*U, *K), v(*K, *B);
    Triangle tri1(u, v);
    BoundingBox box1(tri1.getPoints());
    ASSERT_TRUE(box1.max() == *B);
    ASSERT_TRUE(box1.min() == *U);

    TwoDimensionalVector n(*F, *J), m(*J, *K);
    Triangle tri2(n, m);
    BoundingBox box2(tri2.getPoints());
    ASSERT_TRUE(box2.max() == *J);
    ASSERT_TRUE(box2.min() == *A);
}

TEST_F(CollisionTest, TwoAdjacentRectanglesShouldCollide)
{
    ASSERT_TRUE(boxes[0]->collide(boxes[1]));

    ASSERT_TRUE(boxes[1]->collide(boxes[1]));
    ASSERT_TRUE(boxes[1]->collide(boxes[2]));
    ASSERT_TRUE(boxes[1]->collide(boxes[3]));
    ASSERT_TRUE(boxes[1]->collide(boxes[4]));
    ASSERT_TRUE(boxes[1]->collide(boxes[5]));

    ASSERT_TRUE(boxes[2]->collide(boxes[1]));

    ASSERT_TRUE(boxes[3]->collide(boxes[1]));
    ASSERT_TRUE(boxes[3]->collide(boxes[4]));

    ASSERT_TRUE(boxes[4]->collide(boxes[1]));
    ASSERT_TRUE(boxes[4]->collide(boxes[3]));
    ASSERT_TRUE(boxes[4]->collide(boxes[4]));
    ASSERT_TRUE(boxes[4]->collide(boxes[5]));

    ASSERT_TRUE(boxes[5]->collide(boxes[1]));
    ASSERT_TRUE(boxes[5]->collide(boxes[4]));
}

TEST_F(CollisionTest, TwoNonAdjacentRectanglesShouldNotCollide)
{
    ASSERT_FALSE(boxes[0]->collide(boxes[2]));
    ASSERT_FALSE(boxes[0]->collide(boxes[3]));
    ASSERT_FALSE(boxes[0]->collide(boxes[4]));
    ASSERT_FALSE(boxes[0]->collide(boxes[5]));

    ASSERT_FALSE(boxes[2]->collide(boxes[0]));
    ASSERT_FALSE(boxes[2]->collide(boxes[3]));
    ASSERT_FALSE(boxes[2]->collide(boxes[4]));
    ASSERT_FALSE(boxes[2]->collide(boxes[5]));

    ASSERT_FALSE(boxes[3]->collide(boxes[0]));
    ASSERT_FALSE(boxes[3]->collide(boxes[2]));
    ASSERT_FALSE(boxes[3]->collide(boxes[5]));

    ASSERT_FALSE(boxes[4]->collide(boxes[0]));
    ASSERT_FALSE(boxes[4]->collide(boxes[2]));

    ASSERT_FALSE(boxes[5]->collide(boxes[0]));
    ASSERT_FALSE(boxes[5]->collide(boxes[2]));
    ASSERT_FALSE(boxes[5]->collide(boxes[3]));
}

TEST_F(CollisionTest, TwoAdjacentTrianglesShouldCollide)
{
    TwoDimensionalVector i(*F, *J), j(*J, *K);
    Triangle tri1(i, j);
    TwoDimensionalVector k(*H, *C), l(*C, *B);
    Triangle tri2(k, l);

    BoundingBox tri1_box(tri1.getPoints());
    BoundingBox tri2_box(tri2.getPoints());
    ASSERT_TRUE(tri1_box.collide(&tri2_box));
    ASSERT_TRUE(tri2_box.collide(&tri1_box));
}

TEST_F(CollisionTest, TwoNonAdjacentTrianglesShouldNotCollide)
{
    TwoDimensionalVector i(*F, *J), j(*J, *K);
    Triangle tri1(i, j);
    TwoDimensionalVector k(*N, *P), l(*Q, *P);
    Triangle tri2(k, l);
    BoundingBox tri1_box(tri1.getPoints());
    BoundingBox tri2_box(tri2.getPoints());
    ASSERT_FALSE(tri1_box.collide(&tri2_box));
    ASSERT_FALSE(tri2_box.collide(&tri1_box));
}

TEST_F(CollisionTest, TwoAdjacentCirclesShouldCollide)
{
    TwoDimensionalVector u(*K, *B), v(*N, *P);
    Circle cir1(u), cir2(v);
    BoundingBox cir1_box(cir1.getPoints());
    BoundingBox cir2_box(cir2.getPoints());
    ASSERT_TRUE(cir1_box.collide(&cir2_box));
    ASSERT_TRUE(cir2_box.collide(&cir1_box));
}

TEST_F(CollisionTest, TwoNonAdjacentCirclesShouldNotCollide)
{
    TwoDimensionalVector u(*K, *B), v(*F, *G);
    Circle cir1(u), cir2(v);
    BoundingBox cir1_box(cir1.getPoints());
    BoundingBox cir2_box(cir2.getPoints());
    ASSERT_FALSE(cir1_box.collide(&cir2_box));
    ASSERT_FALSE(cir2_box.collide(&cir1_box));
}

// #include <set>
// #include "../src/point.h"
// #include "../src/bounding_box.h"

// class BoundingBoxTest : public ::testing::Test
// {
// protected:
//     const double difference = 0.001;
//     Point *p0, *p1, *p2, *p3, *p4, *p5;

//     void SetUp()
//     {
//         p0 = new Point(0, 0);
//         p1 = new Point(-28, 15);
//         p2 = new Point(-5, 1);
//         p3 = new Point(11, 6);
//         p4 = new Point(-5, -11);
//         p5 = new Point(-14, -9);
//     }

//     void TearDown()
//     {
//         delete p0;
//         delete p1;
//         delete p2;
//         delete p3;
//         delete p4;
//         delete p5;
//     }
// };

// TEST_F(BoundingBoxTest, ConstructorDoesNotThrowException)
// {
//     Point *points[] = {p0, p1, p2, p3, p4, p5};
//     std::set<const Point *> pointsSet(points, points + 6);
//     ASSERT_NO_THROW(new BoundingBox(pointsSet));
// }

// TEST_F(BoundingBoxTest, CalculateMaxPointWorksExpectedly)
// {
//     Point *points[] = {p0, p1, p2, p3, p4, p5};
//     std::set<const Point *> pointsSet(points, points + 6);
//     BoundingBox *boundingBox = new BoundingBox(pointsSet);

//     Point *maxPoint = boundingBox->calMaximumPoint(pointsSet);
//     ASSERT_NEAR(p3->x(), maxPoint->x(), difference);
//     ASSERT_NEAR(p1->y(), maxPoint->y(), difference);
// }

// TEST_F(BoundingBoxTest, CalculateMinPointWorksExpectedly)
// {
//     Point *points[] = {p0, p1, p2, p3, p4, p5};
//     std::set<const Point *> pointsSet(points, points + 6);
//     BoundingBox *boundingBox = new BoundingBox(pointsSet);

//     Point *minPoint = boundingBox->calMinimumPoint(pointsSet);
//     ASSERT_NEAR(p1->x(), minPoint->x(), difference);
//     ASSERT_NEAR(p4->y(), minPoint->y(), difference);
// }

// TEST_F(BoundingBoxTest, MaxWorkingExpectedly)
// {
//     Point *points[] = {p0, p1, p2, p3, p4, p5};
//     std::set<const Point *> pointsSet(points, points + 6);
//     BoundingBox *boundingBox = new BoundingBox(pointsSet);

//     const Point *maxPoint = boundingBox->max();
//     ASSERT_NEAR(p3->x(), maxPoint->x(), difference);
//     ASSERT_NEAR(p1->y(), maxPoint->y(), difference);
// }

// TEST_F(BoundingBoxTest, MinWorksExpectedly)
// {
//     Point *points[] = {p0, p1, p2, p3, p4, p5};
//     std::set<const Point *> pointsSet(points, points + 6);
//     BoundingBox *boundingBox = new BoundingBox(pointsSet);

//     const Point *minPoint = boundingBox->min();
//     ASSERT_NEAR(p1->x(), minPoint->x(), difference);
//     ASSERT_NEAR(p4->y(), minPoint->y(), difference);
// }

// TEST_F(BoundingBoxTest, CalculateMaxOrMinPointShouldThrowExceptionWithEmptySet)
// {
//     std::set<const Point *> emptyPointsSet;
//     ASSERT_ANY_THROW(new BoundingBox(emptyPointsSet));

//     Point *points[] = {p0, p1, p2, p3, p4, p5};
//     std::set<const Point *> pointsSet(points, points + 6);
//     BoundingBox *boundingBox = new BoundingBox(pointsSet);
//     ASSERT_ANY_THROW(boundingBox->calMaximumPoint(emptyPointsSet));
//     ASSERT_ANY_THROW(boundingBox->calMinimumPoint(emptyPointsSet));
// }

// TEST_F(BoundingBoxTest, BoxesCollideShouldWorkAsExpected)
// {
//     Point *points1[] = {p0, p1, p2};
//     Point *points2[] = {p3, p4, p5};
//     std::set<const Point *> pointsSet1(points1, points1 + 3);
//     std::set<const Point *> pointsSet2(points2, points2 + 3);
//     BoundingBox *boundingBox1 = new BoundingBox(pointsSet1);
//     BoundingBox *boundingBox2 = new BoundingBox(pointsSet2);

//     ASSERT_TRUE(boundingBox1->collide(boundingBox2));
// }

// TEST_F(BoundingBoxTest, BoxesDoNotCollideShouldWorkAsExpected)
// {
//     Point *points1[] = {p1};
//     Point *points2[] = {p0, p2, p3, p4, p5};
//     std::set<const Point *> pointsSet1(points1, points1 + 1);
//     std::set<const Point *> pointsSet2(points2, points2 + 5);
//     BoundingBox *boundingBox1 = new BoundingBox(pointsSet1);
//     BoundingBox *boundingBox2 = new BoundingBox(pointsSet2);

//     ASSERT_FALSE(boundingBox1->collide(boundingBox2));
// }

// TEST_F(BoundingBoxTest, DistanceShouldWorkExpectedly)
// {
//     Point *points1[] = {p0};
//     Point *points2[] = {p2, p3};
//     std::set<const Point *> pointsSet1(points1, points1 + 1);
//     std::set<const Point *> pointsSet2(points2, points2 + 2);
//     BoundingBox *boundingBox1 = new BoundingBox(pointsSet1);
//     BoundingBox *boundingBox2 = new BoundingBox(pointsSet2);

//     ASSERT_NEAR(17.629, boundingBox1->distance(boundingBox2), 0.001);
// }