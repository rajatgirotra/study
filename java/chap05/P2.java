import com.rajatgirotra.tools.*;

public class P2 {
   public static void main(String[] args) {
      P.rint("Available from now on..!!");
      P.rintln("");
      //P.rintln();
      //P.rintln(100);
      P.rintln("" + 100);
      P.rintln("" + 3.14159);
   }
}

/*
Notice that all objects can easily be forced into String representations by
putting them in a String expression; in the above case, starting the
expression with an empty String does the trick. But this brings up an
interesting observation. If you call System.out.println(100), it works
without casting it to a String. With some extra overloading, you can get
the P class to do this as well.

So from now on, whenever you come up with a useful new utility, you can
add it to your own tools or util directory.

*/  
