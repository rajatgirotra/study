package com.rajatgirotra.chap03;

class Number {
   int i;
}

public class Equivalence {
    public static void main(String[] args) {
        Integer i1 = new Integer(47);
        Integer i2 = new Integer(47);
        Integer i3 = new Integer(-47);

        System.out.println("i1 == i2: " + (i1==i2));
        System.out.println("i1 != i2: " + (i1!=i2));
        System.out.println("i1.equals(i2): " + i1.equals(i2));
        System.out.println("i1.equals(i3): " + i1.equals(i3));

        String s = "Hello";
        String s2 = "Hello";
        String s3 = new String("Hello");
        String s4 = new String("Hello");
        String s5 = new String("Hello").intern();

        System.out.println("s == s2: " + s==s2); // s == s2 is not surrounded.
        System.out.println("s == s2: " + (s==s2)); // true
        System.out.println("s == s3: " + (s==s3)); // false
        System.out.println("s3 == s4: " + (s3==s4)); // false
        System.out.println("s3.equals(s4): " + s3.equals(s4)); // true
        System.out.println("s3 == s5: " + (s3==s5)); // false
        System.out.println("s == s5: " + (s==s5)); // true

        Number n1 = new Number();
        Number n2 = new Number();
        Number n3 = new Number();
        n1.i = n2.i = n3.i = 100;
        System.out.println("n1 == n2: " + (n1==n2));
        System.out.println("n1.equals(n2): " + n1.equals(n2));

    }
}

/* Trivial:
== compares references, since i1 and i2 are different references, they are unequal.
.equals() also by default compares references. So you need to override equals() for your class to compare values.
For Integer class, equals() is already overriden.

For string, s, s2 and s5 are all string literals so they are the same references from Java String pool.
Google Java String pool for more. the string intern() method returns a reference from the string pool. If no reference
exists, intern() will create one and then return it.

For your Number class, you never override equals(), so behavior is similar to ==
 */