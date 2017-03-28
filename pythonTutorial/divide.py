#!/usr/bin/env python3

## Just like Java, python3 also has a finally clause which is executed in all cases (even in the face of an exception). Eg:
## Please read 33.exception.py first

def divide(x, y) :
    print('divding', x, 'by', y)
    try:
       result = x // y;
    except ZeroDivisionError as err:
        print('Dvide by zero error:', err)
    else:
        ## No exception has occurred
        print('result of', x, 'divided by', y, 'is', result)
    finally:
        print('Executing finally clause')

if (__name__ == "__main__") :
    import sys
    x, y = sys.argv[1:3]
    divide(int(x), int(y))


   
