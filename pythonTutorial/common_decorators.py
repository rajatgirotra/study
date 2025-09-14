# lets write some common decorators.
# @x
# def y(*args, **kwargs):
#    pass
# is same as: y = x(y)

import functools
import time

# a decorator that does implements the same function twice
def do_twice(func):
    @functools.wraps(func) # this just helps to keep the __name__ and __doc__ for the func() intact.
    def wrapper_do_twice(*args, **kwargs): # a decorator wrapper function will be named as wrapper_<func>.
        func(*args, **kwargs)  # accept *args, **kwargs so that func() can take 0 or more arguments
        return func(*args, **kwargs)
    return wrapper_do_twice

# a timer decorator that measures and prints the time taken by a function to execute.
def timer(func):
    """Print the runtime of the decorated function"""
    @functools.wraps(func)
    def wrapper_timer(*args, **kwargs):
        start_time = time.perf_counter()
        value = func(*args, **kwargs)
        end_time = time.perf_counter()
        run_time = end_time - start_time
        print(f'finished {func.__name__!r} in {run_time:.4f} secs') # !r use repr() instead of str() and .4f means 4 decimal points
        return value
    return wrapper_timer

# a debug decorator to print the arguments are return value
def debug(func):
    """Print the arguments and return value of the decorated function"""
    @functools.wraps(func)
    def wrapper_debug(*args, **kwargs):
        args_repr = [repr(a) for a in args]
        kwargs_repr = [f'{k}={v!r}' for k, v in kwargs.items()]
        signature = ", ".join(args_repr + kwargs_repr)
        print(f'calling {func.__name__}({signature})')
        value = func(*args, **kwargs)
        print(f'{func.__name__} returned {value!r}')
        return value
    return wrapper_debug

# let's try to write a decorator which can optionally take some arguments too.
# example: a decorator "repeat" which by default repeats twice, but can take an argument 'count' and repeats the function 'count' times.# basically, the thing to remember is that repeat(count=4) and repeat(func) both are to be supported so "func" could be none at times and we need to an if condition based on that "func" being None or not.
def repeat(func=None, *, count=2):
    assert count >=0, "repeat count cannot be zero or negative"
    def decorator(func):
       assert callable(func), f"expected callable, got {type(func).__name__}"
       @functools.wraps(func)
       def wrapper_repeat(*args, **kwargs):
           for i in range(count-1):
               func(*args, **kwargs)
           return func(*args, **kwargs)
       return wrapper_repeat

    if func is None:
        return decorator
    return decorator(func)

@repeat
def say_whee():
    print('Whee')

@repeat(3)
def dwim():
    print('Do not repeat!')

say_whee()
dwim()
