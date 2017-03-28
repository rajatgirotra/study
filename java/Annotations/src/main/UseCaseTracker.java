/*
 * Please read PasswordUtils.java first.
 */

package main;

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class UseCaseTracker {

    public static void trackUseCases(List<Integer> useCases, Class<?> clazz) {
        for(Method m : clazz.getDeclaredMethods()) {
            UseCase uc = m.getAnnotation(UseCase.class);
            
            if(uc != null) {
                System.out.println("Found use-case: " + uc.id() + " " + uc.description());
                useCases.remove(new Integer(uc.id()));
            }
        }
        for(Integer i : useCases) {
            System.out.println("Warning: Use-case: " + i + " not found");
        }
    }
    
    public static void main(String[] args) {
        List<Integer> useCases = new ArrayList<Integer>();
        Collections.addAll(useCases, 47,48,49,50);
        trackUseCases(useCases, PasswordUtils.class);
    }
}

/*
We have an AnnotatedElement interface which basically defines the getAnnotation() method.
All of the classes Method, Class, Constructor, Field, Package implement this interface. The getAnnotation() method
basically returns the annotation object of the specified type.
We have seen only two types (int and String) as elements of the UseCase annotation. But we can use any of the below
types:

1] int, float, boolean etc.. (any of the primitive types)
2] String
3] Enums
4] Class
5] Annotations
6] Arrays of the above.

So you can say

public @interface @UseCase {
   int id();
   String description();
   Class whichClass();
   Enum whichEnum(); etc etc.
   Test whichTest();  //nested annotations, very useful feature, as you'll see.
}

Please read Must_Read_2.txt next
*/