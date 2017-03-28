## Please read 19.modules.txt first
## we create a couple of functions in this module

def fib(n) :
   """ Prints all fibonacci numbers less than the given argument n. """
   a, b = 0, 1
   while(a < n) :
      print(a, end = ' ')
      a, b = b, a + b
   print()


def fib2(n) :
   """ Returns a list of all fibonacci numbers less than the given argument n. """
   a, b = 0, 1
   resultList = []
   while(a < n) :
      resultList.append(a)
      a, b = b, a + b
   return resultList

## A special python built in variable __main__ : This is a variable which is set to the name of the module when it is imported.
## So if you import fibo.py in any module and say print(fibo.__name__), it will print "fibo". But when the fibo.py is run directly using the command line
## like: python3 fibo.py, in that case, it is set to a special variable __main__. So the code below will execute only if this module is run directly,
## not when it is imported into another module.

if (__name__ == "__main__") :
   import sys ## import sys module, so that you can read the argument passed, if any
   fib(int(sys.argv[1]))

