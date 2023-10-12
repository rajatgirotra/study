Method Overloading
1) instance or static member functions must have the same name
2) they must have different set of parameters
3) Return type may be same or different. It doesnt matter
4) access specifier ( public, private etc) may be same or different. it doesnt matter
5) overloaded functions may throw the same or different checked or unchecked exceptions. it doesnt matter
Known as compile time polymorphism in Java.

Method Overriding
1) instance member functions must have same name and signature
2) Good to use @Override annotation.
3) The return type can be a subclass of the parent class.
4) Overriden methods cannot have more restrictive access specifier.
5) ctor, final methods, and private methods cannot be overriden
6) cannot throw a new or a broader checked exception.
7) Known as run-time polymorphism as JVM decides at run time which method to call.

Override Example:
=================
Base class has:

protected Object clone() throws CloneNotSupportedException {
    return super.clone();
}

Sub class overrides
@Override
public Person clone() {
    return new Person(some args);
}

protected changed to public during overriding --> That's ok.
return type of Object changed to Person --> That's ok, as Person is subclass of Object.
exception clause ommited --> That's ok as well.

Read Cylinder.java next