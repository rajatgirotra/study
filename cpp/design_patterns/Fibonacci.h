/*

Adapter takes one type and produces an interface to some other type. This is useful when youre given a library or piece of code that has a particular interface, and youve got a second library or piece of code that uses the same basic ideas as the first piece, but expresses itself differently. If you adapt the forms of expression to each other, you can rapidly produce a solution.

*/

#ifndef _FIBONACCIGENERATOR_H_
#define _FIBONACCIGENERATOR_H_ 1

class Fibonacci
{
private:
   int n;
   int val[2];

public:
   Fibonacci() : n(0)
   { 
      val[0] = val[1] = 0;
   };

   int operator() () 
   {
      int result = ( n >= 2 ? (val[0] + val[1]) : (n > 0) ? 1 : 0 );
      val[0] = val[1];
      val[1] = result;
      ++n;
      return result;
   }

   int count() const
   { return n; }
};
#endif
