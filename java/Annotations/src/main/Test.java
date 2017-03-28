/*
 * Please read Testable.java first
 * Here we define the @Test annotation.
 * 
 * 1] the definition of an annotation is just like an interface except that you have the @ in it.
 * 2] An annotation definition requires meta-annotations. Here we use:
 *     a) @Target which tells where this annotation can be applied: to a method, field, c'tor, package etc.
 *     b) @Retention which tells how long the annotation information is kept: in the source code, in class files,
 *        or during runtime.
 */
package main;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

//@Target(ElementType.FIELD) //Uncommen this to see the error in Testable.java
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface Test {
}

/*
You can also declare parameters for your annotations: something like
 @Test(paramterName1 = parameterValue1, parameterName2 = parameterValue2)
 these look like methods in your annotation interface. We'll come to this shortly. 
 
 AN ANNOTATION WITHOUT ELEMENTS IS CALLED MARKER ANNOTATION.
 
 Please read UseCase.java next.
*/