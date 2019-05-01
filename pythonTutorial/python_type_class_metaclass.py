# In python, everything is an object. This means that variables, types like (int, str, float, list, dict etc), instances of classes, functions, classes (yes class is also an object as you will see in a bit) are all objects. Infact, functions and classes are first class objects. This means they can be passed around as function arguments, returned from functions, created at runtime and assigned to variables. Yes classes can be created at run time also as we will see.

# Also everything object has a class(you can say 'type' also, its the same thing). You can get the class/type of an object using object.__class__ or type(objects). Both will give you the same result.

class A(object):
    pass

def func_foo():
    pass

x = 1
y = 'str'

print A.__class__, type(A)
print func_foo.__class__, type(func_foo)
print x.__class__, type(x)
print y.__class__, type(y)

# We said before that class is also an object. Let's now see how to create a class at runtime.
def make_myklass(**kwargs):
    return type('MyClass', (object,), dict(**kwargs))

myklass_foo_bar = make_myklass(foo=2, bar=4)
print myklass_foo_bar.__class__, type(myklass_foo_bar)
# Create an instance of MyKlass
myklass = myklass_foo_bar()
print myklass.__class__, type(myklass), myklass.foo, myklass.bar

# A little about type keyword in python before we move to metaclasses.

# In python, there are multiple uses of the type keyword.
# 1. It gives you the type of the object. This you have already seen above too.
print('1.0 is of type %s' % type(1.0))
print('HelloWorld is of type %s' % type('HelloWorld'))
print('6 is of type %s' % type(6))
print('float is of type %s' % type(float))

class Foo(object):
    pass
print('class Foo is of type %s' % type(Foo))

# 2.
# Notice above that type/class of float, class Foo, class A, and all builtin and user defined types is "type".  So really "type" is the class of a class. That's what a metaclass is (class of class). That's the second usage. "type" is the default class of all classes or we say "type" is the default metclass. You can specify your own metaclass also with slightly different syntax in python 2 and python 3.

# Python 2 metaclass (must derive from the default "type" metaclass)
class Meta(type):
    pass

class P(object):
    __metaclass__ = Meta
    pass

# Python 3
#class P1(metaclass=Meta):
#    pass

# Lets now see the third use of the "type" keyword and metaclasses as they are related.

# But what really is a metaclass. Just like an object instance is created using the name of the object; Similarly an class can be created at runtime by using its metaclass. I.e. you can create classes dynamically using a metaclass.
# The syntax for creating a class at runtime using a metaclass is 
# metaclass ('className', (), {})
# argument 1 is the string name you want to give to your class.
# argument 2 is a tuple of base classes of the class you are creating
# argument 3 is a dictionary of methods/attributes you want to define in your class.

def always_false(self):
    return False

RuntimeClazz = type('RuntimeClazz', (), {'always_false': always_false}) # third usage, you already saw this above.

print(RuntimeClazz.__dict__)
print(RuntimeClazz().always_false())

# Ideally you would rarely want to create classes on the fly. But whenever you do you can use this syntax above.

# What else are metaclasses used for. Metaclasses can be used to control the creation and initialization of the class you are creating. When you say "type(name, (bases,), dict())" behind the scenes python calls two functions of your metaclass

# 1) MyKlass = MyMeta.__new__(MyMeta, name, (bases,), dict)  for creation
# 2) MyMeta.__init__(MyKlass, name, (bases,), dict)  for initialization
# Lets create a real example and then learn
# Note that an instance of MyMeta class is not created. So __init__ and __new__ are not member functions, rather __new__ looks like class method, and __init__ looks like a static method.

class MyMeta(type):
    def __new__(meta, name, bases, dct):
        print '----------------------------'
        print 'Allocating memory for class %s' % name
        print meta
        print bases
        print dct
        # delegate to super class now
        return super(MyMeta, meta).__new__(meta, name, bases, dct)

    def __init__(cls, name, bases, dct):
        print '----------------------------'
        print 'Initializing class %s' % name
        print cls
        print bases
        print dct
        # delegate to super class now
        return super(MyMeta, cls).__init__(name, bases, dct)

    # The __call__ method is called whenever you create an instance of MyKlass.
    def __call__(cls, *args, **kwargs):
        print '__call__ called when creating an instance of %s' % cls.__name__
        return super(MyMeta, cls).__call__(*args, **kwargs)

# The code in the Meta class is executed when python see's this class definition.
class MyKlass(object):
    __metaclass__ = MyMeta

    def foo(self, param):
        print 'MyKlass::foo() called'
        pass

    barattr = 2


myklass_1 = MyKlass()
print myklass_1.barattr
myklass_1.foo(10)
