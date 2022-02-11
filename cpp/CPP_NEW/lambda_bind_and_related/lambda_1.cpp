/* C++11 introduces lambda functions. You already know from BLL that lambda expression is nothing
 * but an unnamed function object
 *
 * Let's see how it is used in C++11.
 */
#include <iostream>
using namespace std;

int main()
{
    //A lambda expression starts with square brackets [] called lambda introducer, followed by optional arguments in round brackets(),
    //followed by mutable, followed by exception specification, followed by return type.
    //followed by code in curly braces {}, followed by function call operator ().
    // [] (arguments) mutable(optional)  exceptionSpec(optional) -> return_type { code } ();
    //
    [] {
        cout << "Hello World" << endl;
       }();

   //You can give your lambda function a name if you want, eg:
   auto lambda = [] { cout << "My Lambda function with a name " << endl; };
   //call it now
   lambda();

   auto l = [] (const string& str) { cout << str << endl;  return 5; };
   auto p =  l("Goodbye, cruel world");
   cout << p << endl;

   int x = 0;
   int y = 0;
   //If you want your lambda function to access variables defined before the lambda function,
   //you can either pass it by value or by reference like below.
   auto l1 = [] (int pX, int& pY) { 
                           cout << "X: " << pX << endl;
                           cout << "Y: " << pY << endl;
                           ++pX;
                           ++pY; 
                           };
   x = y = 42;
   l1(x, y);
   l1(x, y);
   cout << "Y (outside): " << y << endl;

   //The other way is to capture the outside scope inside the lambda introducer [], using
   // [=]  meaning capture the outside scope by value OR
   // [&]  meaning capture the outside scope by reference
   // this way is much more convenient and easy to use and less typing also.
   int a{};
   int b{};
   int c{};
   auto l2 = [=] {
                     cout << "Capture scope by Value: " << endl;
                     cout << "a: " << a << endl;
                     cout << "b: " << b << endl;
                     cout << "c: " << c << endl;
                     //++a; ++b; ++c; //This will report a compiler error, because you are passing the scope by value, so you cannot modify a, b, or c
                };
   a = 10;
   b = 20;
   c = 30;
   l2();

   //There is actually a big difference in the two approaches above.
   //In approach one, you are not passing scope, you are just passing copies of variables x and y, defined in outside scope. x and y are
   //not accessible inside the lambda function. Incrementing both pX and pY is not a problem.
   //
   //In approach two, you are passing the scope inside the lambda function, so you can access a, b, c inside it.
   //However, since it is passed using [=], it means it is passed as read only, so an ++a or ++b or ++c is an error.
   //
   //The third approach is to pass the scope by reference using [&]
   a = b = c = 0;
   auto l3 = [&] { 
                     cout << "Capture scope by Reference: " << endl;
                     cout << "a: " << a << endl;
                     cout << "b: " << b << endl;
                     cout << "c: " << c << endl;
                     ++a; ++b; ++c;
                 };

   a = 30; b= 30; c = 30;
   l3();
   cout << "a (outside): " << a << endl;
   cout << "b (outside): " << b << endl;
   cout << "c (outside): " << c << endl;
   a = 199;
   l3();
   cout << "a (outside): " << a << endl;
   cout << "b (outside): " << b << endl;
   cout << "c (outside): " << c << endl;

   //Another approach is that u still pass the outside scope by value, but pass it as mutable, so u will be able to modify it.
   //In this case, the scope is passed in a write mode but changes won't be visible after the lambda function.
   a = b = c = 0;
   auto l4 = [=] () mutable { 
                     cout << "Capture scope by value but mutable: " << endl;
                     cout << "a: " << a << endl;
                     cout << "b: " << b << endl;
                     cout << "c: " << c << endl;
                     ++a; ++b; ++c;
                 };

   a = 35; b= 35; c = 35;
   l4();
   l4(); //this will print 1 as a, b and c. This means that your lambda function becomes stateful by using mutable.
   cout << "a (outside): " << a << endl;
   cout << "b (outside): " << b << endl;
   cout << "c (outside): " << c << endl;
}

/*
So [=] means --> all variables in scope will be passed by value and the function object of the closure class will be const. So cannot modify any scope variables.
   [&] means --> all variables in scope will be passed by reference.
   [=] mutable means --> all variables in scope will be passed by value and the function object of the closure will be non-const.
*/
