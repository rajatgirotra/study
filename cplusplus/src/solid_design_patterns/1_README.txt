SOLID:
S: Single Responsibility principle (Self explanatory)
O: Open/Closed principle (classes, functions, modules) should be open for extension, but closed for modification.
L: Liskov substitution principle
I: Interface Segregation principle
D: Dependency Inversion principle

Single Responsibility and Open/Closed principles often collide.

Liskov substitution principle just means that "subtypes should be substitutable for base types".
We are talking about "Behavioral Subtyping" (i.e. IS-A relationship) which means:
1. Contravariance of method arguments in a subtype.
2. Covariance of return types in a subtype.
3. Preconditions cannot be strengthened in a subtype.
4. Postconditions cannot be weakened in a subtype.
5. Invariants of the super type must be preserved in a subtype.

Interface Segregation: Having many client interfaces is better than having one big interface.
Also use Strategy pattern here like:
1) class Shape which has a "void draw() = 0";
2) A DrawStrategy base class which has "virtual void draw() = 0;" and many subclasses like CanvasDraw, PortraitDraw etc.
3) Shape class will hold a pointer/reference to DrawStrategy and the draw() function will call the virtual draw() function.