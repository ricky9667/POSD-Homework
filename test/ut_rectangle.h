#include <string>
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/rectangle.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"

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

TEST_F(RectangleTest, testRectangleGetters)
{
    ASSERT_EQ(lengthVector->length(), rectangle->length());
    ASSERT_EQ(widthVector->length(), rectangle->width());
}

TEST_F(RectangleTest, testRectangleArea)
{
    ASSERT_NEAR(12.5309, rectangle->area(), 0.001);
}

TEST_F(RectangleTest, testRectanglePerimeter)
{
    ASSERT_NEAR(14.1596, rectangle->perimeter(), 0.001);
}

TEST_F(RectangleTest, testRectangleInfo)
{
    std::string expectedInfo = "Rectangle (Vector ((-2.00, 1.00), (1.50, 0.47)), Vector ((-2.00, 1.00), (-1.47, 4.50)))";
    ASSERT_EQ(expectedInfo, rectangle->info());
}

TEST_F(RectangleTest, testRectangleNotOrthogonal)
{
    TwoDimensionalVector *lengthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(-2, 5));
    TwoDimensionalVector *widthVector = new TwoDimensionalVector(new Point(-2, 1), new Point(-7, 2));

    ASSERT_ANY_THROW(new Rectangle(lengthVector, widthVector));
}

TEST_F(RectangleTest, testCreateDFSIterator)
{
    Iterator *iterator = rectangle->createIterator(new DFSIteratorFactory());

    ASSERT_ANY_THROW(iterator->currentItem());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_TRUE(iterator->isDone());
}

TEST_F(RectangleTest, testCreateBFSIterator)
{
    Iterator *iterator = rectangle->createIterator(new BFSIteratorFactory());

    ASSERT_ANY_THROW(iterator->currentItem());
    ASSERT_ANY_THROW(iterator->next());
    ASSERT_TRUE(iterator->isDone());
}
