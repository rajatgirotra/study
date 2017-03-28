#!/usr/bin/env python

import member_property

d = member_property.data("Price")
print (d.name, d.value)
d.value = 20
print (d.name, d.value)
# The below line should not be allowed.
# d.name = 'Cost'

p = member_property.property()
p.hours = 13
print(p.roHours)
#p.roHours = 2


p.set2(11.3, False)
print(p.set2)
