# In general, we say that we should hide member variables in a class and expose getters and setters. However in python we say that member variables should be public; as it is more pythonic. Lets see. 

class P(object):
    def __init__(self, arg):
        self.__x = arg

    def get_x(self):
        return self.__x

    def set_x(self, arg):
        self.__x = arg

# How __x is private. In Python variables prefixed with underscore and double underscore have special meaning.
# We'll get to that later. The important thing is that we have getter and setters here.

p = P(42)
x = p.get_x()
y = p.get_x()
p.set_x(p.get_x() + p.get_x()) # how non-intutive and not pythonic.

# Lets try making member variables public

class P1(object):
    def __init__(self, arg):
        self.x = x


p1 = P1(42)
x1 = p1.x
y1 = p1.x
p1.x = p1.x + p1.x # this is pythonic.

# But what if we want the value of x to be always between 0 and 1000. If anyone sets -ive, we force it to 0. If anyone
# sets > 1000, we cap it to 1000. That is the whole reason we need encapsulation ie. the set_x() method.
# Here properties come into use. property() is actually a builtin function in python which returns a property object.
# property(fget=None, fset=None, fdel=None, doc=None). ie no arguments are mandatory.
# property = property() creates an empty property object.
# property.getter(get_x)
# property.setter(set_x).
# Lets see it in action

class P2(object):
    def __init__(self, arg = 0):
        self.x = arg  # here property x is getting set, so set_x will be called

    def get_x(self):
        if not hasattr(self, '_x'):
            raise AttributeError('Please set value before getting')
        return self._x

    def set_x(self, arg):
        if arg < 0:
            self._x = 0
        elif arg > 1000:
            self._x = 1000
        else:
            self._x = arg
        
    x = property(get_x, set_x)


p2 = P2()
print 'default value is %s' % p2.x
p2.x = 987
print 'value is %s' % p2.x
p2.x = 1030
print 'value is %s' % p2.x
p2.x = -10
print 'value is %s' % p2.x

# you can also use the @property decorator which is more ideal. See below:

class P3(object):
    def __init__(self, arg = 0):
        self.x = arg  # here property x is getting set, so set_x will be called

    @property  # means x = property(x) ie we are passing "x" as the the property getter
    def x(self):
        if not hasattr(self, '_x'):
            raise AttributeError('Please set value before getting')
        return self._x

    @x.setter # x is of type property, you here we are saying x = x.setter(x)
    def x(self, arg):
        if arg < 0:
            self._x = 0
        elif arg > 1000:
            self._x = 1000
        else:
            self._x = arg

p3 = P3()
print 'default value in p3 is %s' % p3.x
p3.x = 987
print 'value is %s' % p3.x
p3.x = 1030
print 'value is %s' % p3.x
p3.x = -10
print 'value is %s' % p3.x


class Magic(object):
    @property
    def __repr__(self):
        def inner():
            return 'It works!!'
        return inner

print (repr(Magic()))
