#include <string>
#include <vector>
#include "../../src/builder/shape_parser.h"

class ShapeParserTest : public ::testing::Test
{
protected:
    std::string circleInput = "Circle (Vector ((-4.28, 0.26), (-4.83, 0.73)))";
    std::string triangleInput = "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))";
    std::string rectangleInput = "Rectangle (Vector ((-2.00, 1.00), (1.50, 0.47)), Vector ((-2.00, 1.00), (-1.47, 4.50)))";
    std::string compoundShapeInput = "CompoundShape (Triangle (Vector ((0.00, 0.00), (2.00, 0.00)), Vector ((0.00, 0.00), (8.00, 2.00))), Rectangle (Vector ((0.00, 0.00), (2.00, 0.00)), Vector ((0.00, 0.00), (0.00, 8.00))))";

    void SetUp() {}

    void TearDown() {}
};

TEST_F(ShapeParserTest, ParseCircleShouldWorkExpectedly)
{
    ShapeParser parser(circleInput);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();

    ASSERT_EQ(1, result.size());
    ASSERT_EQ(circleInput, result.at(0)->info());
}

TEST_F(ShapeParserTest, ParseTriangleShouldWorkExpectedly)
{
    ShapeParser parser(triangleInput);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();

    ASSERT_EQ(1, result.size());
    ASSERT_NEAR(6, result.at(0)->area(), 0.001);
    ASSERT_NEAR(12, result.at(0)->perimeter(), 0.001);
}

TEST_F(ShapeParserTest, ParseRectangleShouldWorkExpectedly)
{
    ShapeParser parser(rectangleInput);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();

    ASSERT_EQ(1, result.size());
    ASSERT_NEAR(12.5309, result.at(0)->area(), 0.001);
    ASSERT_NEAR(14.1596, result.at(0)->perimeter(), 0.001);
}

TEST_F(ShapeParserTest, ParseCompoundShapeShouldWorkExpectedly)
{
    ShapeParser parser(compoundShapeInput);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();

    ASSERT_EQ(1, result.size());
    ASSERT_EQ(compoundShapeInput, result.at(0)->info());
}

TEST_F(ShapeParserTest, ParseMultiplueShapesShouldWorkExpectedly)
{
    std::string input = circleInput + ",\n" + compoundShapeInput;
    ShapeParser parser(input);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();

    ASSERT_EQ(2, result.size());
    ASSERT_EQ(circleInput, result.at(0)->info());
    ASSERT_EQ(compoundShapeInput, result.at(1)->info());
}