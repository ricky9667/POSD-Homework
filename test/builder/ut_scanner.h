#include "../../src/builder/scanner.h"

TEST(ScannerTest, ScanCircleShouldBeCorrect)
{
    std::string input = "Circle (Vector ((14.00, 2.00), (18.00, -4.00)))";
    Scanner scanner(input);
    ASSERT_EQ("Circle", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(14.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(2.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(18.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(-4.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_TRUE(scanner.isDone());
}

TEST(ScannerTest, ScanTriangleShouldBeCorrect)
{
    std::string input = "Triangle (Vector ((5.00, 8.00), (8.00, 11.00)), Vector ((5.00, 8.00), (10.00, 8.00)))";
    Scanner scanner(input);
    ASSERT_EQ("Triangle", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(5.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(8.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(8.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(11.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(5.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(8.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(10.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(8.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_TRUE(scanner.isDone());
}

TEST(ScannerTest, ScanRectangleShouldBeCorrect)
{
    std::string input = "Rectangle (Vector ((20.00, 13.00), (16.00, 14.00)), Vector ((16.00, 14.00), (15.00, 10.00)))";
    Scanner scanner(input);
    ASSERT_EQ("Rectangle", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(20.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(13.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(16.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(14.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(16.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(14.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(15.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(10.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_TRUE(scanner.isDone());
}

TEST(ScannerTest, ScanCompoundShapeShouldBeCorrect)
{
    std::string input = "CompoundShape ()";
    Scanner scanner(input);
    ASSERT_EQ("CompoundShape", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_TRUE(scanner.isDone());
}

TEST(ScannerTest, ScanSimpleCompoundShapeShouldBeCorrect)
{
    std::vector<std::string> expectedToken = {"CompoundShape", "(", "Circle", "(", "Vector", "(", "(", "double", ",", "double", ")", ",",
                                              "(", "double", ",", "double", ")", ")", ")", ",",
                                              "Rectangle", "(", "Vector", "(", "(", "double", ",", "double", ")", ",",
                                              "(", "double", ",", "double", ")", ")", ",",
                                              "Vector", "(", "(", "double", ",", "double", ")", ",",
                                              "(", "double", ",", "double", ")", ")", ")", ")"};
    std::vector<double> expectedDouble = {0.0, 0.0, 0.0, 5.0,
                                          0.0, 0.0, 0.0, 5.0,
                                          0.0, 0.0, 5.0, 0.0};

    std::string input = "CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 5.00))), Rectangle (Vector ((0.00, 0.00), (0.00, 5.00)), Vector ((0.00, 0.00), (5.00, 0.00))))";
    Scanner scanner(input);

    int pos = 0;
    for (auto token : expectedToken)
    {
        if (token == "double")
        {
            ASSERT_EQ(expectedDouble.at(pos), scanner.nextDouble());
            pos++;
        }
        else
        {
            ASSERT_EQ(token, scanner.next());
        }
    }
    ASSERT_TRUE(scanner.isDone());
}

TEST(ScannerTest, ScanComplexCompoundShapeShouldBeCorrect)
{
    std::vector<std::string> expectedToken = {"CompoundShape", "(", "CompoundShape", "(",
                                              "Circle", "(", "Vector", "(", "(", "double", ",", "double", ")", ",",
                                              "(", "double", ",", "double", ")", ")", ")", ",",
                                              "Rectangle", "(", "Vector", "(", "(", "double", ",", "double", ")", ",",
                                              "(", "double", ",", "double", ")", ")", ",",
                                              "Vector", "(", "(", "double", ",", "double", ")", ",",
                                              "(", "double", ",", "double", ")", ")", ")", ")", ",",
                                              "CompoundShape", "(", "Circle", "(", "Vector", "(", "(", "double", ",", "double", ")", ",",
                                              "(", "double", ",", "double", ")", ")", ")", ")", ")"};
    std::vector<double> expectedDouble = {0.0, 0.0, 0.0, 5.0,
                                          0.0, 0.0, 0.0, 5.0,
                                          0.0, 0.0, 5.0, 0.0,
                                          0.0, 0.0, 0.0, 3.0};

    std::string input = "CompoundShape (CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 5.00))), Rectangle (Vector ((0.00, 0.00), (0.00, 5.00)), Vector ((0.00, 0.00), (5.00, 0.00)))), CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 3.00)))))";
    Scanner scanner(input);

    int pos = 0;
    for (auto token : expectedToken)
    {
        if (token == "double")
        {
            ASSERT_EQ(expectedDouble.at(pos), scanner.nextDouble());
            pos++;
        }
        else
        {
            ASSERT_EQ(token, scanner.next());
        }
    }
    ASSERT_TRUE(scanner.isDone());
}

TEST(ScannerTest, NextShouldThrowExceptionWhenIsDone)
{
    std::string input = "Circle (Vector ((14.00, 2.00), (18.00, -4.00)))";
    Scanner scanner(input);
    ASSERT_EQ("Circle", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(14.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(2.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(18.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(-4.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());

    ASSERT_ANY_THROW(scanner.next());
}

TEST(ScannerTest, NextDoubleShouldThrowExceptionWhenIsDone)
{
    std::string input = "Circle (Vector ((14.00, 2.00), (18.00, -4.00)))";
    Scanner scanner(input);
    ASSERT_EQ("Circle", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(14.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(2.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(18.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(-4.0, scanner.nextDouble());

    ASSERT_ANY_THROW(scanner.nextDouble());
}

// #include <string>
// #include "../../src/builder/scanner.h"

// class ScannerTest : public ::testing::Test
// {
// protected:
//     const std::string vectorToken = "Vector";
//     const std::string circleToken = "Circle";
//     const std::string leftParenthesisToken = "(";
//     const std::string rightParenthesisToken = ")";
//     const std::string commaToken = ",";

//     void SetUp() {}

//     void TearDown() {}
// };

// TEST_F(ScannerTest, NextShouldWorkExpectedly)
// {
//     std::string inputString = "Circle ()";
//     Scanner scanner(inputString);

//     ASSERT_EQ(circleToken, scanner.next());
//     ASSERT_EQ(leftParenthesisToken, scanner.next());
//     ASSERT_EQ(rightParenthesisToken, scanner.next());
// }

// TEST_F(ScannerTest, NextDoubleShouldWorkExpectedly)
// {
//     std::string inputString = "4.86, 1.323";
//     Scanner scanner(inputString);

//     ASSERT_NEAR(4.86, scanner.nextDouble(), 0.001);
//     ASSERT_EQ(commaToken, scanner.next());
//     ASSERT_NEAR(1.323, scanner.nextDouble(), 0.001);
// }

// TEST_F(ScannerTest, IsDoneShouldWorkExpectedly)
// {
//     std::string inputString = "Circle (Vector ((-4.28, 0.26), (-4.83, 0.73)))";
//     Scanner scanner(inputString);

//     // circle
//     ASSERT_EQ(circleToken, scanner.next());
//     ASSERT_FALSE(scanner.isDone());

//     ASSERT_EQ(leftParenthesisToken, scanner.next());
//     ASSERT_FALSE(scanner.isDone());

//     // vector
//     ASSERT_EQ(vectorToken, scanner.next());
//     ASSERT_FALSE(scanner.isDone());

//     ASSERT_EQ(leftParenthesisToken, scanner.next());
//     ASSERT_FALSE(scanner.isDone());

//     // first point
//     ASSERT_EQ(leftParenthesisToken, scanner.next());
//     ASSERT_FALSE(scanner.isDone());

//     ASSERT_NEAR(-4.28, scanner.nextDouble(), 0.001);
//     ASSERT_FALSE(scanner.isDone());

//     ASSERT_EQ(commaToken, scanner.next());
//     ASSERT_FALSE(scanner.isDone());

//     ASSERT_NEAR(0.26, scanner.nextDouble(), 0.001);
//     ASSERT_FALSE(scanner.isDone());

//     // end first point
//     ASSERT_EQ(rightParenthesisToken, scanner.next());
//     ASSERT_FALSE(scanner.isDone());

//     ASSERT_EQ(commaToken, scanner.next());
//     ASSERT_FALSE(scanner.isDone());

//     // second point
//     ASSERT_EQ(leftParenthesisToken, scanner.next());
//     ASSERT_FALSE(scanner.isDone());

//     ASSERT_NEAR(-4.83, scanner.nextDouble(), 0.001);
//     ASSERT_FALSE(scanner.isDone());

//     ASSERT_EQ(commaToken, scanner.next());
//     ASSERT_FALSE(scanner.isDone());

//     ASSERT_NEAR(0.73, scanner.nextDouble(), 0.001);
//     ASSERT_FALSE(scanner.isDone());

//     // end second point
//     ASSERT_EQ(rightParenthesisToken, scanner.next());
//     ASSERT_FALSE(scanner.isDone());

//     // end vector
//     ASSERT_EQ(rightParenthesisToken, scanner.next());
//     ASSERT_FALSE(scanner.isDone());

//     // end circle
//     ASSERT_EQ(rightParenthesisToken, scanner.next());
//     ASSERT_TRUE(scanner.isDone());
// }

// TEST_F(ScannerTest, ScannerShouldThrowExceptionWhenIsDone)
// {
//     std::string inputString = "Circle";
//     Scanner scanner(inputString);

//     ASSERT_FALSE(scanner.isDone());
//     ASSERT_EQ(circleToken, scanner.next());
//     ASSERT_TRUE(scanner.isDone());
//     ASSERT_ANY_THROW(scanner.next());
//     ASSERT_ANY_THROW(scanner.nextDouble());
// }
