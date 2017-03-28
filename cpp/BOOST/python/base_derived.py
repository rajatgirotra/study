#!/usr/bin/env python
from base_derived import Base, Derived

# Simple with base
b = Base(3)
print(b.getValue())
b.setValue(6)
print(b.getValue())

# simpe with derived
d = Derived(5)
print(d.getValue())
d.setValue(2)
print(d.getValue())

