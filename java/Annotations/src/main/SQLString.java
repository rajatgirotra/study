/*
 * Please read Constraints.java first
 */
package main;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
public @interface SQLString {

    int value() default 0;
    String name() default "";
    Constraints constraints() default @Constraints; //Note this carefully. how to use nested annotations.    
}

/*
Next we create another annotation SQLInteger which will map to NUMBER in database.
Please read SQLInteger.java next
*/