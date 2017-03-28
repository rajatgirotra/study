# What are they?? You know what functions are. They have a single point of entry starting with the first line of code
# They have a single point of exit, where return is called or exception is raised. If function finished normally without
# an explicit return statement, a "return None" is implicitly implied. The function local variables are destroyed and all
# context is deleted.

# Generators are somewhat different. These are functions which have a "yield" statement (they might also have return statements).
# But what yield does is that it stores the function and its variables and remembers all context, so that next time the generator
# is called, it knows where to start off (basically after the yield statement).

# Whats the use u ask? Consider a function which takes a big list of integers and returns a list of all primes numbers in that list
# In main, the only use is to iterator over that list and do something with the next returned prime number. Very simple:

import math


def is_prime(number):
    if number > 1:
        if number == 2:
            return True
        if number % 2 == 0:
            return False
        for current in range(3, int(math.sqrt(number) + 1), 2):
            if number % current == 0:
                return False
        return True
    return False


def get_primes(input_list):
    return [number for number in input_list if is_prime(number)]

# Now suppose the input list is infinite or so big that you cannot keep in memory all at once.
# And lets suppose that you want to return the prime no only if it is greater than a given number.
# Or the sequence is non-ending and every time a function is called, it should return the next prime number in sequence
# Now how can you achieve the same with a function. You will have to remember every time what value you
# retuned from your function, and then continue from there. Also it becomes almost impossible to achieve this
# via a function. Here generators come in handy. Generators are functions that yield a value ie they give you a value
# and pass back control to you only temporarily and voluntary under the assumption that you will call the generator again
# soon. Generators functions are by default iterable, so can be and are most often used in for loop and other loop iterations.
# Because they are implicitly iterable, this means they implement the __next__ function() automatically.
# You can call the python function

# next (iterable, default) - Which calls __next__() on the iterable to return you the next value or the default
# if the iterable has exhausted. If no default is specified, the Iterator throws a StopIteration exception

# Lets see things in action now.
print (get_primes(range(500)))

# Next lets create the simplest generator
def small_generator():
    yield 1
    yield 2
    yield 3
    # There is an implicit return None here so the next for loop
    # prints 1, 2, 3 and then returns automatically

for value in small_generator():
    print(value)


# Another example, explicitly using next()
our_generator = small_generator()
print
print
print(next(our_generator, 0))
print(next(our_generator, 0))
print(next(our_generator, 0))
#print(next(our_generator)) # Will raise a StopIteration exception, as iterator has exhausted.
print(next(our_generator, 0)) # Calling with a default value is rather safe.
