from call_method_ext import *


class Derived(Base):

    def __init__(self):
        super(Derived, self).__init__()

    def class_name(self):
        return self.__class__.__name__


print('is_base(Base): %s' % is_base(Base()))


# Only uncomment if you understand the output from the above print statement
print()
print('is_base(Derived): %s' % is_base(Derived()))
print()
print('call_f(Base): %s' % call_f(Base()))
print()
print('call_f(Derived): %s' % call_f(Derived()))

