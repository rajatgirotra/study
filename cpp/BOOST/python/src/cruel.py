import cruel_ext

vd = cruel_ext.value_decider() # with no arguments
print(vd.get_value(), vd.get_decision())

vd = cruel_ext.value_decider(-25) # using 1 argument c'tor
print(vd.get_value(), vd.get_decision())

vd = cruel_ext.value_decider(100, True) # using 2 argument c'tor
print(vd.get_value(), vd.get_decision())
