#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/compound_shape.h"

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

TEST_F(CompoundShapeTest, testCompoundShapeArea)
{
    Shape* shapes[] = {c1, r1};
    CompoundShape* compoundShape = new CompoundShape(shapes, 2); 
    ASSERT_NEAR(c1->area() + r1->area(), compoundShape->area(), 0.001);
}

TEST_F(CompoundShapeTest, testCompoundShapePerimeter)
{
    Shape* shapes[] = {c1, r1};
    CompoundShape* compoundShape = new CompoundShape(shapes, 2); 
    ASSERT_NEAR(c1->perimeter() + r1->perimeter(), compoundShape->perimeter(), 0.001);
}

TEST_F(CompoundShapeTest, testCompoundShapeInfo)
{
    Shape* shapes[] = {c1, r1};
    CompoundShape* compoundShape = new CompoundShape(shapes, 2);
    std::string expectedInfo = "CompoundShape (Circle (Vector ((1.34, -2.00), (6.00, 7.00))), Rectangle (Vector ((-3.00, 3.00), (-1.00, 3.00)), Vector ((-1.00, 3.00), (-1.00, -1.00))))";
    ASSERT_EQ(expectedInfo, compoundShape->info());
}

TEST_F(CompoundShapeTest, testAddShape)
{
    TwoDimensionalVector *vec1 = new TwoDimensionalVector(new Point(0, 0), new Point(3, 3));
    TwoDimensionalVector *vec2 = new TwoDimensionalVector(new Point(0, 0), new Point(-1, 1));
    Triangle *triangle = new Triangle(vec1, vec2);
    Shape* shapes[] = {c1, r1};
    CompoundShape* compoundShape = new CompoundShape(shapes, 2);
    ASSERT_NO_THROW(compoundShape->addShape(triangle));

    delete vec1;
    delete vec2;
    delete triangle;
}

TEST_F(CompoundShapeTest, testDeleteShape)
{
    TwoDimensionalVector *vec1 = new TwoDimensionalVector(new Point(0, 0), new Point(3, 3));
    TwoDimensionalVector *vec2 = new TwoDimensionalVector(new Point(0, 0), new Point(-1, 1));
    Triangle *triangle = new Triangle(vec1, vec2);
    Shape* shapes[] = {c1, r1};
    CompoundShape* compoundShape = new CompoundShape(shapes, 2);
    compoundShape->addShape(triangle);
    ASSERT_NO_THROW(compoundShape->deleteShape(triangle));
    
    delete vec1;
    delete vec2;
    delete triangle;
}
