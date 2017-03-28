// Read Must_Read_2.txt first.
import java.util.*;

class Book
{
   boolean checkedOut = false;

   Book(boolean check)
   {
      checkedOut = check;
   }
   
   void checkIn()
   {
      checkedOut = false;
   }

   void checkOut()
   {
      checkedOut = true;
   }

   public void finalize()
   {
      if(checkedOut)
         System.out.println("Book not checked in");
   }

   public static void main(String[] args)
   {
      new Book(true);
      System.gc(); // Force garbage collection and finalization
      return;
   }
}

