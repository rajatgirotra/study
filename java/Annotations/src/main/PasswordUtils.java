/*
 * Please read UseCase.java first
 */

package main;

import java.util.List;

public class PasswordUtils {
    
    //null values are not allowed for non-primitive types, either here or as default values.
    //to get around this, you can use specific values, such as empty strings or negative values.
    //@UseCase(id = 46, description = null)
    public void dummyPasswordValidator() {
        
    }

    @UseCase(id = 47, description = "Password must contain atleast one numeric")
    public boolean validatePassword(final String password) {
        return password.matches("\\w*\\d\\w*");
    }
    
    @UseCase(id = 48)
    public String encryptPassword(String password) {
        return new StringBuilder(password).reverse().toString();
    }
    
    @UseCase(id = 49, description = "New Passwords can be equal to previously used ones")
    public boolean checkForNewPassword(List<String> prevPasswords, final String newPassword) {
        return !prevPasswords.contains(newPassword);
    }    
}

/*
 * Next I'll show you how we can use these annotations later.
 * We've already seen the 3 standard java annotations, @Override, @Deprecated and @SuppressWarnings.
 * Lets have a look at the 4 meta-annotations in java.
 * 
 *   @Target - i.e. where this annotation can be applied.
 *   @Retention - i.e. how long the annotation information is kept. Use the following possible values.
 *                 RetentionPolicy.SOURCE, RetentionPolicy.CLASS, RetentionPolicy.RUNTIME.
 *   @Documented - i.e. include this annotation in the java docs.
 *   @Inherited - Allow subclasses to inherit parent annotations.
 *   
 *   Most of the time, you'll define your own annotations and write your own processors to deal with them.
 *   using the annotations API which is an extension of the reflections API.
 *   
 *   Please read UseCaseTracker.java next.
 */
