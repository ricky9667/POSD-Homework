#include "../../src/iterator/iterator.h"
#include "../../src/iterator/null_iterator.h"

class NullIteratorTest : public ::testing::Test
{
protected:
    Iterator *it;

    void SetUp() override
    {
        it = new NullIterator();
    }

    void TearDown() override
    {
        delete it;
    }
};

TEST_F(NullIteratorTest, testFirst)
{
    ASSERT_ANY_THROW(it->first());
}

TEST_F(NullIteratorTest, testCurrentItem)
{
    ASSERT_ANY_THROW(it->currentItem());
}

TEST_F(NullIteratorTest, testNext)
{
    ASSERT_ANY_THROW(it->next());
}

TEST_F(NullIteratorTest, testIsDone)
{
    ASSERT_TRUE(it->isDone());
}

