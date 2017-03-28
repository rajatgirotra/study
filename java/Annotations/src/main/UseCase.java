/*
 * Please read Test.java first
 * 
 * Here we create a new annotation called UseCase, which can take two parameters
 * 1] an integer id
 * 2] a string description
 * 
 * Each method which contains this annotation means that it covers some business use case.
 * This way the program manager can easily see how many use cases are implemented.
 */

package main;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

import java.lang.annotation.Target;

@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface UseCase {
    public int id();
    public String description() default "No description";
}

/*
The good thing is that parameters will now be type-checked by the compiler. because it knows that id
is integer and description is string.
Next lets use this annotation. Please read PasswordUtils.java next
*/