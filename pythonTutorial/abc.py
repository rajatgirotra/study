class A(object):
    def foo(self, param):
        print self
        print A


a = A()
a.foo(10)
