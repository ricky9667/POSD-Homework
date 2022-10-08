#include "../../src/iterator/iterator.h"
#include "../../src/iterator/dfs_compound_iterator.h"
#include "../../src/compound_shape.h"

class DFSCompoundIteratorTest : public ::testing::Test
{
protected:
    Point *p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9, *p10, *p11, *p12;
    TwoDimensionalVector *v1, *v2, *v3, *v4, *v5, *v6;
    Triangle *t1;
    Rectangle *r1;
    Circle *c1, *c2;
    CompoundShape *com1, *com2, *com3;

    void SetUp() override
    {
        p0 = new Point(0, 0);
        p1 = new Point(8, 2);
        p2 = new Point(0, 0);
        p3 = new Point(2, 0);
        p4 = new Point(2, 2);
        p5 = new Point(3, 2);
        p6 = new Point(2, 2);
        p7 = new Point(2, 7);
        p8 = new Point(2, 6);
        p9 = new Point(1, 6);
        p10 = new Point(8, 5);
        p11 = new Point(-1, -1);
        v1 = new TwoDimensionalVector(p0, p1);
        v2 = new TwoDimensionalVector(p2, p3);
        v3 = new TwoDimensionalVector(p4, p5);
        v4 = new TwoDimensionalVector(p6, p7);
        v5 = new TwoDimensionalVector(p8, p9);
        v6 = new TwoDimensionalVector(p10, p11);
        t1 = new Triangle(v1, v2);
        r1 = new Rectangle(v3, v4);
        c1 = new Circle(v5);
        c2 = new Circle(v6);

        Shape* shapes2[] = {t1};
        com2 = new CompoundShape(shapes2, 1);
        Shape* shapes3[] = {r1, c1, c2};
        com3 = new CompoundShape(shapes3, 3);
        Shape* shapes1[] = {com2, com3};
        com1 = new CompoundShape(shapes1, 2);
    }

    void TearDown() override
    {
        delete p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11;
        delete v1, v2, v3, v4, v5, v6;
        delete t1;
        delete r1;
        delete c1, c2;
        delete com2, com3;
        delete com1;
    }
};

TEST_F(DFSCompoundIteratorTest, testConstructor)
{
    Shape* shapes[] = {c1, r1};
    ASSERT_NO_THROW(new DFSCompoundIterator(shapes, shapes + 2));
}

TEST_F(DFSCompoundIteratorTest, testFirst)
{
    Iterator *iterator = com1->createDFSIterator();
    iterator->first();
    ASSERT_EQ(com2, iterator->currentItem());
}

TEST_F(DFSCompoundIteratorTest, testCurrentItem)
{
    Iterator *iterator = com1->createDFSIterator();
    iterator->first();
    ASSERT_EQ(com2, iterator->currentItem());
    iterator->next();
    ASSERT_EQ(t1, iterator->currentItem());
    iterator->next();
    ASSERT_EQ(com3, iterator->currentItem());
    iterator->next();
    ASSERT_EQ(r1, iterator->currentItem());
    iterator->next();
    ASSERT_EQ(c1, iterator->currentItem());
    iterator->next();
    ASSERT_EQ(c2, iterator->currentItem());
}

TEST_F(DFSCompoundIteratorTest, testIsDone)
{
    Iterator *iterator = com2->createDFSIterator();
    iterator->first();
    ASSERT_FALSE(iterator->isDone());
    iterator->next();
    ASSERT_TRUE(iterator->isDone());
}
