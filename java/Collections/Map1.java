// Please read Set2.java first
//: c11:Map1.java
// Things you can do with Maps.
import java.util.*;


public class Map1 {
    private static Collections2.StringPairGenerator geo = Collections2.geography;
    private static Collections2.RandStringPairGenerator rsp = Collections2.rsp;

    // Producing a Set of the keys:
    public static void printKeys(Map map) {
        System.out.print("Size = " + map.size() + ", ");
        System.out.print("Keys: ");
        System.out.println(map.keySet());
    }

    @SuppressWarnings("unchecked")
    public static void test(Map map) {
        // Strip qualifiers from class name:
        System.out.println(map.getClass().getName().replaceAll("\\w+\\.", ""));
        Collections2.fill(map, geo, 5);
        // Map has 'Set' behavior for keys:
        Collections2.fill(map, geo.reset(), 5);
        printKeys(map);
        // Producing a Collection of the values:
        System.out.print("Values: ");
        System.out.println(map.values());
        System.out.println(map);

        String key = CountryCapitals.pairs[4][0];
        String value = CountryCapitals.pairs[4][1];
        System.out.println("map.containsKey(\"" + key + "\"): " +
            map.containsKey(key));
        System.out.println("map.get(\"" + key + "\"): " + map.get(key));
        System.out.println("map.containsValue(\"" + value + "\"): " +
            map.containsValue(value));

        Map map2 = new TreeMap();
        Collections2.fill(map2, rsp, 5);
        map.putAll(map2);
        printKeys(map);
        key = map.keySet().iterator().next().toString();
        System.out.println("First key in map: " + key);
        map.remove(key);
        printKeys(map);
        map.clear();
        System.out.println("map.isEmpty(): " + map.isEmpty());
        Collections2.fill(map, geo.reset(), 25);
        // Operations on the Set change the Map:
        map.keySet().removeAll(map.keySet());
        System.out.println("map.isEmpty(): " + map.isEmpty());
    }

    @SuppressWarnings("unchecked")
    public static void main(String[] args) {
        //test(new HashMap());
        //test(new TreeMap());
        //test(new LinkedHashMap());

        //test(new IdentityHashMap());
        //test(new WeakHashMap());
    }
} ///:~
/*
Please read Must_Read_2.txt next
*/
