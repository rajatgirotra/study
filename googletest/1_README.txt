Google test and google mock were so closely related that they got merged into one project. The project is hosted on GitHub

Let talk about Google Moack which allows you to create Mock classes and then write some expectations on them

Let say you have ABC called Turtle like this:

class Turtle {
  ...
  virtual ~Turtle() {}
  virtual void PenUp() = 0;
  virtual void PenDown() = 0;
  virtual void Forward(int distance) = 0;
  virtual void Turn(int degrees) = 0;
  virtual void GoTo(int x, int y) = 0;
  virtual int GetX() const = 0;
  virtual int GetY() const = 0;
};

Typically you'll have some class which implements this interface in your code.

You can generate a mock for this class, ie a class with virtual functions using google mock.
You can also create a mock for class with non-virtual methiods, but we'll come to that later.
How we do it. 

1) Create a file mock_turtle.cpp
2) Include gmock/gmock.h
3) Derive from Turtle
4) Use gmock MACROS "MOCK_METHODn" or "MOCK_CONST_METHODn" to create dummy implementations.

#include "gmock/gmock.h"
class MockTurtle : public Turtle
{
public:
    virtual ~MockTurtle() {}
    MOCK_METHOD0(PenUp, void());
    MOCK_METHOD0(PenDown, void());
    MOCK_METHOD1(Forward, void(int distance));
    ...
    MOCK_CONST_METHOD0(GetX, int());
    MOCK_CONST_METHOD0(GetY, int());
};


Next you create your test class and write a few tests using GoogleTest

#include "gmock/gmock.h"
#include "gtest/gtest.h"
using namespace testing; //google mocks testing namespace

TEST(PainterTest, Test_One)
{
// Create a MockTurtle class
MockTurtle turtle;

//Create expectations on the methods of the class, like how many times it will be called, with what arguments, etc etc.
//These expectations are checked when the MockTurtle object goes out of scope. ie when the PainterTest will end.
//So if you are allocating on the heap, make sure you destroy the object at the end. otherwise expectations will not be checked.
//Also expectations must be set initially 

EXPECT_CALL(turtle, PenDown()).Times(AtLeast(1)); //Both Times and AtLeast are from testing namespace
//Times is actually called the cardinality. See a few more examples below.

Painter painter(&turtle);

EXPECT_TRUE(painter.DrawCircle(0, 0,10));
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

//Another example for Cardinality
.Times(5)
.WillOnce(Return(100))
.WillOnce(Return(200))
.WillRepeatedly(Return(300))

//The above means that the function should be called 5 times, First time it should return 100, second time 200
and the rest of the times 300.

//So you saw above how to specify return values.
//What about arguments?? How do you specify what arguments your method will be called with. That's done using Matchers
//Eg:

EXPECT_CALL(turtle, Forward(100)); //ie. Forward should be called with argument 100
EXPECT_CALL(turtle, Forward(_)); // _ (underscors) is a special matcher meaning any argument is OK
EXPECT_CALL(turtle, Forward(Ge(200))); // Ge means Greater than equal to. Many more matchers are available in gmock.

Of course these mock objects are dummy objects, so they do not know what to return from the mock functions.
If the return type is a build-in type or pointer then gmock will return 0 automatically,
otherwise if it is a user defined type with a default c'tor gmock will return the default constructed value.
Otherwise you must specify what the function should return using the "Return" action you saw above like

WillOnce(Return(100)) etc..


