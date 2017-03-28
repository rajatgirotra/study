/*
 * Please read SQLString.java first
 */

package main;

public @interface SQLInteger {

    public String name() default "";
    Constraints constraints() default @Constraints;
}

/*
Just for your information, if you want to make the default Constraints attributes with the uniqueness attribute
set to true, you write

public @interface Uniqueness {
    Constraints constraints() default @Constraints(unique=true);
}

Next let us write a simple java bean class Member with firstName, lastName, age and handle fields.
firstName, lastName and handle are String fields and age is Integer.
Also there is a static integer to keep  the memberCount. and getters() and setters().

 Please read Member.java next

*/