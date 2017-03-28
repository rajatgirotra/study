/*
Local variables are not initialized when they are created at method invocation, that is,
when the execution of a method is started. They must be explicitly initialized before being used.
The compiler will report attempts to use uninitialized local variables.
*/

public class TooSmartClass {
    public static void main(String[] args) {
        int weight = 10, thePrice;                   // Local variables

        if (weight <  10) thePrice = 1000;
        if (weight >  50) thePrice = 5000;
        if (weight >= 10) thePrice = weight*10;            // Always executed.
        //if(true) thePrice = 0;
        //if(1 > 0) thePrice = 0;
        System.out.println("The price is: " + thePrice);   // (1)
    }
}

/*
In Example 2.2, the compiler complains that the local variable thePrice used in the println statement at (1) may not be initialized.
However, it can be seen that at runtime the local variable thePrice will get the value 100 in the last if-statement,
before it is used in the println statement. The compiler does not perform a rigorous analysis of the program in this regard. 
It only compiles the body of a conditional statement if it can deduce the condition to be true. 
The program will compile correctly if the variable is initialized in the declaration, or if an unconditional assignment is made to the variable.
Replacing the declaration of the local variables in Example 2.2 with the following declaration solves the problem:

int weight = 10, thePrice = 0;         // Both local variables initialized.

*/
