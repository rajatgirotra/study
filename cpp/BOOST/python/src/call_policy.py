from call_policy_ext import *

y_obj = get_Y();
z = get_Z_pointer();

x = foo(y_obj, z);
del z
print('z value: %s' % y_obj.z_value())  # yes, it prints garbage here; if i dont use with_custodian_and_ward
# and using with_custodian_and_ward fixes it (it prints 50 correctly).
# actually 'del z' will decrement the reference count, but not delete it. So it works correctly.
