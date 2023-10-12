POJO -> Plain Old Java Object. Just a class with instance variables and their getters and setters and may be a few more helpful function.
Also called a JavaBean or just Bean. A bean is just a POJO with some extra rules applied to it. Also called a Data Transfer Object (DTO).

See Student class which is a POJO. See how much boilerplate code there is in a POJO with 4 fields. To make things easy. Java 16 created a new
type Record. Its purpose is to replace the boilerplate code in POJO's, but it has some restrictions. Java calls them "plain data carriers".

See LPAStudent which is a record. It takes a parameter list and we give it the same parameter list as the Student class ctor.

Records created are immutable