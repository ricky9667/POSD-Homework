#include <string>
#include <set>
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/triangle.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"
#include "../src/iterator/factory/list_iterator_factory.h"
#include "../src/visitor/shape_visitor.h"
#include "../src/visitor/collision_detector.h"

class TriangleTest : public ::testing::Test
{
protected:
    Point *p0, *p1, *p2;
    TwoDimensionalVector *v1, *v2;
    Triangle *triangle;

    void SetUp() override
    {
        p0 = new Point(0, 0);
        p1 = new Point(3, 0);
        p2 = new Point(3, 4);
        v1 = new TwoDimensionalVector(p0, p1);
        v2 = new TwoDimensionalVector(p2, p1);
        triangle = new Triangle(v1, v2);
    }

    void TearDown() override
    {
        delete p0;
        delete p1;
        delete p2;
        delete v1;
        delete v2;
        delete triangle;
    }
};

TEST_F(TriangleTest, TriangleAreaCalculationShouldBeCorrect)
{
    ASSERT_NEAR(6, triangle->area(), 0.001);
}

TEST_F(TriangleTest, TrianglePerimeterCalculationShouldBeCorrect)
{
    ASSERT_NEAR(12, triangle->perimeter(), 0.001);
}

TEST_F(TriangleTest, TriangleInfoShouldWorkExpectedly)
{
    std::string expectedInfo = "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))";
    ASSERT_EQ(expectedInfo, triangle->info());
}

TEST_F(TriangleTest, TriangleWithParallelVectorsShouldThrowExpection)
{
    TwoDimensionalVector *a = new TwoDimensionalVector(new Point(0, 0), new Point(3, 1));
    TwoDimensionalVector *b = new TwoDimensionalVector(new Point(0, 0), new Point(6, 2));

    ASSERT_ANY_THROW(new Triangle(a, b));
}

TEST_F(TriangleTest, DFSIterationInTriangleShouldThrowException)
{
    Iterator *iterator = triangle->createIterator(new DFSIteratorFactory());

    ASSERT_ANY_THROW(iterator->currentItem());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_TRUE(iterator->isDone());
}

TEST_F(TriangleTest, BFSIteratorInTriangleShouldThrowException)
{
    Iterator *iterator = triangle->createIterator(new BFSIteratorFactory());

    ASSERT_ANY_THROW(iterator->currentItem());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_TRUE(iterator->isDone());
}

TEST_F(TriangleTest, ListIteratorInTriangleShouldThrowException)
{
    Iterator *iterator = triangle->createIterator(new ListIteratorFactory());

    ASSERT_ANY_THROW(iterator->currentItem());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_TRUE(iterator->isDone());
}

TEST_F(TriangleTest, AddShapeShouldThrowException)
{
    Triangle *other = new Triangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(-3, 7.2)),
        new TwoDimensionalVector(new Point(0, 0), new Point(4.54, -1)));

    ASSERT_ANY_THROW(triangle->addShape(other));
}

TEST_F(TriangleTest, DeleteShapeShouldThrowException)
{
    Triangle *other = new Triangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(-3, 7.2)),
        new TwoDimensionalVector(new Point(0, 0), new Point(4.54, -1)));

    ASSERT_ANY_THROW(triangle->deleteShape(other));
}

TEST_F(TriangleTest, GetPoints)
{
    std::set<const Point *> points = triangle->getPoints();

    ASSERT_EQ(3, points.size());
}

TEST_F(TriangleTest, AcceptDoesNotThrowException)
{
    Triangle *other = new Triangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(-3, 7.2)),
        new TwoDimensionalVector(new Point(0, 0), new Point(4.54, -1)));

    ShapeVisitor *collisionDetector = new CollisionDetector(other);
    ASSERT_NO_THROW(triangle->accept(collisionDetector));

    delete other;
}
