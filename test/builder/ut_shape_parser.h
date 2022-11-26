#include <string>
#include <vector>
#include "../../src/builder/shape_parser.h"

class ShapeParserTest : public ::testing::Test
{
protected:
    std::string testInput1 = "Circle (Vector ((-4.28, 0.26), (-4.83, 0.73)))";
    std::string testInput2 = "CompoundShape (Triangle (Vector ((0.00, 0.00), (2.00, 0.00)), Vector ((0.00, 0.00), (8.00, 2.00))), Rectangle (Vector ((0.00, 0.00), (2.00, 0.00)), Vector ((0.00, 0.00), (0.00, 8.00))))";
    std::string testInput3 = testInput1 + ",\n" + testInput2;
    std::string testInput4 = "Rectangle (Vector ((-2.00, 1.00), (1.50, 0.47)), Vector ((-2.00, 1.00), (-1.47, 4.50)))";

    void SetUp() {}

    void TearDown() {}
};

TEST_F(ShapeParserTest, ParseCircleShouldWorkExpectedly)
{
    ShapeParser parser(testInput1);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();

    ASSERT_EQ(1, result.size());
    ASSERT_EQ(testInput1, result.at(0)->info());
}

TEST_F(ShapeParserTest, ParseRectangleShouldWorkExpectedly)
{
    ShapeParser parser(testInput4);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();

    ASSERT_EQ(1, result.size());
    ASSERT_EQ(testInput4, result.at(0)->info());
}

TEST_F(ShapeParserTest, ParseCompoundShapeShouldWorkExpectedly)
{
    ShapeParser parser(testInput2);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();

    ASSERT_EQ(1, result.size());
    ASSERT_EQ(testInput2, result.at(0)->info());
}

TEST_F(ShapeParserTest, ParseMultiplueShapesShouldWorkExpectedly)
{
    ShapeParser parser(testInput3);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();

    ASSERT_EQ(2, result.size());
    ASSERT_EQ(testInput1, result.at(0)->info());
    ASSERT_EQ(testInput2, result.at(1)->info());
}