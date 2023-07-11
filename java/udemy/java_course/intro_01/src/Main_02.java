// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main_02 {
    public static void main(String[] args) {
        System.out.println("Byte size: " + Byte.SIZE + " bits, range (" + Byte.MIN_VALUE + " to " + Byte.MAX_VALUE + ")");
        System.out.println("Short size: " + Short.SIZE + " bits, range (" + Short.MIN_VALUE + " to " + Short.MAX_VALUE + ")");
        // default type for integer literals is int
        System.out.println("Int size: " + Integer.SIZE + " bits, range (" + Integer.MIN_VALUE + " to " + Integer.MAX_VALUE + ")");
        System.out.println("Long size: " + Long.SIZE + " bits, range (" + Long.MIN_VALUE + " to " + Long.MAX_VALUE + ")");
        System.out.println("Float size: " + Float.SIZE + " bits, range (" + Float.MIN_VALUE + " to " + Float.MAX_VALUE + ")");
        // default type for real literals is double
        System.out.println("Double size: " + Double.SIZE + " bits, range (" + Double.MIN_VALUE + " to " + Double.MAX_VALUE + ")");

        int maxIntValue = Integer.MAX_VALUE;
        maxIntValue += 1;
        System.out.println("Max integer value + 1 (to show an overflow): " + maxIntValue);

        int minIntValue = Integer.MIN_VALUE;
        minIntValue -= 1;
        System.out.println("Min integer value + 1 (to show an underflow): " + minIntValue);

        long l = 65536L; // get into habit of using L when initializing long. By default, a number literal is int.
//        short s = 32768; // Error. cannot initialize a value out of range.

        float f = 56.5f; // need to put f, because by default 56.5 is double.
        double d = 56.5d; // use of d is optional.

        // As a rule of thumb, stick to doubles.

        int complexNumber = 210_768_123; // same as 210,768,123. java allows underscore so it can be read easily.

        // why we need casting
        byte myMinByteValue = Byte.MIN_VALUE;

        // ERROR. Why?? The right hand side is an expression. The Java compiler never tries to evaluate the result of the expression.
        // and by default assumes that an expression result type is an int. So it complains you are converting from int to byte. So we need a cast
//        byte myNewByteValue = myMinByteValue/2;
        byte myNewByteValue = (byte)(myMinByteValue/2);

        // this is ok. as we are using literals and java compiler can evaluate the expression and see the result will fit in a byte.
        // so that's fine.
        byte oneMoreByte = (-128/2);

        int myIntValue = 5;
        float myFloatValue = 5; // no 5F?? because 5 is an int and is allowed to initialize a float or double.
        double myDoubleValue = 5;

        // However, prefer using BigDecimal in favor of floats and doubles. BigDecimal gives you more precise decimal results.

        // char type in Java uses two bytes. You can initialize it either with a character, or with its unicode value or its decimal value
        char d1 = 'D';
        char d2 = '\u0044';
        char d3 = 68;
        System.out.println(d1 + " " + d2 + " " + d3);

        // boolean has two values (true or false
        boolean isSleeping = true;
        Boolean isAwake = Boolean.FALSE;
        System.out.println("isSleeping: " + isSleeping + ", isAwake: " + isAwake.toString());

        // remember
        // the notation x -=y literally means x = (data type of x) (x - y). So x - y gives a double of 4.5 which when cast to int gives 4.
        int r = 10;
        r -= 5.5;
        System.out.println("the value of r is " + r + ".. Surprised??");

        // String object is immutable. Everytime you concatenate string objects. a new object is created and old one is destroyed automatically.
        // So it is not preferred way to create strings by concatenating. Rather it is preferred to use the StringBuilder class.
    }
}