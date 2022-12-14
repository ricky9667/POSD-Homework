#include "../../src/shape.h"
#include "../../src/builder/shape_parser.h"
#include <vector>
#include <string>

TEST(ShapeParserTest, ParseCircleShouldBeCorrect)
{
    std::string input = "Circle (Vector ((0.00, 0.00), (3.00, 0.00)))";
    ShapeParser parser(input);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();

    ASSERT_NEAR(9 * M_PI, result.at(0)->area(), 0.001);
    delete *(result.begin());
}

TEST(ShapeParserTest, ParseTriangleShouldBeCorrect)
{
    std::string input = "Triangle (Vector ((5.00, 8.00), (8.00, 11.00)), Vector ((5.00, 8.00), (10.00, 8.00)))";
    ShapeParser parser(input);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();
    ASSERT_NEAR(7.5, result.at(0)->area(), 0.001);
    delete *(result.begin());
}

TEST(ShapeParserTest, ParseRectangleShouldBeCorrect)
{
    std::string input = "Rectangle (Vector ((20.00, 13.00), (16.00, 14.00)), Vector ((16.00, 14.00), (15.00, 10.00)))";
    ShapeParser parser(input);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();
    ASSERT_NEAR(17, result.at(0)->area(), 0.001);
    delete *(result.begin());
}

TEST(ShapeParserTest, ParseCompoundShapeShouldBeCorrect)
{
    std::string input = "CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 5.00))), Rectangle (Vector ((0.00, 0.00), (0.00, 5.00)), Vector ((0.00, 0.00), (5.00, 0.00))))";
    ShapeParser parser(input);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();
    ASSERT_NEAR(5 * 5 * M_PI + 25, result.at(0)->area(), 0.001);
    delete *(result.begin());
}

TEST(ShapeParserTest, ParseComplexCompoundShapeShouldBeCorrect)
{
    std::string input = "CompoundShape (CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 5.00))), Rectangle (Vector ((0.00, 0.00), (0.00, 5.00)), Vector ((0.00, 0.00), (5.00, 0.00)))), CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 3.00)))))";
    ShapeParser parser(input);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();
    ASSERT_NEAR(5 * 5 * M_PI + 25 + 3 * 3 * M_PI, result.at(0)->area(), 0.001);
    delete *(result.begin());
}

TEST(ShapeParserTest, ParseMultipleShapeShouldBeCorrect)
{
    std::string input = "Circle (Vector ((0.00, 0.00), (3.00, 0.00))) Triangle (Vector ((5.00, 8.00), (8.00, 11.00)), Vector ((5.00, 8.00), (10.00, 8.00)))";
    ShapeParser parser(input);
    parser.parse();
    std::vector<Shape *> result = parser.getResult();

    ASSERT_NEAR(9 * M_PI, result.at(0)->area(), 0.001);
    ASSERT_NEAR(7.5, result.at(1)->area(), 0.001);
    delete *(result.begin());
    delete *(result.begin() + 1);
}

// #include <string>
// #include <vector>
// #include "../../src/builder/shape_parser.h"

// class ShapeParserTest : public ::testing::Test
// {
// protected:
//     std::string circleInput = "Circle (Vector ((-4.28, 0.26), (-4.83, 0.73)))";
//     std::string triangleInput = "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))";
//     std::string rectangleInput = "Rectangle (Vector ((-2.00, 1.00), (1.50, 0.47)), Vector ((-2.00, 1.00), (-1.47, 4.50)))";
//     std::string compoundShapeInput = "CompoundShape (Triangle (Vector ((0.00, 0.00), (2.00, 0.00)), Vector ((0.00, 0.00), (8.00, 2.00))), Rectangle (Vector ((0.00, 0.00), (2.00, 0.00)), Vector ((0.00, 0.00), (0.00, 8.00))))";

//     void SetUp() {}

//     void TearDown() {}
// };

// TEST_F(ShapeParserTest, ParseCircleShouldWorkExpectedly)
// {
//     ShapeParser parser(circleInput);
//     parser.parse();
//     std::vector<Shape *> result = parser.getResult();

//     ASSERT_EQ(1, result.size());
//     ASSERT_EQ(circleInput, result.at(0)->info());
// }

// TEST_F(ShapeParserTest, ParseTriangleShouldWorkExpectedly)
// {
//     ShapeParser parser(triangleInput);
//     parser.parse();
//     std::vector<Shape *> result = parser.getResult();

//     ASSERT_EQ(1, result.size());
//     ASSERT_NEAR(6, result.at(0)->area(), 0.001);
//     ASSERT_NEAR(12, result.at(0)->perimeter(), 0.001);
// }

// TEST_F(ShapeParserTest, ParseRectangleShouldWorkExpectedly)
// {
//     ShapeParser parser(rectangleInput);
//     parser.parse();
//     std::vector<Shape *> result = parser.getResult();

//     ASSERT_EQ(1, result.size());
//     ASSERT_NEAR(12.5309, result.at(0)->area(), 0.001);
//     ASSERT_NEAR(14.1596, result.at(0)->perimeter(), 0.001);
// }

// TEST_F(ShapeParserTest, ParseCompoundShapeShouldWorkExpectedly)
// {
//     ShapeParser parser(compoundShapeInput);
//     parser.parse();
//     std::vector<Shape *> result = parser.getResult();

//     ASSERT_EQ(1, result.size());
//     ASSERT_EQ(compoundShapeInput, result.at(0)->info());
// }

// TEST_F(ShapeParserTest, ParseMultiplueShapesShouldWorkExpectedly)
// {
//     std::string input = circleInput + ",\n" + compoundShapeInput;
//     ShapeParser parser(input);
//     parser.parse();
//     std::vector<Shape *> result = parser.getResult();

//     ASSERT_EQ(2, result.size());
//     ASSERT_EQ(circleInput, result.at(0)->info());
//     ASSERT_EQ(compoundShapeInput, result.at(1)->info());
// }