/*
 * So you already read that you need a FunctionalInterface for lambda expression.
 * Lets talk about some of the important Functional interfaces in java which truly enable functional programming.
 * 
 * These are Function, Supplier, Consumer, Predicate.
 * 
 * These are defined like these
 * 
 * @FunctionalInterface
 * interface Function<T, R>
 * {
 *     R apply(T t); // maps a value of type T to type R.
 * }
 * 
 * @FunctionalInterface
 * interface Supplier<T>
 * {
 *     T get(); // is a producer of a value of type T
 * }
 * 
 * @FunctionalInterface
 * interface Consumer<T>
 * {
 *     void accept(T t); // is a consumer of a value of type T
 * }
 * 
 * @FunctionalInterface
 * interface Predicate<T>
 * {
 *     boolean test(T t); // accepts a value of type T and returns a boolean. (Its a boolean predicate)
 * }
 * Lets see how these are used.
 */
package generics;

public class FunctionalProgramming {
    
}
