/*
 * Please read DBTable.java first.
 * We'll encapsulate the following constraints in this annotation.
 * 1] Primary key constraint
 * 2] Not null constraint
 * 3] unique constraint
 * 
 * By default all constraints are false.
 */
package main;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
public @interface Constraints {

    boolean primaryKey() default false;
    boolean unique() default false;
    boolean allowNull() default false;
}

/*
Next we create an annotation SQLString. Fields with this annotation will be of type VARCHAR2() in the database.
Please read SQLString.java next
*/