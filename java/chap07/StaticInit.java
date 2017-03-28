import java.util.*;

class Base {
   static {
      System.out.println("Initialising static block in Base class");
   }
   public static int i;
}

class Derv extends Base {
   static {
      System.out.println("Initialising static block in Derv class");
   }
   public static final int VAL=9;
}

class StaticInit {
   public static void main(String[] args) {
      Class<?> cls = Base.class;
      System.out.println(Base.i);
      cls = Derv.class;      
   }
}

