class A { int i; }

public class VarArgs {
   static void print(Object[] x) {
      for(int i = 0; i < x.length; i++)
         System.out.println(x[i]);
   }
   public static void main(String[] args) {
      print(new Object[] {
            new Integer(47), new VarArgs(),
            new Float(3.14), new Double(11.11)
            });
      print(new Object[] {"one", "two", "three" });
      print(new Object[] {new A(), new A(), new A()});
   }
}

/*
You can see that print( ) takes an array of Object, then steps through
the array and prints each one. The standard Java library classes produce
sensible output, but the objects of the classes created here: A and
VarArgs, print the class name, followed by an @ sign, and yet another
regular expression construct: \p{XDigit}, which indicates a hexadecimal
digit. The trailing + means there will be one or more hexadecimal digits.
Thus, the default behavior (if you dont define a toString( ) method for
your class, which will be described later in the book) is to print the class
name and the address of the object.
*/
