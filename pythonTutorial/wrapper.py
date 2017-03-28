#!/usr/bin/env python

# We'll talk about update_wrapper and wraps function here.
# There is a limitation with the partial() function. The
# __name__ and __doc__ attributes of the partial object do not reflect
# the __name__ and __doc__ of the wrapper function. Infact partial does
# not have a __name__attribute at all. So to achieve that
# we have a function update_wrapper

# functools.update_wrapper(wrapper, wrapped, [assignments], [updations])
# the wrapper argument is a partial object. It can also be a function but
# it wont make sense as the __name__ and __doc__ will already be OK.
# eg: for a function foo, when you say bar=foo, then __name__ and __doc__
# of bar are the same as that for foo.

# wrapped is the function we are wrapping.
# [assignments] is by default
# functools.WRAPPER_ASSIGNMENTS (which is __name__, __doc__, __module__)
# ie copy these into the partial object
# [updations] is by default functools.WRAPPER_UPDATES (which is by default
# __dict__)
import functools

# define a function to show details of normal function
# partial function, and wrapper function.


def show_details(name, f):
    """ Show details of callable object f """
    print "%s" % name
    print "\tobject: %s" % f
    print '\t__name__: ',
    try:
        print "%s" % f.__name__
    except AttributeError:
        print "%s" % "no __name__"
    print "\t__doc__: %s" % repr(f.__doc__)
    if isinstance(f, functools.partial):
        print "\tfunc: ", f.func
        print "\targs: ", f.args
        print "\tkwords: ", f.keywords


def myfunc(a, b=2):
    """ Docstring for myfunc() """
    print "\tcalled myfunc() with (%s %s)" % (a, b)
    return


if __name__ == "__main__":

    # straight-forward function
    show_details("myfunc", myfunc)

    # create a partial
    p1 = functools.partial(myfunc, b=4)  # bind argument b to 4
    print
    show_details("partial with b=4", p1)  # note __name__ and __doc__ in output

    # use update wrapper to update __name__ and __doc__
    p1 = functools.update_wrapper(p1, myfunc)
    print
    show_details("partial with updated_wrapper with b=4", p1)

    # Now lets write a function (called as a decorator function)
    # which decorates argument f and returns the decorated function
    def simple_decorator(f):  # will take myfunc and bind some arguments
        # @functools.wraps(f)
        def decorated(a='decorated function', b=1):
            """ Decorated function """
            print '\t decorated:', (a, b)
            return f(a, b=b)
        # decorated = functools.update_wrapper(decorated, f)
        return decorated

    decorated_function = simple_decorator(myfunc)
    show_details("decorated_function", decorated_function)
    # Note how __name__ and __doc__ for myfunc have been lost.
    # Now go and enable update_wrapper in simple_decorator and see the diff.

    # The other way is to not call update_wrapper, rather just say
    # @wraps(f) which basically calls update_wrapper underneath for you.
    # so its much cleaner
