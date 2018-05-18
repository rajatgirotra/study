import data_member_ext

obj = data_member_ext.Var('pi')
obj.value = 3.14
print('Value of %s is around %s' % (obj.name, obj.value))

# cannot modify name
obj.name = 'e'

obj = data_member_ext.BetterVar('pi')
obj.value = 3.14
print('Value of %s is around %s' % (obj.name, obj.value))
# cannot modify name
obj.name = 'e'
