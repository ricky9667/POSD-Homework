#include <set>
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/circle.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"
#include "../src/visitor/shape_visitor.h"
#include "../src/visitor/collision_detector.h"

class CircleTest : public ::testing::Test
{
protected:
    Point *p1, *p2;
    TwoDimensionalVector *vector;
    Circle *circle;

    void SetUp() override
    {
        p1 = new Point(-4.284, 0.264);
        p2 = new Point(-4.827, 0.728);
        vector = new TwoDimensionalVector(p1, p2);
        circle = new Circle(vector);
    }

    void TearDown() override
    {
        delete p1;
        delete p2;
        delete vector;
        delete circle;
    }
};

TEST_F(CircleTest, testCircleRadius)
{
    ASSERT_NEAR(vector->length(), circle->radius(), 0.001);
}

TEST_F(CircleTest, testCircleArea)
{
    TwoDimensionalVector *vector = new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728));
    Circle *circle = new Circle(vector);

    ASSERT_NEAR(1.6027, circle->area(), 0.001);
}

TEST_F(CircleTest, testCirclePerimeter)
{
    TwoDimensionalVector *vector = new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728));
    Circle *circle = new Circle(vector);

    ASSERT_NEAR(4.4877, circle->perimeter(), 0.001);
}

TEST_F(CircleTest, testCircleInfo)
{
    TwoDimensionalVector *vector = new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728));
    Circle *circle = new Circle(vector);

    std::string expectedInfo = "Circle (Vector ((-4.28, 0.26), (-4.83, 0.73)))";
    ASSERT_EQ(expectedInfo, circle->info());
}

TEST_F(CircleTest, testCreateDFSIterator)
{
    Iterator *iterator = circle->createIterator(new DFSIteratorFactory());

    ASSERT_ANY_THROW(iterator->currentItem());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_TRUE(iterator->isDone());
}

TEST_F(CircleTest, testCreateBFSIterator)
{
    Iterator *iterator = circle->createIterator(new BFSIteratorFactory());

    ASSERT_ANY_THROW(iterator->currentItem());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_TRUE(iterator->isDone());
}

TEST_F(CircleTest, AddShapeShouldThrowException)
{
    Circle *other = new Circle(
        new TwoDimensionalVector(new Point(0, 0), new Point(3, 7)));

    ASSERT_ANY_THROW(circle->addShape(other));
}

TEST_F(CircleTest, DeleteShapeShouldThrowException)
{
    Circle *other = new Circle(
        new TwoDimensionalVector(new Point(0, 0), new Point(3, 7)));

    ASSERT_ANY_THROW(circle->deleteShape(other));
}

TEST_F(CircleTest, GetPoints)
{
    std::set<const Point *> points = circle->getPoints();

    ASSERT_EQ(2, points.size());
}

TEST_F(CircleTest, AcceptDoesNotThrowException)
{
    Circle *other = new Circle(
        new TwoDimensionalVector(new Point(0, 0), new Point(3, 7)));

    ShapeVisitor *collisionDetector = new CollisionDetector(other);
    ASSERT_NO_THROW(circle->accept(collisionDetector));

    delete other;
}
