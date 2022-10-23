#include <string>
#include <set>
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/triangle.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"

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

TEST_F(TriangleTest, testTriangleArea)
{
    ASSERT_NEAR(6, triangle->area(), 0.001);
}

TEST_F(TriangleTest, testTrianglePerimeter)
{
    ASSERT_NEAR(12, triangle->perimeter(), 0.001);
}

TEST_F(TriangleTest, testTriangleInfo)
{
    std::string expectedInfo = "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))";
    ASSERT_EQ(expectedInfo, triangle->info());
}

TEST_F(TriangleTest, testTriangleParallel)
{
    TwoDimensionalVector *a = new TwoDimensionalVector(new Point(0, 0), new Point(3, 1));
    TwoDimensionalVector *b = new TwoDimensionalVector(new Point(0, 0), new Point(6, 2));

    ASSERT_ANY_THROW(new Triangle(a, b));
}

TEST_F(TriangleTest, testCreateDFSIterator)
{
    Iterator *iterator = triangle->createIterator(new DFSIteratorFactory());

    ASSERT_ANY_THROW(iterator->currentItem());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_TRUE(iterator->isDone());
}

TEST_F(TriangleTest, testCreateBFSIterator)
{
    Iterator *iterator = triangle->createIterator(new BFSIteratorFactory());

    ASSERT_ANY_THROW(iterator->currentItem());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_TRUE(iterator->isDone());
}

TEST_F(TriangleTest, GetPoints)
{
    std::set<const Point *> points = triangle->getPoints();

    ASSERT_EQ(3, points.size());
    // ASSERT_FALSE(points.find(p0) == points.end());
    // ASSERT_FALSE(points.find(p1) == points.end());
    // ASSERT_FALSE(points.find(p2) == points.end());
    ASSERT_TRUE(points.find(new Point(10, 3)) == points.end());
}
