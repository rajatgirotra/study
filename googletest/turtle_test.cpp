#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "turtle_mock.hpp"
#include "painter.hpp"
using namespace std;
using testing::_;
using testing::Ge;
using namespace testing;
using testing::InSequence;

TEST (TurtleTests, TestOne)
{
    TurtleMock mock;
    EXPECT_CALL(mock, PenDown()).Times(1);

    Painter p(mock);
    p.TestOne();
}

/*
 By default, when a mock method is invoked, Google Mock will search the expectations in the reverse order they are defined,
 and stop when an active expectation that matches the arguments is found (you can think of it as "newer rules override older ones.").
*/
TEST (TurtleTests, TestTwo)
{
    TurtleMock mock;
    EXPECT_CALL(mock, Forward(_));
    EXPECT_CALL(mock, Forward(20)).Times(2);
    Painter p(mock);
    p.TestTwo();
}

TEST (TurtleTests, TestThree)
{
    //Strange. This test fails because we call Forward thrice with argument 20.
    //Whether you try AtLeast or AtMost, in both cases it fails. Its because the expection
    //is still kept alive. Read carefully the resultant error on command-line
    //and you'll understand what i am saying. Google mock always first matches with the last expectation matched
    //They call it that Expectations are Sticky
    TurtleMock mock;
    EXPECT_CALL(mock, Forward(_));
    //EXPECT_CALL(mock, Forward(20)).Times(AtMost(2));
    //EXPECT_CALL(mock, Forward(20)).Times(AtLeast(2));
    EXPECT_CALL(mock, Forward(20)).Times(2);
    Painter p(mock);
    p.TestThree();
}

TEST (TurtleTests, TestFour)
{    
    TurtleMock mock;
    //Also expectations dont have to be ordered.
    //in painter.TestFour, we call Forward(20), Forward(0), Forward(20)
    //but the test passes. So Expectation can be matched in an unordered way
    EXPECT_CALL(mock, Forward(_));
    EXPECT_CALL(mock, Forward(20)).Times(2);
    Painter p(mock);
    p.TestFour();
}

TEST (TurtleTests, TestFive)
{    
    TurtleMock mock;
    //If you are really worried about expectation occurring in sequence
    //create an object of InSequence like shown below.
    {
        InSequence dummy;
        EXPECT_CALL(mock, Forward(_));
        EXPECT_CALL(mock, Forward(20)).Times(2);
    }
    //Note order is now as written
    Painter p(mock);
    p.TestFive();
}

TEST (TurtleTests, TestSix)
{    
    TurtleMock mock;
    //We want to make sure that GoTo is called exactly twice
    //to go to tehe origin(0,0)
    //and we want to ignore any other instructions it receives.
    //Note order is still the reverse
    EXPECT_CALL(mock, GoTo(_,_)).Times(AnyNumber());
    EXPECT_CALL(mock, GoTo(0,0)).Times(2);
    Painter p(mock);
    p.TestSix();
}

TEST (TurtleTests, TestSeven)
{
    TurtleMock mock;
    //Test your understanding
    //what does the following code do    
    using testing::Return;
    for(int i = 5; i > 0; --i)
        EXPECT_CALL(mock, GetX()).WillOnce(Return(10*i));
    //What expectation is really set here.
    Painter p(mock);
    p.TestSeven();
}
//Actually what you are doing is saying
/*
EXPECT_CALL.WillOnce(50);
EXPECT_CALL.WillOnce(40);
EXPECT_CALL.WillOnce(30);
EXPECT_CALL.WillOnce(20);
EXPECT_CALL.WillOnce(10);

Now the first time you call. it is ok and returns 10.
But the next time, the expectation is still active ie sticky, So it will always fail
saying that WillOnce() should only be called once. So basically it the other EXPECT_CALL
dont server any purpose. What you really need to do is retire the expectation after it gets called
*/

TEST (TurtleTests, TestEight)
{
    TurtleMock mock;
    //Test your understanding
    //what does the following code do    
    using testing::Return;
    for(int i = 5; i > 0; --i)
        EXPECT_CALL(mock, GetX()).WillOnce(Return(10*i)).RetiresOnSaturation();
    //What expectation is really set here.
    Painter p(mock);
    p.TestEight();
}

/* Or better still if you are worried about sequence
   use InSequence
*/
TEST (TurtleTests, TestNine)
{
    TurtleMock mock;
    using testing::Return;
    {
        InSequence dummy;
        for(int i = 1; i <= 5; ++i)
            EXPECT_CALL(mock, GetX()).WillOnce(Return(10*i)).RetiresOnSaturation();
    }
    //What expectation is really set here.
    Painter p(mock);
    p.TestNine();
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
