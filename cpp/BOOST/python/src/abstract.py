import abstract_ext
import copy


class Circle(abstract_ext.Shape):
     def draw(self):
         print("Circle::draw()")


shape = Circle()

abstract_ext.call_draw(shape)

