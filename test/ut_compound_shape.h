#include <list>

#include "../src/point.h"
#include "../src/two_dimensional_vector.h"
#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/compound_shape.h"

class CompoundShapeTest : public ::testing::Test {
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

        delete v1;
        delete v2;
        delete v3;

        delete c1;
        
        delete r1;
    }
};

TEST_F(CompoundShapeTest, testArea)
{
    //List<Shape *> shapes = {c1, r1};
    //CompoundShape* compoundShape = new CompoundShape(shapes); 
    //ASSERT_EQ(c1.area() + r1.area(), compoundShape->area());
}

