#include <set>
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/shape.h"
#include "../src/triangle.h"
#include "../src/rectangle.h"
#include "../src/circle.h"
#include "../src/compound_shape.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"
#include "../src/visitor/shape_visitor.h"
#include "../src/visitor/collision_detector.h"

class CompoundShapeTest : public ::testing::Test
{
protected:
    Point *p1, *p2, *p3, *p4, *p5;
    TwoDimensionalVector *v1, *v2, *v3;
    Circle *c1;
    Rectangle *r1;

    void SetUp() override
    {
        p1 = new Point(1.3449, -1.999);
        p2 = new Point(6.0, 7);
        p3 = new Point(-3, 3);
        p4 = new Point(-1, 3);
        p5 = new Point(-1, -1);

        v1 = new TwoDimensionalVector(p1, p2);
        v2 = new TwoDimensionalVector(p3, p4);
        v3 = new TwoDimensionalVector(p4, p5);

        c1 = new Circle(v1);

        r1 = new Rectangle(v2, v3);
    }

    void TearDown() override
    {
        delete p1;
        delete p2;
        delete p3;
        delete p4;
        delete p5;
        delete v2;
        delete v3;
        delete c1;
        delete r1;
    }
};

TEST_F(CompoundShapeTest, CompoundShapeAreaCalculationShouldBeCorrect)
{
    Shape *shapes[] = {c1, r1};
    CompoundShape *compoundShape = new CompoundShape(shapes, 2);
    ASSERT_NEAR(c1->area() + r1->area(), compoundShape->area(), 0.001);
}

TEST_F(CompoundShapeTest, CompoundShapePerimeterCalculationShouldBeCorrect)
{
    Shape *shapes[] = {c1, r1};
    CompoundShape *compoundShape = new CompoundShape(shapes, 2);
    ASSERT_NEAR(c1->perimeter() + r1->perimeter(), compoundShape->perimeter(), 0.001);
}

TEST_F(CompoundShapeTest, CompoundShapeInfoShouldWorkExpectedly)
{
    Shape *shapes[] = {c1, r1};
    CompoundShape *compoundShape = new CompoundShape(shapes, 2);
    std::string expectedInfo = "CompoundShape (Circle (Vector ((1.34, -2.00), (6.00, 7.00))), Rectangle (Vector ((-3.00, 3.00), (-1.00, 3.00)), Vector ((-1.00, 3.00), (-1.00, -1.00))))";
    ASSERT_EQ(expectedInfo, compoundShape->info());
}

TEST_F(CompoundShapeTest, AddShapeShouldWorkExpectedly)
{
    TwoDimensionalVector *vec1 = new TwoDimensionalVector(new Point(0, 0), new Point(3, 3));
    TwoDimensionalVector *vec2 = new TwoDimensionalVector(new Point(0, 0), new Point(-1, 1));
    Triangle *triangle = new Triangle(vec1, vec2);
    Shape *shapes[] = {c1, r1};
    CompoundShape *compoundShape = new CompoundShape(shapes, 2);
    ASSERT_NO_THROW(compoundShape->addShape(triangle));

    Iterator *iterator = compoundShape->createIterator(new DFSIteratorFactory());
    ASSERT_EQ(c1, iterator->currentItem());
    iterator->next();
    ASSERT_EQ(r1, iterator->currentItem());
    iterator->next();
    ASSERT_EQ(triangle, iterator->currentItem());

    delete vec1;
    delete vec2;
    delete triangle;
}

TEST_F(CompoundShapeTest, DeleteShapeShouldWorkExpectedly)
{
    TwoDimensionalVector *vec1 = new TwoDimensionalVector(new Point(0, 0), new Point(3, 3));
    TwoDimensionalVector *vec2 = new TwoDimensionalVector(new Point(0, 0), new Point(-1, 1));
    Triangle *triangle = new Triangle(vec1, vec2);
    Shape *shapes[] = {c1, r1};
    CompoundShape *compoundShape = new CompoundShape(shapes, 2);
    compoundShape->addShape(triangle);
    ASSERT_NO_THROW(compoundShape->deleteShape(triangle));

    Iterator *iterator = compoundShape->createIterator(new BFSIteratorFactory());
    ASSERT_EQ(c1, iterator->currentItem());
    iterator->next();
    ASSERT_EQ(r1, iterator->currentItem());
    iterator->next();
    ASSERT_TRUE(iterator->isDone());

    delete vec1;
    delete vec2;
    delete triangle;
}

TEST_F(CompoundShapeTest, DFSIteratorShouldWorkExpectedly)
{
    Shape *shapes[] = {c1, r1};
    CompoundShape *compoundShape = new CompoundShape(shapes, 2);
    Iterator *iterator = compoundShape->createIterator(new DFSIteratorFactory());

    iterator->first();
    ASSERT_EQ(c1, iterator->currentItem());
    iterator->next();
    ASSERT_EQ(r1, iterator->currentItem());
}

TEST_F(CompoundShapeTest, BFSIteratorShouldWorkExpectedly)
{
    Shape *shapes[] = {c1, r1};
    CompoundShape *compoundShape = new CompoundShape(shapes, 2);
    Iterator *iterator = compoundShape->createIterator(new BFSIteratorFactory());

    iterator->first();
    ASSERT_EQ(c1, iterator->currentItem());
    iterator->next();
    ASSERT_EQ(r1, iterator->currentItem());
}

TEST_F(CompoundShapeTest, GetPoints)
{
    Shape *shapes[] = {c1, r1};
    CompoundShape *compoundShape = new CompoundShape(shapes, 2);
    std::set<const Point *> points = compoundShape->getPoints();

    int expectedSize = c1->getPoints().size() + r1->getPoints().size();
    ASSERT_EQ(expectedSize, points.size());
}

TEST_F(CompoundShapeTest, AcceptDoesNotThrowException)
{
    Shape *shapes[] = {c1, r1};
    CompoundShape *compoundShape = new CompoundShape(shapes, 2);
    Circle *other = new Circle(
        new TwoDimensionalVector(new Point(0, 0), new Point(3, 7)));

    ShapeVisitor *collisionDetector = new CollisionDetector(other);
    ASSERT_NO_THROW(compoundShape->accept(collisionDetector));

    delete other;
}
