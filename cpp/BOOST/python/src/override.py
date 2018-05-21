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

print('str(Integer): %s' % str(Integer(99)))
print('float(Integer): %s' % float(Integer(99)))
print('abs(Integer(-25)): %s' % abs(Integer(-25)))
print('pow(Integer(25), +2): %s' % pow(Integer(25), Integer(2)))

