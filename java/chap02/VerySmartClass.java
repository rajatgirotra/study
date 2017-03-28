public class VerySmartClass {
    public static void main(String[] args) {
        String importantMessage;       // Local reference variable
        //String importantMessage = null;       // Local reference variable
        //String importantMessage = "Initialize before use!";       // Local reference variable

        System.out.println("The message length is: " + importantMessage.length());
    }
}

/*

In Example 2.3, the compiler complains that the local variable importantMessage used in the println statement may not be initialized. 
If the variable importantMessage is set to the value null, the program will compile. However, at runtime, a NullPointerException 
will be thrown since the variable importantMessage will not denote any object. 
The golden rule is to ensure that a reference variable, whether local or not, is assigned a reference to an object before it is used, 
that is, ensure that it does not have the value null. The program compiles and runs if we replace the declaration with the following declaration, 
which creates a string literal and assigns its reference to the local reference variable importantMessage:

String importantMessage = "Initialize before use!";
*/


