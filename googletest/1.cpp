#include <iostream>
#include <gtest/gtest.h>
using namespace std;

long factorial(const long& n)
{
    if (n < 0)
        return 0;
    if( n == 0)
        return 1;

    return n * factorial( n - 1 );
}

TEST(FactorialTest, HandlesZeroInput)
{
    ASSERT_EQ(1, factorial(0));
}

TEST(FactorialTest, HandlesPositiveInput)
{
    EXPECT_EQ(120, factorial(5));
    EXPECT_EQ(720, factorial(6));
    EXPECT_EQ(1, factorial(1));
    EXPECT_EQ(3628800, factorial(10));
}

TEST(FactorialTest, HandlesNegativeInput)
{
    ASSERT_EQ(0, factorial(-10)) << "function factorial does not handle negative nos. " << endl;
}

/*int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/
