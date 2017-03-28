#!/usr/bin/env python
from bd2 import Base, Derived, b, d, factory


def takePointer(baseP):
    baseP.setValue(10)
    print(baseP.getValue())

# Simple with base
bo = Base(3)
print(bo.getValue())
bo.setValue(6)
print(bo.getValue())

# simpe with derived
do = Derived(5)
print(do.getValue())
do.setValue(2)
print(do.getValue())

# b takes a Base* so we can pass bo or do
b(bo)
b(do)

# d takes a Derived* so we can pass only do
# d(bo)  # will error
d(do)

print('bo is of type', type(bo),
      # Base is derived from Boost.Python.instance
      'Class Name is ', type(bo).__name__,
      ' it bases ', type(bo).__bases__)

print('do is of type', type(do),
      'Class Name is ', type(do).__name__,
      ' it bases ', type(do).__bases__)

print('isinstance(bo, Base) ', isinstance(bo, Base))
print('isinstance(bo, Derived) ', isinstance(bo, Derived))

print('isinstance(do, Base) ', isinstance(do, Base))
print('isinstance(do, Derived) ', isinstance(do, Derived))


po = factory()
takePointer(po)
