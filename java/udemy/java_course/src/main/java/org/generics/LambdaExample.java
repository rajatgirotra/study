/*
 * A lambda is a jvm manufactured class which implements some interface.
 * This interface is special in the sense that it can only have a single abstract method (a method without a body).
 * If the interface has more than one abstract methods, we cannot create a lambda for it.
 * Such an interface is called a FuntionalInterface. There is even an annotation available to mark an interface
 * as FunctionalInterface, so compiler will enforce it.
 * 
 *  The lambda expression returns you a variable of the lambda class manufactured by the jvm.
 */
package org.generics;

@FunctionalInterface
interface Printer {
    public void print();
}

@FunctionalInterface
interface Printer2 {
    public String print(String suffix);
}


class Picture implements Printer {
    public void print() {
        System.out.println("Picture Printer");
    }
}


public class LambdaExample {

    public static void test(Printer printer) {
        printer.print();
    }

    public static void test2(Printer2 printer2) {
        System.out.println(printer2.print("!"));
    }

    public static void main(String[] args) {
        Picture picture = new Picture();
        picture.print();
        
        // instead of creating Picture class with print, we can create a lambda expression which returns a lambda variable
        Printer lambdaVariable = () -> {
            System.out.println("LambdaVariable printer");
        };

        // if a lambda expression has a single statement, {} are optional.
        Printer lambdaVariable2 = () -> System.out.println("LambdaVariable2 printer");

        // if a lambda expression has a single argument, the () surrounding the argument is optional
        // and if the lambda expression has a single statement, the result of the statement is returned by default without the need of an explicit 
        // return keyword.
        Printer2 lambdaVariable3 = suffix -> "Meow " + suffix;

        test(lambdaVariable);
        test(lambdaVariable2);

        test2(lambdaVariable3);

        // lets try to print the name of the lambda variable class
        System.out.println(lambdaVariable.getClass().getName()); // package.ClassName$$Lambda$1/<SomeAddress>
        System.out.println(lambdaVariable2.getClass().getName()); // package.ClassName$$Lambda$2/<SomeAddress>
        System.out.println(lambdaVariable3.getClass().getName()); // package.ClassName$$Lambda$3/<SomeAddress>
    }    
}

/*
 * If your interface has more than one abstract methods, you need to use an anonymous inner class.
 * Please read FunctionalProgramming.java next.
 */