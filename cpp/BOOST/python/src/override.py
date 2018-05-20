from override_ext import *

obj = Integer()
print('obj created with default ctor, value: %s' % obj.value)

obj1 = Integer(-100)
print('obj1 created with default ctor, value: %s' % obj1.value)

print('obj + obj1, value: %s' % (obj+obj1).value)
print('obj + 100, value: %s' % (obj+100).value)

print('obj - obj1, value: %s' % (obj-obj1).value)
print('obj - 100, value: %s' % (obj-100).value)

obj += 100
print('obj += 100, value: %s' % obj.value)
obj -= 200
print('obj -= 200, value: %s' % obj.value)

print ('Integer(200) < Integer(300): %s' % (Integer(200) < Integer(300)))