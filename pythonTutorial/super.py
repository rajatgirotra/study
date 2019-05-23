# the super() expression in python gives a delegate/proxy object of the base class. This object is used to call
# base class methods/ctor from derived class. Example:
# super().__init__(*args, **kwargs) will call base class ctor
# super().foo('abc') will call foo('abc') in the base class.

# super() can optionally take two arguments. The first is the name of the class where the search should begin.
# and the second argument is an instance of the class (mostly self).
# Example. If you have a class hierarchy A --> B --> C and both A and B define a function foo(name), in C you have
# class C(B):
#    def bar(name):
#        super().foo(name)
#        super(C, self).foo(name)
#        super(B, self).foo(name)

# then the first and second super() are just the same: they will call foo(name) in B. and the third super() call
# will call foo(name) in A. ie the parameter tells the name of class'es to be searched above the class specified 
# in the argument.

# MRO (method resolution order). In case of multiple inheritence, it can get really trick which base class ctor
# or method will be called when you use super(). This is decided by looking at __mro__ attribute of the class.
# this contains a list of classes that are searched in order. Lets take a look at a complex example:
# i am sure you'll work it out on your own.

class Rectangle:
    def __init__(self, length, width, **kwargs):
        print(f'Rectangle ctor called with length {length}, width {width}, kwargs: {kwargs}')
        self.length = length
        self.width = width
        super().__init__(**kwargs)

    def area(self):
        return self.length * self.width

    def perimeter(self):
        return 2 * self.length + 2 * self.width

# Here we declare that the Square class inherits from
# the Rectangle class
class Square(Rectangle):
    def __init__(self, length, **kwargs):
        print(f'Square ctor called with length {length}, kwargs: {kwargs}')
        super().__init__(length=length, width=length, **kwargs)

class Cube(Square):
    def surface_area(self):
        face_area = super().area()
        return face_area * 6

    def volume(self):
        face_area = super().area()
        return face_area * self.length

class Triangle:
    def __init__(self, base, height, **kwargs):
        print(f'Triangle ctor called with base {base}, height {height}, kwargs: {kwargs}')
        self.base = base
        self.height = height
        super().__init__(**kwargs)  # will call object ctor based on __mro__

    def tri_area(self):
        return 0.5 * self.base * self.height

class RightPyramid(Square, Triangle):
    def __init__(self, base, slant_height, **kwargs):
        print(f'RightPyramid ctor called with base {base}, slant_height {slant_height}, kwargs: {kwargs}')
        self.base = base
        self.slant_height = slant_height
        kwargs["height"] = slant_height
        kwargs["length"] = base
        super().__init__(base=base, **kwargs) # will call Square ctor based on __mro__

    def area(self):
        base_area = super().area()
        perimeter = super().perimeter()
        return 0.5 * perimeter * self.slant_height + base_area

    def area_2(self):
        base_area = super().area()
        triangle_area = super().tri_area()
        return triangle_area * 4 + base_area

if __name__ == "__main__":
    pyramid = RightPyramid(base=2, slant_height=4)
    print(f'RightPyramid.__mro__: {RightPyramid.__mro__}')
    print(f'Area {pyramid.area()}')
    print(f'Area {pyramid.area_2()}')
