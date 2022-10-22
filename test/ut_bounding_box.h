#include <set>
#include "../src/point.h"
#include "../src/bounding_box.h"

class BoundingBoxTest : public ::testing::Test
{
protected:
    const double difference = 0.001;
    Point *p0, *p1, *p2, *p3, *p4, *p5;

    void SetUp()
    {
        p0 = new Point(0, 0);
        p1 = new Point(-28, 15);
        p2 = new Point(-5, 1);
        p3 = new Point(11, 6);
        p4 = new Point(-5, -11);
        p5 = new Point(-14, -9);
    }

    void TearDown()
    {
        delete p0;
        delete p1;
        delete p2;
        delete p3;
        delete p4;
        delete p5;
    }
};

TEST_F(BoundingBoxTest, ConstructorDoesNotThrowException)
{
    Point *points[] = {p0, p1, p2, p3, p4, p5};
    std::set<const Point *> pointsSet(points, points + 6);
    ASSERT_NO_THROW(new BoundingBox(pointsSet));
}

TEST_F(BoundingBoxTest, CalculateMaxPointWorksExpectedly)
{
    Point *points[] = {p0, p1, p2, p3, p4, p5};
    std::set<const Point *> pointsSet(points, points + 6);
    BoundingBox *boundingBox = new BoundingBox(pointsSet);

    Point *maxPoint = boundingBox->calMaximumPoint(pointsSet);
    ASSERT_NEAR(p3->x(), maxPoint->x(), difference);
    ASSERT_NEAR(p1->y(), maxPoint->y(), difference);
}

TEST_F(BoundingBoxTest, CalculateMinPointWorksExpectedly)
{
    Point *points[] = {p0, p1, p2, p3, p4, p5};
    std::set<const Point *> pointsSet(points, points + 6);
    BoundingBox *boundingBox = new BoundingBox(pointsSet);

    Point *minPoint = boundingBox->calMinimumPoint(pointsSet);
    ASSERT_NEAR(p1->x(), minPoint->x(), difference);
    ASSERT_NEAR(p4->y(), minPoint->y(), difference);
}

TEST_F(BoundingBoxTest, MaxWorkingExpectedly)
{
    Point *points[] = {p0, p1, p2, p3, p4, p5};
    std::set<const Point *> pointsSet(points, points + 6);
    BoundingBox *boundingBox = new BoundingBox(pointsSet);

    const Point *maxPoint = boundingBox->max();
    ASSERT_NEAR(p3->x(), maxPoint->x(), difference);
    ASSERT_NEAR(p1->y(), maxPoint->y(), difference);
}

TEST_F(BoundingBoxTest, MinWorksExpectedly)
{
    Point *points[] = {p0, p1, p2, p3, p4, p5};
    std::set<const Point *> pointsSet(points, points + 6);
    BoundingBox *boundingBox = new BoundingBox(pointsSet);

    const Point *minPoint = boundingBox->min();
    ASSERT_NEAR(p1->x(), minPoint->x(), difference);
    ASSERT_NEAR(p4->y(), minPoint->y(), difference);
}

TEST_F(BoundingBoxTest, CalculateMaxOrMinPointShouldThrowExceptionWithEmptySet)
{
    std::set<const Point *> emptyPointsSet;
    ASSERT_ANY_THROW(new BoundingBox(emptyPointsSet));

    Point *points[] = {p0, p1, p2, p3, p4, p5};
    std::set<const Point *> pointsSet(points, points + 6);
    BoundingBox *boundingBox = new BoundingBox(pointsSet);
    ASSERT_ANY_THROW(boundingBox->calMaximumPoint(emptyPointsSet));
    ASSERT_ANY_THROW(boundingBox->calMinimumPoint(emptyPointsSet));
}

TEST_F(BoundingBoxTest, BoxesCollideShouldWorkAsExpected)
{
    Point *points1[] = {p0, p1, p2};
    Point *points2[] = {p3, p4, p5};
    std::set<const Point *> pointsSet1(points1, points1 + 3);
    std::set<const Point *> pointsSet2(points2, points2 + 3);
    BoundingBox *boundingBox1 = new BoundingBox(pointsSet1);
    BoundingBox *boundingBox2 = new BoundingBox(pointsSet2);

    ASSERT_TRUE(boundingBox1->collide(boundingBox2));
}

TEST_F(BoundingBoxTest, BoxesDoNotCollideShouldWorkAsExpected)
{
    Point *points1[] = {p1, p4};
    Point *points2[] = {p0, p2, p3, p5};
    std::set<const Point *> pointsSet1(points1, points1 + 2);
    std::set<const Point *> pointsSet2(points2, points2 + 4);
    BoundingBox *boundingBox1 = new BoundingBox(pointsSet1);
    BoundingBox *boundingBox2 = new BoundingBox(pointsSet2);

    ASSERT_FALSE(boundingBox1->collide(boundingBox2));
}