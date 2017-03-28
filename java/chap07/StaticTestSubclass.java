class StaticTest
{
   public static void doIt()
   {
      System.out.println("StaticTest.doIt()");
   }
 
   public void instanceDoIt()
   {
      System.out.println("StaticTest.instanceDoIt()");
   }
}
 
public class StaticTestSubclass extends StaticTest
{
   public static void main(String[] args)
   {
      StaticTest s = new StaticTestSubclass();
      s.doIt();
      s.instanceDoIt();
   }
 
   public static void doIt()
   {
      System.out.println("StaticTestSubclass.doIt()");
   }
 
   public void instanceDoIt()
   {
      System.out.println("StaticTestSubclass.instanceDoIt()");
   }
}
 
/* Output
StaticTest.doIt()
StaticTestSubclass.instanceDoIt()

As you can see, dynamic binding is only used with the instance method, not the static method. That's because only the instance method is overridden. The static method is hidden. There is a distinct difference.
static methods can not be overridden only hidden. The difference is that hidden methods do not participate in polymorphism.

*/

