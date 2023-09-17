package annotations;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/* creating an annotation requires using @interface */
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@interface VeryImportant {
    // randomString is just like a class member variable. Dont let () at the end of randomString() mislead you.
    // its just the syntax for defining annotation arguments. And we have also provided a default value
    String randomString() default "Very Important Message";
}

// an annotation on a class method which can invoke the method immediately
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
@interface RunImmediately {
    public int times() default 3;
}

// an annotation on a class member
@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
@interface ImportantString {
}

@VeryImportant
public class SimpleAnnotation {

    @ImportantString
    public String randomString = "You have an important lesson to learn";

    public Double randomDouble;

    public static void main(String[] args) throws IllegalArgumentException, IllegalAccessException {
        // using annotation
        if(SimpleAnnotation.class.isAnnotationPresent(VeryImportant.class)) {
            System.out.println("This is an important class");
        } else {
            System.out.println("This is not an important class");
        }

        // get all the declared method on this class and call the ones which have the RunImmediately annotation
        var simpleannotation = new SimpleAnnotation();
        for(Method method : SimpleAnnotation.class.getDeclaredMethods()) {
            if(method.isAnnotationPresent(RunImmediately.class)) {
                for(int i = 0; i < method.getAnnotation(RunImmediately.class).times(); ++i) {
                    try {
                        method.invoke(simpleannotation);
                    } catch (IllegalAccessException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    } catch (IllegalArgumentException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    } catch (InvocationTargetException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    }
                }
                
            }
        }

        // using annotations on member variables.
        var fields = SimpleAnnotation.class.getDeclaredFields();
        for(var field : fields) {
            if(field.isAnnotationPresent(ImportantString.class)) {
                if(field.get(simpleannotation) instanceof String myString) {
                    System.out.println("Important String: " + myString);
                }
            }
        }
    }

    public void one() {
        System.out.println("one");
    }

    @RunImmediately(times = 2)
    public void two() {
        System.out.println("two");
    }

    @RunImmediately()
    public void three() {
        System.out.println("three");
    }

}