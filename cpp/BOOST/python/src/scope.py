import scope_ext

print("scope_ext.yes %s" % scope_ext.yes)

y = scope_ext.X.Y()
y.g()

print("scope_ext.no %s" % scope_ext.no)
