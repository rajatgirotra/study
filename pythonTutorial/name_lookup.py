# How is name lookup performed in python.
# First remember that an object/class and and object/class instance both have their separate namespaces(dictionaries).
# Example:
class Foo:
    pass

f1 = Foo()
print('Class Foo dict %s' % Foo.__dict__)
print('Class instance f1 dict %s' % f1.__dict__)


# Lets take the example where you access a variable using "instancename.variablename"
# example: instance.foobar
# The rule is
# if 'foobar' in instance.__class__.__dict__ and 'foobar' is a data descriptor 
#     return instance.__class__.__dict__['foobar'].__get__(instance, Class)
# if instance.__dict__['foobar'] exists? If yes return it.
# else if 'foobar' in instance.__class__.__dict__ and 'foobar' is NOT a data descriptor.
#     return instance.__class__.__dict__['foobar'].__get__(instance, Class)
# else if 'foobar' in instance.__class__.__dict__? return it.
# else raise Attribute Error

# A class is a data descriptor if it has both __get__() and __set__() functions.
# A class is NOT a data descriptor if it has __get__() but not __set__() function.

# Example:
class Base(object):
    class_var = 1
    def foo(self, arg):
        self.i_var = arg
        class_var = 20 # doesnt refer too Base.class_var; instead is a local variable
        Base.class_var *= 1.5 # this is how you do it

b1 = Base()
b2 = Base()
print ('Base.class_var %s' % Base.class_var) # will give 1
print ('b1.class_var %s' % b1.class_var)  # will give 1
print ('b2.class_var %s' % b2.class_var)  # will give 1

b1.foo(10)
print (b1.i_var) # will give 10
b2.foo(100)
print (b2.i_var) # will give 100

print('After calling foo')
print ('Base.class_var %s' % Base.class_var)
print ('b1.class_var %s' % b1.class_var)
print ('b2.class_var %s' % b2.class_var)

print('b1 dict %s' % b1.__dict__)
print('b2 dict %s' % b2.__dict__)

# Modifying class attribute using an instance actually creates a copy of that attribute in the instance namespace
b1.class_var = -189
b2.class_var = -200

print('After modifying class_var using instances of Foo ')
print ('Base.class_var %s' % Base.class_var)
print ('b1.class_var %s' % b1.class_var)
print ('b2.class_var %s' % b2.class_var)

print('b1 dict %s' % b1.__dict__)
print('b2 dict %s' % b2.__dict__)
