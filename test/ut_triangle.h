#include "../src/triangle.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"

class TriangleTest : public ::testing::Test
{
protected:
    Point *A, *B, *C, *D, *E, *F;
    TwoDimensionalVector *u, *v, *w, *e, *f;
    void SetUp() override
    {

        A = new Point(5, 8);
        B = new Point(10, 8);
        C = new Point(8, 11);
        D = new Point(7, 8);
        E = new Point(5, 11);
        F = new Point(6, 12);
        u = new TwoDimensionalVector(*A, *B);
        v = new TwoDimensionalVector(*A, *C);
        w = new TwoDimensionalVector(*C, *B);
        e = new TwoDimensionalVector(*A, *D);
        f = new TwoDimensionalVector(*E, *F);
    }

    void TearDown() override
    {
        delete A;
        delete B;
        delete C;
        delete D;
        delete E;
        delete F;
        delete u;
        delete v;
        delete w;
        delete e;
        delete f;
    }
};

TEST_F(TriangleTest, LegalTriangle)
{
    ASSERT_NO_THROW(Triangle(*v, *u));
    ASSERT_NO_THROW(Triangle(*v, *e));
    ASSERT_NO_THROW(Triangle(*v, *w));
    ASSERT_NO_THROW(Triangle(*w, *u));
}

TEST_F(TriangleTest, IllegalTriangle)
{
    // two vectors do not connect to each other
    ASSERT_ANY_THROW(Triangle(*v, *f));
    ASSERT_ANY_THROW(Triangle(*f, *v));
    ASSERT_ANY_THROW(Triangle(*w, *e));
    ASSERT_ANY_THROW(Triangle(*f, *w));
    // parallel vectors
    ASSERT_ANY_THROW(Triangle(*e, *u));
}

TEST_F(TriangleTest, AreaShouldBeCorrect)
{
    ASSERT_NEAR(7.5, Triangle(*v, *u).area(), 0.001);
    ASSERT_NEAR(7.5, Triangle(*u, *v).area(), 0.001);
    ASSERT_NEAR(7.5, Triangle(*w, *u).area(), 0.001);
    ASSERT_NEAR(7.5, Triangle(*v, *w).area(), 0.001);
}

TEST_F(TriangleTest, PerimeterShouldBeCorrect)
{
    ASSERT_NEAR(12.8481, Triangle(*v, *u).perimeter(), 0.001);
    ASSERT_NEAR(12.8481, Triangle(*u, *v).perimeter(), 0.001);
    ASSERT_NEAR(12.8481, Triangle(*w, *u).perimeter(), 0.001);
    ASSERT_NEAR(12.8481, Triangle(*v, *w).perimeter(), 0.001);
}

TEST_F(TriangleTest, InfoShouldBeCorrect)
{
    Triangle tri(*v, *u);
    ASSERT_EQ("Triangle (Vector ((5.00, 8.00), (8.00, 11.00)), Vector ((5.00, 8.00), (10.00, 8.00)))", tri.info());
}

// hw 2
TEST_F(TriangleTest, AddShapeShouldThrowException)
{
    Triangle tri(*v, *u);
    Shape *s = new Triangle(*v, *u);

    ASSERT_ANY_THROW(tri.addShape(s));

    delete s;
}

TEST_F(TriangleTest, DeleteShapeShouldThrowException)
{
    Triangle tri(*v, *u);
    Shape *s = new Triangle(*v, *u);

    ASSERT_ANY_THROW(tri.deleteShape(s));

    delete s;
}

TEST_F(TriangleTest, CurrentItemOfDFSIteratorShouldThrowException)
{
    Triangle tri(*v, *u);
    Iterator *it = tri.createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
}

TEST_F(TriangleTest, IsDoneOfDFSIteratorShouldReturnTrue)
{
    Triangle tri(*v, *u);
    Iterator *it = tri.createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_TRUE(it->isDone());

    delete it;
}

TEST_F(TriangleTest, CurrentItemOfBFSIteratorShouldThrowException)
{
    Triangle tri(*v, *u);
    Iterator *it = tri.createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
}

TEST_F(TriangleTest, IsDoneOfBFSIteratorShouldReturnTrue)
{
    Triangle tri(*v, *u);
    Iterator *it = tri.createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_TRUE(it->isDone());

    delete it;
}

// hw 3
TEST_F(TriangleTest, GetPointsShouldBeCorrect)
{
    Triangle tri(*v, *u);
    std::set<Point> points = tri.getPoints();
    ASSERT_TRUE(points.size() == 3);
    ASSERT_TRUE(points.find(*A) != points.end());
    ASSERT_TRUE(points.find(*B) != points.end());
    ASSERT_TRUE(points.find(*C) != points.end());
}


// #include <string>
// #include <set>
// #include "../src/point.h"
// #include "../src/two_dimensional_vector.h"
// #include "../src/triangle.h"
// #include "../src/iterator/factory/dfs_iterator_factory.h"
// #include "../src/iterator/factory/bfs_iterator_factory.h"
// #include "../src/iterator/factory/list_iterator_factory.h"
// #include "../src/visitor/shape_visitor.h"
// #include "../src/visitor/collision_detector.h"

// class TriangleTest : public ::testing::Test
// {
// protected:
//     Point *p0, *p1, *p2;
//     TwoDimensionalVector *v1, *v2;
//     Triangle *triangle;

//     void SetUp() override
//     {
//         p0 = new Point(0, 0);
//         p1 = new Point(3, 0);
//         p2 = new Point(3, 4);
//         v1 = new TwoDimensionalVector(p0, p1);
//         v2 = new TwoDimensionalVector(p2, p1);
//         triangle = new Triangle(v1, v2);
//     }

//     void TearDown() override
//     {
//         delete p0;
//         delete p1;
//         delete p2;
//         delete v1;
//         delete v2;
//         delete triangle;
//     }
// };

// TEST_F(TriangleTest, TriangleAreaCalculationShouldBeCorrect)
// {
//     ASSERT_NEAR(6, triangle->area(), 0.001);
// }

// TEST_F(TriangleTest, TrianglePerimeterCalculationShouldBeCorrect)
// {
//     ASSERT_NEAR(12, triangle->perimeter(), 0.001);
// }

// TEST_F(TriangleTest, TriangleInfoShouldWorkExpectedly)
// {
//     std::string expectedInfo = "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))";
//     ASSERT_EQ(expectedInfo, triangle->info());
// }

// TEST_F(TriangleTest, TriangleWithParallelVectorsShouldThrowExpection)
// {
//     TwoDimensionalVector *a = new TwoDimensionalVector(new Point(0, 0), new Point(3, 1));
//     TwoDimensionalVector *b = new TwoDimensionalVector(new Point(0, 0), new Point(6, 2));

//     ASSERT_ANY_THROW(new Triangle(a, b));
// }

// TEST_F(TriangleTest, DFSIterationInTriangleShouldThrowException)
// {
//     Iterator *iterator = triangle->createIterator(new DFSIteratorFactory());

//     ASSERT_ANY_THROW(iterator->currentItem());
//     ASSERT_ANY_THROW(iterator->next());
//     ASSERT_TRUE(iterator->isDone());
// }

// TEST_F(TriangleTest, BFSIteratorInTriangleShouldThrowException)
// {
//     Iterator *iterator = triangle->createIterator(new BFSIteratorFactory());

//     ASSERT_ANY_THROW(iterator->currentItem());
//     ASSERT_ANY_THROW(iterator->next());
//     ASSERT_TRUE(iterator->isDone());
// }

// TEST_F(TriangleTest, ListIteratorInTriangleShouldThrowException)
// {
//     Iterator *iterator = triangle->createIterator(new ListIteratorFactory());

//     ASSERT_ANY_THROW(iterator->currentItem());
//     ASSERT_ANY_THROW(iterator->next());
//     ASSERT_TRUE(iterator->isDone());
// }

// TEST_F(TriangleTest, AddShapeShouldThrowException)
// {
//     Triangle *other = new Triangle(
//         new TwoDimensionalVector(new Point(0, 0), new Point(-3, 7.2)),
//         new TwoDimensionalVector(new Point(0, 0), new Point(4.54, -1)));

//     ASSERT_ANY_THROW(triangle->addShape(other));
// }

// TEST_F(TriangleTest, DeleteShapeShouldThrowException)
// {
//     Triangle *other = new Triangle(
//         new TwoDimensionalVector(new Point(0, 0), new Point(-3, 7.2)),
//         new TwoDimensionalVector(new Point(0, 0), new Point(4.54, -1)));

//     ASSERT_ANY_THROW(triangle->deleteShape(other));
// }

// TEST_F(TriangleTest, GetPoints)
// {
//     std::set<const Point *> points = triangle->getPoints();

//     ASSERT_EQ(3, points.size());
// }

// TEST_F(TriangleTest, AcceptDoesNotThrowException)
// {
//     Triangle *other = new Triangle(
//         new TwoDimensionalVector(new Point(0, 0), new Point(-3, 7.2)),
//         new TwoDimensionalVector(new Point(0, 0), new Point(4.54, -1)));

//     ShapeVisitor *collisionDetector = new CollisionDetector(other);
//     ASSERT_NO_THROW(triangle->accept(collisionDetector));

//     delete other;
// }
