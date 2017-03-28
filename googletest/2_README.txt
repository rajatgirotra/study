Important Points
===============

1) Mock methods declared using MOCK_METHODn or MOCK_CONST_METHODn must always be public,
    even if the corresponding virtual functions in base class are protected or private.

2) If for some reason, you dont want to mock a method from base class, use the "using" directive
   to bring it in scope. Like:
   struct MockFoo : public Foo
   {
       using Foo:Add;
       public:
           MOCK_METHOD1(Add, int(Element x));
   };

3) If you have a template class, create mock methods using MOCK_METHODn_T or MOCK_CONST_METHODn_T macros
   template <typename Elem>
   class StackInterface
   {
       virtual ~StackInterface();

       public:
          virtual int GetSize() const = 0;
          virtual void Push(const Elem& elem) = 0;
   };
   
   template <typename Elem>
   class MockStack : public StackInterface<Elem>
   {
       public:
        MOCK_METHOD1_T(Push, void(const Elem& elem));
        MOCK_CONST_METHOD0_T(GetSize(), int());
   };

4) For Mocking a class which has no virtual functions, Just define a totally unrelated class
and MOCK the methods you need.
Then because there are no virtual functions and so no runtime polymorphism to decide which class to use,
the real one or mock one, you must decide this at compile time (ie using templates). Do this
class <MockOrReal>
class CreateObject(MockOrReal* object) {..}
So where ever you need to use Real Objects, wrap inside a template wrapper so you can test it.


4)) By default, if you call a function for which you have set no expectations, gmock will throw a wrning but the test will pass.
However, you can decide whether you want to switch off the warning (by using NickMock<>) or convert them into errors (using StrictMock<>)
Both NiceMock and StrictMock will be created as subclasses of MockFoo.
    TEST()
    {
        NickMock<MockFoo> foo("hi", 12); //will turn off warning. Similarly StrictMock will enable it.
        ...
    }
    
