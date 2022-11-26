#include "../../../src/iterator/factory/iterator_factory.h"

class IteratorFactoryTest : public ::testing::Test
{
protected:
    void SetUp() {}

    void TearDown() {}
};

TEST_F(IteratorFactoryTest, DFSFactoryShouldReturnSameInstance)
{
    IteratorFactory *expectedFactory = IteratorFactory::getInstance("DFS");
    IteratorFactory *resultFactory = IteratorFactory::getInstance("DFS");

    ASSERT_EQ(expectedFactory, resultFactory);
}

TEST_F(IteratorFactoryTest, BFSFactoryShouldReturnSameInstance)
{
    IteratorFactory *expectedFactory = IteratorFactory::getInstance("BFS");
    IteratorFactory *resultFactory = IteratorFactory::getInstance("BFS");

    ASSERT_EQ(expectedFactory, resultFactory);
}

TEST_F(IteratorFactoryTest, ListFactoryShouldReturnSameInstance)
{
    IteratorFactory *expectedFactory = IteratorFactory::getInstance("List");
    IteratorFactory *resultFactory = IteratorFactory::getInstance("List");

    ASSERT_EQ(expectedFactory, resultFactory);
}
