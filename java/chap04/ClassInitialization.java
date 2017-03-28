/*

   Its interesting to note that creating a reference to a Class object using ".class" doesnt automatically initialize the Class object. There are actually three steps in preparing a class for use:

   1.  Loading, which is performed by the class loader. This finds the bytecodes (usually, but not necessarily, on your disk in your classpath) and creates a Class object from those bytecodes.

   2.  Linking. The link phase verifies the bytecodes in the class, allocates storage for static fields, and if necessary, resolves all references to other classes made by this class.

   3.  Initialization.
       3a) Execute static initializers in both base and derived classes.
       3b) Create an object and wipe it completely so everything is zero.
       3c) Go to base class (superclass)
           3c1) Run in line member initializers
           3c2) Run the c'tor
	   3d) Go to derived class
           3d1) Run in line member initializers
           3d2) Run the c'tor
   Initialization is delayed until the first reference to a static method (the constructor is implicitly static) or to a non-constant static field:

 */
//: typeinfo/ClassInitialization.java
import java.util.*;
class Initable {
    static final int staticFinal = 34;
    static final int staticFinal2 =
        ClassInitialization.rand.nextInt(1000);
    static {
        System.out.println("Initializing Initable");
    }
}
class Initable2 {
    static int staticNonFinal = 147;
    static {
        System.out.println("Initializing Initable2");
    }
}
class Initable3 {
    static int staticNonFinal = 74;
    static {
        System.out.println("Initializing Initable3");
    }
}
public class ClassInitialization {
    public static Random rand = new Random(47);

    public static void main(String[] args) throws Exception {
        Class initable = Initable.class;

        System.out.println("After creating Initable class ref");
        // Does not trigger initialization:

        System.out.println(Initable.staticFinal);
        // Does not trigger initialization: as staticFinal is a const field. Its declared final.

        System.out.println(Initable.staticFinal2);
        // Does trigger initialization: although statcFinal2 is declared final, it is assigned a value at runtime.
	// So this triggers the initialization.

        System.out.println(Initable2.staticNonFinal);
	//this triggers initialization as the static field is non-constant.

        Class initable3 = Class.forName("Initable3");
	// using Class.forName() always triggers initialization.

        System.out.println("After creating Initable3 ref");
        System.out.println(Initable3.staticNonFinal);
    }
}

