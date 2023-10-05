package org.example;

import java.util.ArrayList;
import java.util.List;

class Animal {
    public void makeNoise() {}
};

class Cat extends Animal {};

class Dog extends Animal {};

class Manx extends Cat {};

class Terrier extends Dog {};

class BoundedSuper<T extends Cat> {

}

class MyList<T extends Object> {

}

public class GenericsPlayground {
    public static void main(String[] args) {
        
        // List<Animal> animals0 = new ArrayList<Manx>(); // this isn't allowed as you already in 1_README.txt

        // so this is a valid workaround.
        // <? extends Animal> is READ-ONLY. See example below.
        @SuppressWarnings("unused")
        List<? extends Animal> animals1 = new ArrayList<Animal>();
        // animals1.add(new Cat); // error as <? extends Animal> is READ-ONLY
        @SuppressWarnings("unused")
        List<? extends Animal> animals2 = new ArrayList<Dog>();
        @SuppressWarnings("unused")
        List<? extends Animal> animals3 = new ArrayList<Terrier>();
        @SuppressWarnings("unused")
        List<? extends Animal> animals4 = new ArrayList<Cat>();
        @SuppressWarnings("unused")
        List<? extends Animal> animals5 = new ArrayList<Manx>();

        // <? super Dog> means ? can be Dog or any of its super type. So ? can be Dog, or Animal or Object,
        // but not Terrier or Cat or Manx
        // also <? super Dog> is MODIFIABLE
        List<? super Dog> dogs1 = new ArrayList<Dog>();
        dogs1.add(new Dog());
        @SuppressWarnings("unused")
        List<? super Dog> dogs2 = new ArrayList<Animal>();
        @SuppressWarnings("unused")
        List<? super Dog> dogs3 = new ArrayList<Object>();
        // List<? super Dog> dogs4 = new ArrayList<Terrier>(); // invalid
        // List<? super Dog> dogs0 = new ArrayList<Cat>();

        List<Object> objects = new ArrayList<Object>(); objects.add(new Object());
        List<Animal> animals = new ArrayList<Animal>(); animals.add(new Animal());
        List<Cat> cats = new ArrayList<Cat>(); cats.add(new Cat());
        List<Manx> manxCats = new ArrayList<Manx>(); manxCats.add(new Manx());
        List<Dog> dogs = new ArrayList<Dog>(); dogs.add(new Dog());
        List<Terrier> terrierDogs = new ArrayList<Terrier>(); terrierDogs.add(new Terrier());

        ext(animals); // OK
        ext(cats); // OK
        ext(manxCats); // OK
        ext(dogs);  // OK
        ext(terrierDogs); // OK
        // ext(objects); // NOT-OK, ext accepts any Animal or below.

        spr(cats); // OK
        spr(animals); // OK
        spr(objects); // OK
        // spr(manxCats); // spr accepts <? super Cat> i.e. Cat or above
        // spr(dogs);
        // spr(terrierDogs);
    }

    public static void ext(List<? extends Animal> list) {
        // extends applies READ-ONLY
        // so what can we really do here. The only thing is that we must treat list to be list<Animal>
        // and deal with it like that
        list.forEach(System.out::println);
    }

    public static void spr(List<? super Cat> list) {
        // <? super Cat> is MODIFIABLE. Treat list as nothing but List<Cat>
        // therefore you can add anything in the lst which is Cat and below in the Cat hierarchy.
        list.add(new Cat());
        list.add(new Manx());
        // list.add(new Animal()); // cannot add Animal to List<Cat>

        // how do you iterate now?? <? super Cat> means ? could be Cat, Animal, or Object.
        // So only iterating as Object is allowed.
        for(Object o : list) {
            System.out.println(o.getClass().getName());
        }
    }
}

/* Please read AnonymousInnerClassExample.java next */