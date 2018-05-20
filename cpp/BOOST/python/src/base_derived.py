from base_derived_ext import Base, Derived, factory, b, d

# Simple with base
base = Base(3)
print(base.value)
base.value = 10
print(base.value)

base.display()

# simpe with derived
derv = Derived(2.5, 10)
print(derv.dbl_value(), derv.value)
derv.value = -100
print(derv.value)

po = factory()
po.f()  # should call Derived::f()

b(po)
d(po)

