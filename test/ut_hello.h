#include "../src/hello.h"

TEST(HelloTest, first)
{
    Hello h;
    ASSERT_EQ("Hello, POSD!", h.say());
}
