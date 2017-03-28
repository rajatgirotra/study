/*

Default Values for Fields
Default values for fields of primitive data types and reference types are listed in Table 2.14. The value assigned depends on the type of the field.

Table 2.14. Default Values Data Type
 Default Value
 
boolean
 false
 
char
 '\u0000'
 
Integer (byte, short, int, long)
 0L for long, 0 for others
 
Floating-point (float, double)
 0.0F or 0.0D
 
Reference types
 null
 


If no initialization is provided for a static variable either in the declaration or in a static initializer block (see Section 8.2, p. 336), it is initialized with the default value of its type when the class is loaded.

Similarly, if no initialization is provided for an instance variable either in the declaration or in an instance initializer block (see Section 8.2, p. 338), it is initialized with the default value of its type when the class is instantiated.

The fields of reference types are always initialized with the null reference value, if no initialization is provided.

Example 2.1 illustrates default initialization of fields. Note that static variables are initialized when the class is loaded the first time, and instance variables are initialized accordingly in every object created from the class Light.

*/

public class Light {
    // Static variable
    static int counter;      // Default value 0 when class is loaded.

    // Instance variables
    int     noOfWatts = 100; // Explicitly set to 100.
    boolean indicator;       // Implicitly set to default value false.
    String  location;        // Implicitly set to default value null.

     public static void main(String[] args) {
        Light bulb = new Light();
        System.out.println("Static variable counter: "     + Light.counter);
        System.out.println("Instance variable noOfWatts: " + bulb.noOfWatts);
        System.out.println("Instance variable indicator: " + bulb.indicator);
        System.out.println("Instance variable location: "  + bulb.location);
        return;
    }
}

/*

Output from the program:

Static variable counter: 0
Instance variable noOfWatts: 100
Instance variable indicator: false
Instance variable location: null

*/

