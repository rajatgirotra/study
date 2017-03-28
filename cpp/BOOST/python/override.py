#!/usr/bin/env python
import override


class Derived(override.BaseWrapper):
    def __init__(self):
        override.BaseWrapper.__init__(self)
        print "Creating derived Object"

    def f(self):
        print "Function f() returning 10"
        return 10


if __name__ == "__main__":
    obj = Derived()
    x = obj.f()
    print ('x is', x)
