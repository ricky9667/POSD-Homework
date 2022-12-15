#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/compound_shape.h"
#include "../src/iterator/iterator.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"

class CompoundShapeTest : public ::testing::Test
{
protected:
    Point *p1, *p2, *p3, *p4;
    TwoDimensionalVector *vec1, *vec2, *vec3;
    Shape *cir1, *cir2, *rect;
    CompoundShape *cs1, *cs2, *cs3;

    void SetUp() override
    {
        p1 = new Point(0, 0);
        p2 = new Point(0, 5);
        p3 = new Point(5, 0);
        p4 = new Point(0, 3);

        vec1 = new TwoDimensionalVector(*p1, *p2);
        vec2 = new TwoDimensionalVector(*p1, *p3);
        vec3 = new TwoDimensionalVector(*p1, *p4);
        cir1 = new Circle(*vec1);
        cir2 = new Circle(*vec3);
        rect = new Rectangle(*vec1, *vec2);

        Shape *sp1[] = {cir1, rect};
        cs1 = new CompoundShape(sp1, 2);

        Shape *sp2[] = {cir2};
        cs2 = new CompoundShape(sp2, 1);

        Shape *sp3[] = {cs1, cs2};
        cs3 = new CompoundShape(sp3, 2);
    }

    void TearDown() override
    {
        delete cs3;
        delete p1;
        delete p2;
        delete p3;
        delete p4;
        delete vec1;
        delete vec2;
        delete vec3;
    }
};

TEST_F(CompoundShapeTest, ConstructorShouldBeCorrect)
{
    Shape *cir1 = new Circle(*vec1);
    Shape *cir2 = new Circle(*vec3);
    Shape *rect = new Rectangle(*vec1, *vec2);
    Shape *shapes[] = {cir1, rect, cir2};
    ASSERT_NO_THROW(CompoundShape cs(shapes, 3));
}

TEST_F(CompoundShapeTest, AreaShouldBeCalculatedCorrectly)
{
    ASSERT_NEAR(pow(5.0, 2) * M_PI + 25, cs1->area(), 0.001);
    ASSERT_NEAR(pow(3.0, 2) * M_PI + pow(5.0, 2) * M_PI + 25, cs3->area(), 0.001);
}

TEST_F(CompoundShapeTest, PerimeterShouldBeCalculatedCorrectly)
{
    ASSERT_NEAR(10 * M_PI + 20, cs1->perimeter(), 0.001);
    ASSERT_NEAR(10 * M_PI + 6 * M_PI + 20, cs3->perimeter(), 0.001);
}

TEST_F(CompoundShapeTest, InfoShouldBeCorrectly)
{
    std::string result = "CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 5.00))), Rectangle (Vector ((0.00, 0.00), (0.00, 5.00)), Vector ((0.00, 0.00), (5.00, 0.00))))";

    ASSERT_EQ(result, cs1->info());

    std::string result2 = "CompoundShape (CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 5.00))), Rectangle (Vector ((0.00, 0.00), (0.00, 5.00)), Vector ((0.00, 0.00), (5.00, 0.00)))), CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 3.00)))))";

    ASSERT_EQ(result2, cs3->info());
}

TEST_F(CompoundShapeTest, AddShapeCorrectly)
{
    Shape *shapes[] = {};
    CompoundShape *cs = new CompoundShape(shapes, 0);
    Circle *c1 = new Circle(*vec1);

    ASSERT_NO_THROW(cs->addShape(c1));

    Iterator *it = cs->createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_EQ(c1, it->currentItem());

    delete cs;
    delete it;
}

TEST_F(CompoundShapeTest, DeleteShapeCorrectly)
{
    Shape *shapes[] = {};
    CompoundShape *cs = new CompoundShape(shapes, 0);
    Circle *c1 = new Circle(*vec1);
    Circle *c2 = new Circle(*vec3);

    cs->addShape(c1);
    cs->addShape(c2);
    cs->deleteShape(c2);

    Iterator *it = cs->createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_EQ(c1, it->currentItem());

    delete cs;
    delete it;
}

TEST_F(CompoundShapeTest, DeleteInnerShapeCorrectly)
{
    Shape *shapes1[] = {};
    Shape *shapes2[] = {};
    CompoundShape *cShape = new CompoundShape(shapes1, 0);
    CompoundShape *cShape2 = new CompoundShape(shapes2, 0);
    Circle *c1 = new Circle(*vec1);
    Circle *c2 = new Circle(*vec3);
    Circle *c3 = new Circle(*vec3);

    cShape->addShape(c1);
    cShape->addShape(c2);
    cShape2->addShape(cShape);
    cShape2->addShape(c3);

    Iterator *it = cShape2->createIterator(IteratorFactory::getInstance("DFS"));

    ASSERT_NEAR(5 * 5 * M_PI + 3 * 3 * M_PI * 2, cShape2->area(), 0.001);
    cShape2->deleteShape(c2);
    ASSERT_NEAR(5 * 5 * M_PI + +3 * 3 * M_PI, cShape2->area(), 0.001);

    delete cShape2;
    delete it;
}

TEST_F(CompoundShapeTest, DFSIteratorShouldBeCorrect)
{
    Iterator *it = cs3->createIterator(IteratorFactory::getInstance("DFS"));
    ASSERT_FALSE(it->isDone());

    ASSERT_NEAR(5 * 5 * M_PI + 25, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(5 * 5 * M_PI, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(25, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(3 * 3 * M_PI, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(3 * 3 * M_PI, it->currentItem()->area(), 0.001);

    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());

    delete it;
}

TEST_F(CompoundShapeTest, BFSIteratorShouldBeCorrect)
{
    Iterator *it = cs3->createIterator(IteratorFactory::getInstance("BFS"));
    ASSERT_FALSE(it->isDone());

    ASSERT_NEAR(5 * 5 * M_PI + 25, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(3 * 3 * M_PI, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(5 * 5 * M_PI, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(25, it->currentItem()->area(), 0.001);
    ASSERT_NO_THROW(it->next());
    ASSERT_NEAR(3 * 3 * M_PI, it->currentItem()->area(), 0.001);

    ASSERT_NO_THROW(it->next());
    ASSERT_TRUE(it->isDone());

    delete it;
}

// hw 3
TEST_F(CompoundShapeTest, GetPointsShouldBeCorrect)
{
    std::set<Point> points = cs3->getPoints();
    std::set<Point, bool (*)(Point, Point)> actualPoints(
        points.begin(), points.end(),
        [](Point p1, Point p2) -> bool
        {
            return p1.x() < p2.x() || (p1.x() == p2.x() && p1.y() < p2.y());
        });
    Point pMax1(5, 5), pMin1(-5, -5), pMax2(3, 3), pMin2(-3, -3);
    ASSERT_TRUE(actualPoints.size() == 7);
    ASSERT_TRUE(actualPoints.find(*p1) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(*p2) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(*p3) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(pMax1) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(pMin1) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(pMax2) != actualPoints.end());
    ASSERT_TRUE(actualPoints.find(pMin2) != actualPoints.end());
}


// #include <set>
// #include "../src/point.h"
// #include "../src/two_dimensional_vector.h"
// #include "../src/shape.h"
// #include "../src/triangle.h"
// #include "../src/rectangle.h"
// #include "../src/circle.h"
// #include "../src/compound_shape.h"
// #include "../src/iterator/factory/dfs_iterator_factory.h"
// #include "../src/iterator/factory/bfs_iterator_factory.h"
// #include "../src/iterator/factory/list_iterator_factory.h"
// #include "../src/visitor/shape_visitor.h"
// #include "../src/visitor/collision_detector.h"

// class CompoundShapeTest : public ::testing::Test
// {
// protected:
//     Point *p1, *p2, *p3, *p4, *p5;
//     TwoDimensionalVector *v1, *v2, *v3;
//     Circle *c1;
//     Rectangle *r1;

//     void SetUp() override
//     {
//         p1 = new Point(1.3449, -1.999);
//         p2 = new Point(6.0, 7);
//         p3 = new Point(-3, 3);
//         p4 = new Point(-1, 3);
//         p5 = new Point(-1, -1);

//         v1 = new TwoDimensionalVector(p1, p2);
//         v2 = new TwoDimensionalVector(p3, p4);
//         v3 = new TwoDimensionalVector(p4, p5);

//         c1 = new Circle(v1);

//         r1 = new Rectangle(v2, v3);
//     }

//     void TearDown() override
//     {
//         delete p1;
//         delete p2;
//         delete p3;
//         delete p4;
//         delete p5;
//         delete v2;
//         delete v3;
//         delete c1;
//         delete r1;
//     }
// };

// TEST_F(CompoundShapeTest, CompoundShapeAreaCalculationShouldBeCorrect)
// {
//     Shape *shapes[] = {c1, r1};
//     CompoundShape *compoundShape = new CompoundShape(shapes, 2);
//     ASSERT_NEAR(c1->area() + r1->area(), compoundShape->area(), 0.001);
// }

// TEST_F(CompoundShapeTest, CompoundShapePerimeterCalculationShouldBeCorrect)
// {
//     Shape *shapes[] = {c1, r1};
//     CompoundShape *compoundShape = new CompoundShape(shapes, 2);
//     ASSERT_NEAR(c1->perimeter() + r1->perimeter(), compoundShape->perimeter(), 0.001);
// }

// TEST_F(CompoundShapeTest, CompoundShapeInfoShouldWorkExpectedly)
// {
//     Shape *shapes[] = {c1, r1};
//     CompoundShape *compoundShape = new CompoundShape(shapes, 2);
//     std::string expectedInfo = "CompoundShape (Circle (Vector ((1.34, -2.00), (6.00, 7.00))), Rectangle (Vector ((-3.00, 3.00), (-1.00, 3.00)), Vector ((-1.00, 3.00), (-1.00, -1.00))))";
//     ASSERT_EQ(expectedInfo, compoundShape->info());
// }

// TEST_F(CompoundShapeTest, AddShapeShouldWorkExpectedly)
// {
//     TwoDimensionalVector *vec1 = new TwoDimensionalVector(new Point(0, 0), new Point(3, 3));
//     TwoDimensionalVector *vec2 = new TwoDimensionalVector(new Point(0, 0), new Point(-1, 1));
//     Triangle *triangle = new Triangle(vec1, vec2);
//     Shape *shapes[] = {c1, r1};
//     CompoundShape *compoundShape = new CompoundShape(shapes, 2);
//     ASSERT_NO_THROW(compoundShape->addShape(triangle));

//     Iterator *iterator = compoundShape->createIterator(new DFSIteratorFactory());
//     ASSERT_EQ(c1, iterator->currentItem());
//     iterator->next();
//     ASSERT_EQ(r1, iterator->currentItem());
//     iterator->next();
//     ASSERT_EQ(triangle, iterator->currentItem());

//     delete vec1;
//     delete vec2;
//     delete triangle;
// }

// TEST_F(CompoundShapeTest, DeleteShapeShouldWorkExpectedly)
// {
//     TwoDimensionalVector *vec1 = new TwoDimensionalVector(new Point(0, 0), new Point(3, 3));
//     TwoDimensionalVector *vec2 = new TwoDimensionalVector(new Point(0, 0), new Point(-1, 1));
//     Triangle *triangle = new Triangle(vec1, vec2);
//     Shape *shapes[] = {c1, r1};
//     CompoundShape *compoundShape = new CompoundShape(shapes, 2);
//     compoundShape->addShape(triangle);
//     ASSERT_NO_THROW(compoundShape->deleteShape(triangle));

//     Iterator *iterator = compoundShape->createIterator(new BFSIteratorFactory());
//     ASSERT_EQ(c1, iterator->currentItem());
//     iterator->next();
//     ASSERT_EQ(r1, iterator->currentItem());
//     iterator->next();
//     ASSERT_TRUE(iterator->isDone());

//     delete vec1;
//     delete vec2;
//     delete triangle;
// }

// TEST_F(CompoundShapeTest, DFSIteratorShouldWorkExpectedly)
// {
//     Shape *shapes[] = {c1, r1};
//     CompoundShape *compoundShape = new CompoundShape(shapes, 2);
//     Iterator *iterator = compoundShape->createIterator(new DFSIteratorFactory());

//     iterator->first();
//     ASSERT_EQ(c1, iterator->currentItem());
//     iterator->next();
//     ASSERT_EQ(r1, iterator->currentItem());
// }

// TEST_F(CompoundShapeTest, BFSIteratorShouldWorkExpectedly)
// {
//     Shape *shapes[] = {c1, r1};
//     CompoundShape *compoundShape = new CompoundShape(shapes, 2);
//     Iterator *iterator = compoundShape->createIterator(new BFSIteratorFactory());

//     iterator->first();
//     ASSERT_EQ(c1, iterator->currentItem());
//     iterator->next();
//     ASSERT_EQ(r1, iterator->currentItem());
// }

// TEST_F(CompoundShapeTest, ListIteratorShouldWorkExpectedly)
// {
//     Shape *shapes[] = {c1, r1};
//     CompoundShape *compoundShape = new CompoundShape(shapes, 2);
//     Iterator *iterator = compoundShape->createIterator(new ListIteratorFactory());

//     iterator->first();
//     ASSERT_EQ(c1, iterator->currentItem());
//     iterator->next();
//     ASSERT_EQ(r1, iterator->currentItem());
// }

// TEST_F(CompoundShapeTest, GetPoints)
// {
//     Shape *shapes[] = {c1, r1};
//     CompoundShape *compoundShape = new CompoundShape(shapes, 2);
//     std::set<const Point *> points = compoundShape->getPoints();

//     int expectedSize = c1->getPoints().size() + r1->getPoints().size();
//     ASSERT_EQ(expectedSize, points.size());
// }

// TEST_F(CompoundShapeTest, AcceptDoesNotThrowException)
// {
//     Shape *shapes[] = {c1, r1};
//     CompoundShape *compoundShape = new CompoundShape(shapes, 2);
//     Circle *other = new Circle(
//         new TwoDimensionalVector(new Point(0, 0), new Point(3, 7)));

//     ShapeVisitor *collisionDetector = new CollisionDetector(other);
//     ASSERT_NO_THROW(compoundShape->accept(collisionDetector));

//     delete other;
// }

// TEST_F(CompoundShapeTest, ReplaceWorksExpectedly)
// {
//     Shape *shapes[] = {c1, r1};
//     CompoundShape *compoundShape = new CompoundShape(shapes, 2);
//     Circle *other = new Circle(
//         new TwoDimensionalVector(new Point(0, 0), new Point(3, 7)));
//     compoundShape->replace(c1, other);

//     Iterator *iterator = compoundShape->createIterator(new ListIteratorFactory());
//     ASSERT_EQ(other, iterator->currentItem());
//     iterator->next();
//     ASSERT_EQ(r1, iterator->currentItem());
//     iterator->next();
// }
