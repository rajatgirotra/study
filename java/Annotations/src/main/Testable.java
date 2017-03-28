/*
 * Please read Must_Read_1.txt first.
 */
package main;

public class Testable {
    public void execute() {
        System.out.println("Executing..!!");
    }
    
    @Test
    void testExecute() {
        execute();
    }
}

/*
If you see above, you'll realize that the @Test annotation does not do anything by itself.
It only ensures that the Test annotation is defined somewhere in the java build path, otherwise
it will generate errors.

Please read main.Test.java next
*/ 