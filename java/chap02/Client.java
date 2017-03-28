public class Client
{

public static void main(String args[])
{
   // Create a stack
   PrintableCharStack stack = new PrintableCharStack(40);
  
   String str = "!no tis ot nuf era skcatS";
   int length = str.length();
   System.out.println("Original String = " + str);

   for(int i = 0; i < length; ++i)
      stack.push(str.charAt(i));

   System.out.print("Reversed String = ");
   stack.printStackElements();
   //while(!stack.isEmpty())
    //  System.out.print(stack.pop());

   System.out.println();
}
}

 
