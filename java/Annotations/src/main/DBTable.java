/*
 * Please read Must_Read_2.txt java first
 */

package main;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface DBTable {
    public String name() default "";
}

/*
Please read Constraints.java first.
*/