Very trivial.

public class Printer <T> {

};

public class Map <Key, Value> {

};

public class Map <T extends Animal> {
    // T extends Animal is a bounded generic. and Animal can be any class or interface.
};

// let say a class T extends Animal and implements Serializable. and you want your generic parameter to be any such class. Then you do
public class GenericClass <T extends Animal & Serializable>
// just remember that class should be first followed by interfaces.


// template functions are also very trivial.

public static <Key, Value> Value doSomething(Key key, Value value) {
    // do something..
    return value;
}


// generic wildcards.
Let say you have List<Cats> cats. and a function expects List<Object>
void do(List<Object> lst) {

}
calling do(cats); will result in compile time error. Allthough Cat is derived from Object, but List<Cat> doesnt derive from List<Object>,
 so its not possible. The workaround is to use a generic wildcard.

void do(List<?> lst) {
    // ? just means i am not sure the generic type of List, so basically allow everything.
}
or can also specify a bounded generic with wildcard
void do(List<? extends Animal> lst) {
    for(var item : lst) {
        item.makeNoise(); // this should work
    }
}

Another bounded generic is <T super Animal>
Lets assume we have the following hierarchy of classes.

Object -> Animal 
Animal -> Cat
Animal -> Dog
Cat -> Manx
Dog -> Terrier

public class MyClass<T super Cat> // this isn't allowed
{
    T obj; // basically T could be Cat, or Animal or Object
    // so if Animal impments makeNoise(), and T type if Object, how can makeNoise() be called?
    // that's why <T super Cat> is invalid.
}

See GenericsPlaygroud.java for more


