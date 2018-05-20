import abstract_ext
import copy


class Circle(abstract_ext.Shape):
     def draw(self):
         print("Circle::draw()")


shape = Circle()
shape.draw()

