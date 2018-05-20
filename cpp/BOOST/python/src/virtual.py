import virtual_ext


shape = virtual_ext.Shape()


class Circle(virtual_ext.Shape):
    def draw(self):
        print("Circle::draw()")


shape.draw()
shape = Circle()
shape.draw()
