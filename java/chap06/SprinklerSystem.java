import java.util.*;

class WaterSource {
   private String s;

   WaterSource() {
      System.out.println("WaterSource()");
      s = new String("Constructed");
   }

   public String toString() {
      return s;
   }
}

public class SprinklerSystem {
   private String value1, value2, value3, value4;
   private WaterSource ws;
   private int i;
   private float f;

   public String toString() {
      return "value1 = " + value1 + "\n" +
             "value2 = " + value2 + "\n" +
             "value3 = " + value3 + "\n" +
             "value4 = " + value4 + "\n" +
             "i      = " + i      + "\n" +
             "f      = " + f      + "\n" +
             "ws     = " + ws     + "\n";
   }

   public static void main(String[] args) {
      SprinklerSystem ss = new SprinklerSystem();
      System.out.println(ss.toString());
   }
}

   
          
