#include <cmath>
#include "../src/circle.h"
#include "../src/iterator/iterator.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"

class CircleTest : public ::testing::Test
{
protected:
    Point *K, *L;
    TwoDimensionalVector *r;

    void SetUp() override
    {
        K = new Point(14, 2);
        L = new Point(18, -4);
        r = new TwoDimensionalVector(*K, *L);
    }

    void TearDown() override
    {
        delete K;
        delete L;
        delete r;
    }
};

TEST_F(CircleTest, LegalCircle)
{
    ASSERT_NO_THROW(Circle cir(*r));
}

TEST_F(CircleTest, RadiusShouldBeCorrect)
{
    ASSERT_NEAR(7.2111, Circle(*r).radius(), 0.001);
}

TEST_F(CircleTest, AreaShouldBeCorrect)
{
    ASSERT_NEAR(pow(7.2111, 2) * M_PI, Circle(*r).area(), 0.001);
}

TEST_F(CircleTest, PerimeterShouldBeCorrect)
{
    ASSERT_NEAR(2 * M_PI * 7.2111, Circle(*r).perimeter(), 0.001);
}

TEST_F(CircleTest, InfoShouldBeCorrect)
{
    Circle cir(*r);
    ASSERT_EQ("Circle (Vector ((14.00, 2.00), (18.00, -4.00)))", cir.info());
}

// hw 2
TEST_F(CircleTest, AddShapeShouldThrowException)
{
    Circle cir(*r);
    Shape *s = new Circle(*r);

    ASSERT_ANY_THROW(cir.addShape(s));

    delete s;
}

TEST_F(CircleTest, DeleteShapeShouldThrowException)
{
    Circle cir(*r);
    Shape *s = new Circle(*r);

    ASSERT_ANY_THROW(cir.deleteShape(s));

    delete s;
}

TEST_F(CircleTest, CurrentItemOfDFSIteratorShouldThrowException)
{
    Circle cir(*r);
    Iterator *it = cir.createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
}

TEST_F(CircleTest, IsDoneOfDFSIteratorShouldReturnTrue)
{
    Circle cir(*r);
    Iterator *it = cir.createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_TRUE(it->isDone());

    delete it;
}

TEST_F(CircleTest, CurrentItemOfBFSIteratorShouldThrowException)
{
    Circle cir(*r);
    Iterator *it = cir.createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
}

TEST_F(CircleTest, IsDoneOfBFSIteratorShouldReturnTrue)
{
    Circle cir(*r);
    Iterator *it = cir.createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_TRUE(it->isDone());

    delete it;
}

// hw 3
TEST_F(CircleTest, getPointsShouldBeCorrect)
{
    double radius = r->length();
    Circle cir(*r);
    std::set<Point> points = cir.getPoints();
    ASSERT_TRUE(points.size() == 2);
    Point pMax(K->x() + radius, K->y() + radius);
    Point pMin(K->x() - radius, K->y() - radius);
    ASSERT_TRUE(points.find(pMax) != points.end());
    ASSERT_TRUE(points.find(pMin) != points.end());
    Point lowerright(K->x() + radius, K->y() - radius);
    Point upperleft(K->x() - radius, K->y() + radius);
    ASSERT_TRUE(points.find(lowerright) == points.end());
    ASSERT_TRUE(points.find(upperleft) == points.end());
}


// #include <set>
// #include "../src/point.h"
// #include "../src/two_dimensional_vector.h"
// #include "../src/circle.h"
// #include "../src/iterator/factory/dfs_iterator_factory.h"
// #include "../src/iterator/factory/bfs_iterator_factory.h"
// #include "../src/iterator/factory/list_iterator_factory.h"
// #include "../src/visitor/shape_visitor.h"
// #include "../src/visitor/collision_detector.h"

// class CircleTest : public ::testing::Test
// {
// protected:
//     Point *p1, *p2;
//     TwoDimensionalVector *vector;
//     Circle *circle;

//     void SetUp() override
//     {
//         p1 = new Point(-4.284, 0.264);
//         p2 = new Point(-4.827, 0.728);
//         vector = new TwoDimensionalVector(p1, p2);
//         circle = new Circle(vector);
//     }

//     void TearDown() override
//     {
//         delete p1;
//         delete p2;
//         delete vector;
//         delete circle;
//     }
// };

// TEST_F(CircleTest, CircleRadiusShouldBeCorrect)
// {
//     ASSERT_NEAR(vector->length(), circle->radius(), 0.001);
// }

// TEST_F(CircleTest, CircleAreaCalculationShouldBeCorrect)
// {
//     TwoDimensionalVector *vector = new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728));
//     Circle *circle = new Circle(vector);

//     ASSERT_NEAR(1.6027, circle->area(), 0.001);
// }

// TEST_F(CircleTest, CirclePerimeterCalculationShouldBeCorrect)
// {
//     TwoDimensionalVector *vector = new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728));
//     Circle *circle = new Circle(vector);

//     ASSERT_NEAR(4.4877, circle->perimeter(), 0.001);
// }

// TEST_F(CircleTest, CircleInfoShouldWorkExpectedly)
// {
//     TwoDimensionalVector *vector = new TwoDimensionalVector(new Point(-4.284, 0.264), new Point(-4.827, 0.728));
//     Circle *circle = new Circle(vector);

//     std::string expectedInfo = "Circle (Vector ((-4.28, 0.26), (-4.83, 0.73)))";
//     ASSERT_EQ(expectedInfo, circle->info());
// }

// TEST_F(CircleTest, DFSIterationInCircleShouldThrowException)
// {
//     Iterator *iterator = circle->createIterator(new DFSIteratorFactory());

//     ASSERT_ANY_THROW(iterator->currentItem());
//     ASSERT_ANY_THROW(iterator->next());
//     ASSERT_TRUE(iterator->isDone());
// }

// TEST_F(CircleTest, BFSIterationInCircleShouldThrowException)
// {
//     Iterator *iterator = circle->createIterator(new BFSIteratorFactory());

//     ASSERT_ANY_THROW(iterator->currentItem());
//     ASSERT_ANY_THROW(iterator->next());
//     ASSERT_TRUE(iterator->isDone());
// }

// TEST_F(CircleTest, ListIterationInCircleShouldThrowException)
// {
//     Iterator *iterator = circle->createIterator(new ListIteratorFactory());

//     ASSERT_ANY_THROW(iterator->currentItem());
//     ASSERT_ANY_THROW(iterator->next());
//     ASSERT_TRUE(iterator->isDone());
// }

// TEST_F(CircleTest, AddShapeShouldThrowException)
// {
//     Circle *other = new Circle(
//         new TwoDimensionalVector(new Point(0, 0), new Point(3, 7)));

//     ASSERT_ANY_THROW(circle->addShape(other));
// }

// TEST_F(CircleTest, DeleteShapeShouldThrowException)
// {
//     Circle *other = new Circle(
//         new TwoDimensionalVector(new Point(0, 0), new Point(3, 7)));

//     ASSERT_ANY_THROW(circle->deleteShape(other));
// }

// TEST_F(CircleTest, GetPoints)
// {
//     std::set<const Point *> points = circle->getPoints();

//     ASSERT_EQ(2, points.size());
// }

// TEST_F(CircleTest, AcceptDoesNotThrowException)
// {
//     Circle *other = new Circle(
//         new TwoDimensionalVector(new Point(0, 0), new Point(3, 7)));

//     ShapeVisitor *collisionDetector = new CollisionDetector(other);
//     ASSERT_NO_THROW(circle->accept(collisionDetector));

//     delete other;
// }
