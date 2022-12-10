#include "../src/rectangle.h"
#include "../src/iterator/iterator.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"

class RectangleTest : public ::testing::Test
{
protected:
    Point *E, *F, *I, *J, *G, *H;
    TwoDimensionalVector *k, *l, *m, *n, *f;
    void SetUp() override
    {
        I = new Point(20, 13);
        J = new Point(16, 14);
        G = new Point(15, 10);
        H = new Point(19, 9);
        E = new Point(5, 11);
        F = new Point(6, 12);
        k = new TwoDimensionalVector(*I, *J);
        l = new TwoDimensionalVector(*J, *G);
        m = new TwoDimensionalVector(*G, *H);
        n = new TwoDimensionalVector(*H, *I);
        f = new TwoDimensionalVector(*E, *F);
    }

    void TearDown() override
    {
        delete E;
        delete F;
        delete I;
        delete J;
        delete G;
        delete H;
        delete f;
        delete k;
        delete l;
        delete m;
        delete n;
    }
};

TEST_F(RectangleTest, LegalRectangle)
{
    ASSERT_NO_THROW(Rectangle(*k, *l));
    ASSERT_NO_THROW(Rectangle(*l, *m));
    ASSERT_NO_THROW(Rectangle(*m, *n));
    ASSERT_NO_THROW(Rectangle(*n, *k));
}

TEST_F(RectangleTest, IllegalRectangle)
{
    ASSERT_ANY_THROW(Rectangle(*l, *n));
    ASSERT_ANY_THROW(Rectangle(*k, *m));
    ASSERT_ANY_THROW(Rectangle(*f, *k));
    ASSERT_ANY_THROW(Rectangle(*l, *f));
}

TEST_F(RectangleTest, LengthShouldBeCorrect)
{
    ASSERT_NEAR(k->length(), Rectangle(*k, *l).length(), 0.001);
    ASSERT_NEAR(n->length(), Rectangle(*n, *m).length(), 0.001);
}

TEST_F(RectangleTest, WidthShouldBeCorrect)
{
    ASSERT_NEAR(l->length(), Rectangle(*k, *l).width(), 0.001);
    ASSERT_NEAR(m->length(), Rectangle(*n, *m).width(), 0.001);
}

TEST_F(RectangleTest, AreaShouldBeCorrect)
{
    ASSERT_NEAR(17, Rectangle(*k, *l).area(), 0.001);
    ASSERT_NEAR(17, Rectangle(*n, *m).area(), 0.001);
}

TEST_F(RectangleTest, PerimeterShouldBeCorrect)
{
    ASSERT_NEAR(16.4924, Rectangle(*k, *l).perimeter(), 0.001);
    ASSERT_NEAR(16.4924, Rectangle(*n, *m).perimeter(), 0.001);
}

TEST_F(RectangleTest, InfoShouldBeCorrect)
{
    Rectangle rec(*k, *l);
    ASSERT_EQ("Rectangle (Vector ((20.00, 13.00), (16.00, 14.00)), Vector ((16.00, 14.00), (15.00, 10.00)))", rec.info());
}

// hw 2
TEST_F(RectangleTest, AddShapeShouldThrowException)
{
    Rectangle rec(*k, *l);
    Shape *s = new Rectangle(*k, *l);

    ASSERT_ANY_THROW(rec.addShape(s));

    delete s;
}

TEST_F(RectangleTest, DeleteShapeShouldThrowException)
{
    Rectangle rec(*k, *l);
    Shape *s = new Rectangle(*k, *l);

    ASSERT_ANY_THROW(rec.deleteShape(s));

    delete s;
}

TEST_F(RectangleTest, CurrentItemOfDFSIteratorShouldThrowException)
{
    Rectangle rec(*k, *l);
    Iterator *it = rec.createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
}

TEST_F(RectangleTest, IsDoneOfDFSIteratorShouldReturnTrue)
{
    Rectangle rec(*k, *l);
    Iterator *it = rec.createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_TRUE(it->isDone());

    delete it;
}

TEST_F(RectangleTest, CurrentItemOfBFSIteratorShouldThrowException)
{
    Rectangle rec(*k, *l);
    Iterator *it = rec.createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_ANY_THROW(it->currentItem());

    delete it;
}

TEST_F(RectangleTest, IsDoneOfBFSIteratorShouldReturnTrue)
{
    Rectangle rec(*k, *l);
    Iterator *it = rec.createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_TRUE(it->isDone());

    delete it;
}

// hw 3
TEST_F(RectangleTest, GetPointsShouldBeCorrect)
{
    Rectangle rec(*k, *l);
    std::set<Point> points = rec.getPoints();
    ASSERT_TRUE(points.size() == 4);
    ASSERT_TRUE(points.find(*J) != points.end());
    ASSERT_TRUE(points.find(*I) != points.end());
    ASSERT_TRUE(points.find(*G) != points.end());
    ASSERT_TRUE(points.find(*H) != points.end());
}

// TEST_F(RectangleTest, FindFourthVertexShouldBeCorrect)
// {
//     Point *K = new Point(0, -1);
//     Point *U = new Point(-1, -2);
//     Point *M = new Point(0, -3);
//     Point *N = new Point(1, -2);
//     Rectangle *dummy_rect = new Rectangle(
//         new TwoDimensionalVector(K, U),
//         new TwoDimensionalVector(K, N));
//     ASSERT_EQ(
//         *(dummy_rect->findFourthVertex(
//             new TwoDimensionalVector(K, U),
//             new TwoDimensionalVector(K, N))),
//         *M);
//     ASSERT_EQ(
//         *(dummy_rect->findFourthVertex(
//             new TwoDimensionalVector(M, U),
//             new TwoDimensionalVector(U, K))),
//         *N);
//     ASSERT_EQ(
//         *(dummy_rect->findFourthVertex(
//             new TwoDimensionalVector(K, N),
//             new TwoDimensionalVector(M, N))),
//         *U);
//     ASSERT_EQ(
//         *(dummy_rect->findFourthVertex(
//             new TwoDimensionalVector(N, M),
//             new TwoDimensionalVector(K, N))),
//         *U);
//     delete dummy_rect;
//     delete K;
//     delete U;
//     delete M;
//     delete N;
// }


// #include <string>
// #include <set>
// #include "../src/point.h"
// #include "../src/two_dimensional_vector.h"
// #include "../src/rectangle.h"
// #include "../src/iterator/factory/dfs_iterator_factory.h"
// #include "../src/iterator/factory/bfs_iterator_factory.h"
// #include "../src/iterator/factory/list_iterator_factory.h"
// #include "../src/visitor/shape_visitor.h"
// #include "../src/visitor/collision_detector.h"

// class RectangleTest : public ::testing::Test
// {
// protected:
//     Point *p1, *p2, *p3;
//     TwoDimensionalVector *lengthVector, *widthVector;
//     Rectangle *rectangle;

//     void SetUp() override
//     {
//         p1 = new Point(-2, 1);
//         p2 = new Point(1.5, 0.47);
//         p3 = new Point(-1.47, 4.5);
//         lengthVector = new TwoDimensionalVector(p1, p2);
//         widthVector = new TwoDimensionalVector(p1, p3);
//         rectangle = new Rectangle(lengthVector, widthVector);
//     }

//     void TearDown() override
//     {
//         delete p1;
//         delete p2;
//         delete p3;
//         delete lengthVector;
//         delete widthVector;
//         delete rectangle;
//     }
// };

// TEST_F(RectangleTest, RectangleGettersShouldWorkExpectedly)
// {
//     ASSERT_EQ(lengthVector->length(), rectangle->length());
//     ASSERT_EQ(widthVector->length(), rectangle->width());
// }

// TEST_F(RectangleTest, RectangleAreaCalculationShouldBeCorrect)
// {
//     ASSERT_NEAR(12.5309, rectangle->area(), 0.001);
// }

// TEST_F(RectangleTest, RectanglePerimeterCalculationShouldBeCorrect)
// {
//     ASSERT_NEAR(14.1596, rectangle->perimeter(), 0.001);
// }

// TEST_F(RectangleTest, RectangleInfoShouldWorkExpectedly)
// {
//     std::string expectedInfo = "Rectangle (Vector ((-2.00, 1.00), (1.50, 0.47)), Vector ((-2.00, 1.00), (-1.47, 4.50)))";
//     ASSERT_EQ(expectedInfo, rectangle->info());
// }

// TEST_F(RectangleTest, RectangleWithNonOrthogonalVectorsShouldThrowException)
// {
//     TwoDimensionalVector *lengthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(-2, 5));
//     TwoDimensionalVector *widthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(-7, 2));

//     ASSERT_ANY_THROW(new Rectangle(lengthVector, widthVector));
// }

// TEST_F(RectangleTest, DFSIterationInRectangleShouldThrowException)
// {
//     Iterator *iterator = rectangle->createIterator(new DFSIteratorFactory());

//     ASSERT_ANY_THROW(iterator->currentItem());
//     ASSERT_ANY_THROW(iterator->next());
//     ASSERT_TRUE(iterator->isDone());
// }

// TEST_F(RectangleTest, BFSIteratorInRectangleShouldThrowException)
// {
//     Iterator *iterator = rectangle->createIterator(new BFSIteratorFactory());

//     ASSERT_ANY_THROW(iterator->currentItem());
//     ASSERT_ANY_THROW(iterator->next());
//     ASSERT_TRUE(iterator->isDone());
// }

// TEST_F(RectangleTest, ListIteratorInRectangleShouldThrowException)
// {
//     Iterator *iterator = rectangle->createIterator(new ListIteratorFactory());

//     ASSERT_ANY_THROW(iterator->currentItem());
//     ASSERT_ANY_THROW(iterator->next());
//     ASSERT_TRUE(iterator->isDone());
// }

// TEST_F(RectangleTest, AddShapeShouldThrowException)
// {
//     Rectangle *other = new Rectangle(
//         new TwoDimensionalVector(new Point(0, 0), new Point(6, 6)),
//         new TwoDimensionalVector(new Point(0, 0), new Point(-3, 3)));

//     ASSERT_ANY_THROW(rectangle->addShape(other));
// }

// TEST_F(RectangleTest, DeleteShapeShouldThrowException)
// {
//     Rectangle *other = new Rectangle(
//         new TwoDimensionalVector(new Point(0, 0), new Point(6, 6)),
//         new TwoDimensionalVector(new Point(0, 0), new Point(-3, 3)));

//     ASSERT_ANY_THROW(rectangle->deleteShape(other));
// }

// TEST_F(RectangleTest, GetPoints)
// {
//     std::set<const Point *> points = rectangle->getPoints();

//     ASSERT_EQ(4, points.size());
// }

// TEST_F(RectangleTest, AcceptDoesNotThrowException)
// {
//     Rectangle *other = new Rectangle(
//         new TwoDimensionalVector(new Point(0, 0), new Point(6, 6)),
//         new TwoDimensionalVector(new Point(0, 0), new Point(-3, 3)));

//     ShapeVisitor *collisionDetector = new CollisionDetector(other);
//     ASSERT_NO_THROW(rectangle->accept(collisionDetector));

//     delete other;
// }
