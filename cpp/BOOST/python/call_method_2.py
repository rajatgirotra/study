from call_method_2 import *
import sys

print (sys.modules['call_method_2'])

print('\nCreating Base')
b = Base()
print (b.class_name()) 


class Derived(Base):
    def __init__(self):
        Base.__init__(self)
    # Oevrride class_name in C++ Base class
    def class_name(self):
        return self.__class__.__name__

print('\n\nCreating derived')
d = Derived()
print(d.class_name())
print('Done\n\n')


print(is_base(b))
print('\n\n')


# This wont work now. Because when call_method function returns, it find no ResultConvertor that can be used to convert the PyObject to shared_ptr<const char>
# So we'll need to see how we can solve this. Either by writing our own custom convertor, or some other way. I tries to use register_ptr_to_python() function,
# however, it requires that the argument to shared_ptr<> be a class and const char is a primitive.
print(is_base(d))
print('\n\n')

print('Destroying\n')
