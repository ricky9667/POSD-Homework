#include <string>
#include "../../src/builder/scanner.h"

class ScannerTest : public ::testing::Test
{
protected:
    const std::string vectorToken = "Vector";
    const std::string circleToken = "Circle";
    const std::string leftParenthesisToken = "(";
    const std::string rightParenthesisToken = ")";
    const std::string commaToken = ",";

    void SetUp() {}

    void TearDown() {}
};

TEST_F(ScannerTest, NextShouldWorkExpectedly)
{
    std::string inputString = "Circle ()";
    Scanner scanner(inputString);

    ASSERT_EQ(circleToken, scanner.next());
    ASSERT_EQ(leftParenthesisToken, scanner.next());
    ASSERT_EQ(rightParenthesisToken, scanner.next());
}

TEST_F(ScannerTest, NextDoubleShouldWorkExpectedly)
{
    std::string inputString = "4.86, 1.323";
    Scanner scanner(inputString);

    ASSERT_NEAR(4.86, scanner.nextDouble(), 0.001);
    ASSERT_EQ(commaToken, scanner.next());
    ASSERT_NEAR(1.323, scanner.nextDouble(), 0.001);
}

TEST_F(ScannerTest, IsDoneShouldWorkExpectedly)
{
    std::string inputString = "Circle (Vector ((-4.28, 0.26), (-4.83, 0.73)))";
    Scanner scanner(inputString);

    // circle
    ASSERT_EQ(circleToken, scanner.next());
    ASSERT_FALSE(scanner.isDone());

    ASSERT_EQ(leftParenthesisToken, scanner.next());
    ASSERT_FALSE(scanner.isDone());

    // vector
    ASSERT_EQ(vectorToken, scanner.next());
    ASSERT_FALSE(scanner.isDone());

    ASSERT_EQ(leftParenthesisToken, scanner.next());
    ASSERT_FALSE(scanner.isDone());

    // first point
    ASSERT_EQ(leftParenthesisToken, scanner.next());
    ASSERT_FALSE(scanner.isDone());

    ASSERT_NEAR(-4.28, scanner.nextDouble(), 0.001);
    ASSERT_FALSE(scanner.isDone());

    ASSERT_EQ(commaToken, scanner.next());
    ASSERT_FALSE(scanner.isDone());

    ASSERT_NEAR(0.26, scanner.nextDouble(), 0.001);
    ASSERT_FALSE(scanner.isDone());

    // end first point
    ASSERT_EQ(rightParenthesisToken, scanner.next());
    ASSERT_FALSE(scanner.isDone());

    ASSERT_EQ(commaToken, scanner.next());
    ASSERT_FALSE(scanner.isDone());

    // second point
    ASSERT_EQ(leftParenthesisToken, scanner.next());
    ASSERT_FALSE(scanner.isDone());

    ASSERT_NEAR(-4.83, scanner.nextDouble(), 0.001);
    ASSERT_FALSE(scanner.isDone());

    ASSERT_EQ(commaToken, scanner.next());
    ASSERT_FALSE(scanner.isDone());

    ASSERT_NEAR(0.73, scanner.nextDouble(), 0.001);
    ASSERT_FALSE(scanner.isDone());

    // end second point
    ASSERT_EQ(rightParenthesisToken, scanner.next());
    ASSERT_FALSE(scanner.isDone());

    // end vector
    ASSERT_EQ(rightParenthesisToken, scanner.next());
    ASSERT_FALSE(scanner.isDone());

    // end circle
    ASSERT_EQ(rightParenthesisToken, scanner.next());
    ASSERT_TRUE(scanner.isDone());
}

TEST_F(ScannerTest, ScannerShouldThrowExceptionWhenIsDone)
{
    std::string inputString = "Circle";
    Scanner scanner(inputString);

    ASSERT_FALSE(scanner.isDone());
    ASSERT_EQ(circleToken, scanner.next());
    ASSERT_TRUE(scanner.isDone());
    ASSERT_ANY_THROW(scanner.next());
    ASSERT_ANY_THROW(scanner.nextDouble());
}
