#include <string>
#include <set>
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/rectangle.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"
#include "../src/iterator/factory/list_iterator_factory.h"
#include "../src/visitor/shape_visitor.h"
#include "../src/visitor/collision_detector.h"

class RectangleTest : public ::testing::Test
{
protected:
    Point *p1, *p2, *p3;
    TwoDimensionalVector *lengthVector, *widthVector;
    Rectangle *rectangle;

    void SetUp() override
    {
        p1 = new Point(-2, 1);
        p2 = new Point(1.5, 0.47);
        p3 = new Point(-1.47, 4.5);
        lengthVector = new TwoDimensionalVector(p1, p2);
        widthVector = new TwoDimensionalVector(p1, p3);
        rectangle = new Rectangle(lengthVector, widthVector);
    }

    void TearDown() override
    {
        delete p1;
        delete p2;
        delete p3;
        delete lengthVector;
        delete widthVector;
        delete rectangle;
    }
};

TEST_F(RectangleTest, RectangleGettersShouldWorkExpectedly)
{
    ASSERT_EQ(lengthVector->length(), rectangle->length());
    ASSERT_EQ(widthVector->length(), rectangle->width());
}

TEST_F(RectangleTest, RectangleAreaCalculationShouldBeCorrect)
{
    ASSERT_NEAR(12.5309, rectangle->area(), 0.001);
}

TEST_F(RectangleTest, RectanglePerimeterCalculationShouldBeCorrect)
{
    ASSERT_NEAR(14.1596, rectangle->perimeter(), 0.001);
}

TEST_F(RectangleTest, RectangleInfoShouldWorkExpectedly)
{
    std::string expectedInfo = "Rectangle (Vector ((-2.00, 1.00), (1.50, 0.47)), Vector ((-2.00, 1.00), (-1.47, 4.50)))";
    ASSERT_EQ(expectedInfo, rectangle->info());
}

TEST_F(RectangleTest, RectangleWithNonOrthogonalVectorsShouldThrowException)
{
    TwoDimensionalVector *lengthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(-2, 5));
    TwoDimensionalVector *widthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(-7, 2));

    ASSERT_ANY_THROW(new Rectangle(lengthVector, widthVector));
}

TEST_F(RectangleTest, DFSIterationInRectangleShouldThrowException)
{
    Iterator *iterator = rectangle->createIterator(new DFSIteratorFactory());

    ASSERT_ANY_THROW(iterator->currentItem());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_TRUE(iterator->isDone());
}

TEST_F(RectangleTest, BFSIteratorInRectangleShouldThrowException)
{
    Iterator *iterator = rectangle->createIterator(new BFSIteratorFactory());

    ASSERT_ANY_THROW(iterator->currentItem());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_TRUE(iterator->isDone());
}

TEST_F(RectangleTest, ListIteratorInRectangleShouldThrowException)
{
    Iterator *iterator = rectangle->createIterator(new ListIteratorFactory());

    ASSERT_ANY_THROW(iterator->currentItem());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_TRUE(iterator->isDone());
}

TEST_F(RectangleTest, AddShapeShouldThrowException)
{
    Rectangle *other = new Rectangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(6, 6)),
        new TwoDimensionalVector(new Point(0, 0), new Point(-3, 3)));

    ASSERT_ANY_THROW(rectangle->addShape(other));
}

TEST_F(RectangleTest, DeleteShapeShouldThrowException)
{
    Rectangle *other = new Rectangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(6, 6)),
        new TwoDimensionalVector(new Point(0, 0), new Point(-3, 3)));

    ASSERT_ANY_THROW(rectangle->deleteShape(other));
}

TEST_F(RectangleTest, GetPoints)
{
    std::set<const Point *> points = rectangle->getPoints();

    ASSERT_EQ(4, points.size());
}

TEST_F(RectangleTest, AcceptDoesNotThrowException)
{
    Rectangle *other = new Rectangle(
        new TwoDimensionalVector(new Point(0, 0), new Point(6, 6)),
        new TwoDimensionalVector(new Point(0, 0), new Point(-3, 3)));

    ShapeVisitor *collisionDetector = new CollisionDetector(other);
    ASSERT_NO_THROW(rectangle->accept(collisionDetector));

    delete other;
}
