# In python, there are multiple uses of the type keyword.
# 1. It gives you the type of the object.
print('1.0 is of type %s' % type(1.0))
print('HelloWorld is of type %s' % type('HelloWorld'))
print('6 is of type %s' % type(6))
print('float is of type %s' % type(float))

class Foo(object):
    pass
print('class Foo is of type %s' % type(Foo))

# 2.
# Notice above that type of float, class Foo, and all builtin and user defined types is "type".
# "type" here is a metaclass. Every builtin or user-defined type in python has a metaclass. The
# default metaclass is "type", so the type() function above gives you the name of the metaclass.
# You can specify your own metaclass with slightly different syntax in python 2 and python 3.

# Python 2
class Meta(type):
    pass

class P(object):
    __metaclass__ = Meta
    pass

# Python 3
#class P1(metaclass=Meta):
#    pass

# But what really is a metaclass. Just like an object instance is created using the name of the object; Similarly an object/class can be created by using a metaclass. I.e. you can create objects/classes  dynamically using a metaclass.
# The syntax for creating a class at runtime using a metaclass is 
# metaclass ('className', (), {})
# argument 1 is the string name you want to give to your class.
# argument 2 is a tuple of base classes of the class you are creating
# argument 3 is a dictionary of methods you want to define in your class.

def always_false(self):
    return False

RuntimeClazz = type('RuntimeClazz', (), {'always_false': always_false})

print(RuntimeClazz.__dict__)
print(RuntimeClazz().always_false())

# Ideally you would rarely want to create classes on the fly. But whenever you do you can use this syntax above.
