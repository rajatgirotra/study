package org.generics;

public class GenericConstraints<T> {
    T obj;

    public GenericConstraints(T val) {
        obj = val;
//        System.out.println(T.class);
    }

    public boolean isTypeAString(String s) {
        /*
         compilation error: java.lang.String cannot be safely cast to T
         instanceof is a runtime thing. For instanceof to work, the type T must be reifiable, which means that all information about the type
         must be available at runtime, but this is not the case with generic types.
         */
//        return s instanceof T;
        return false;
    }

    public T getNewInstance() {
        /*
        Same thing. cannot create an object at run-time, as type T is not reifiable.
        Later on, I will show you how the work-around for this problem.
         */
//        return new T();
        return null;
    }

    public String getClazz() {
        /*
        again same thing. type T is erased at run-time, so which Class object should T.class refer to at run time?
         */
//        return T.class.getName();
        return null;
    }

    public String getClazz2() {
        return obj.getClass().getName();
    }


    public static void main(String[] args) {
        GenericConstraints<Integer> gc = new GenericConstraints<>(10);
        System.out.println(gc.isTypeAString("Hello"));
        System.out.println("gc.getNewInstance() != null: " + gc.getNewInstance() != null);
    }
}
