from call_method import *
import sys

print (sys.modules['call_method'])

# because the HeldType is actually Base_callback, when you create a Base()
# object, an object of Base_callback is created instead. So b is Base_callback under the hood.
print('\nCreating Base')
b = Base()
# The PyObject for b has a method class_name which we registered as a call to Base_callback::&base_name
# so it is used.
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


# What happens when is_base() if called.
# 1) The PyObject corresponding to b is holding Base_callback, so is_base() gets called in C++ with Base_callback object.
# 2) This call ends up in Base_callback::class_name(), where we use call_method on the same PyObject.
# 3) Now, This PyObject was created with "class_name" interface defined in BOOST_PYTHON_MODULE, so from class_name(),
# base_name is called; which calls Base::class_name(), you should get True.
# But here is the catch. call_method<> creates a local copy of PyObject (m_self) in our case, and calls base_name() on that copy
# That local copy gets destroyed when the call_method() function returns, so there is no way to get access to the const char*
# object in it. If you try to use it anyway. You get a dangling reference error.
# See this: http://www.boost.org/doc/libs/1_60_0/libs/python/doc/html/faq/i_m_getting_the_attempt_to_retur.html
# so the way out is to use shared_ptr as we'll see shortly.
# print(is_base(b))
