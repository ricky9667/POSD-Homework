#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/circle.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"

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
