package org.generics;

/* GenericsPlayground.java first */

import jnr.ffi.annotations.In;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ArrayAndGenerics {
    public static void main(String[] args) {
        int[] intArr1 = new int[10];
        int[] intArr2 = new int[10];
        String[] strArr1 = new String[10];

        var intArr1Class = intArr1.getClass();
        var intArr2Class = intArr2.getClass();
        var strArr1Class = strArr1.getClass();
        /* primitive or non-primitive, arrays in java also have a corresponding Class object */
        System.out.println("intArr1.getClass().getName(): " +  intArr1Class.getName());
        System.out.println("intArr2.getClass().getName(): " +  intArr2Class.getName());
        System.out.println("strArr1.getClass().getName(): " +  strArr1Class.getName());
        /* In fact, different array objects of the SAME type have the SAME class object */
        System.out.println("intArr1Class == intArr2Class: " + Boolean.toString(intArr1Class == intArr2Class));

        /* and array types even have Object class as their super type */
        System.out.println("intArr1.getClass().getSuperclass(): " +  intArr1Class.getSuperclass());

        array_covariance();
        generic_noncovariance();
    }

    public static void array_covariance() {
        // What does covariance mean?
        /* Covariance means two things
        1. An array of one type can hold objects of its own type and any of its child types.
        2. An arrayS of one type can be assigned to an array of its supertype.
        3. Although 2) is true, at run-time if you try to put some other child type of the supertype in the array, you will get an ArrayStoreException

        Arrays are reifiable types, i.e. JVM runtime has full information of the actual type of the array objects.
         */

        Number[] numArr1 = new Number[]{1, 2.0, 5.5f}; // Number array storing an Integer, Double, Float; as all are child types of Number
        System.out.println("-".repeat(30));
        System.out.println("array storing man different child types");
        Arrays.stream(numArr1).forEach(item -> {
            System.out.println(item.getClass().getSimpleName());
        });
        System.out.println("-".repeat(30));

        Integer[] intArr2 = new Integer[]{1, 2, 3, 4};
        Number[] numArr2 = intArr2; //Number is base of Integer
        try {
            numArr2[1] = 4.5; // run time exception if you try to store another type.
        }catch(ArrayStoreException e) {
            e.printStackTrace();
        }
    }

    public static void generic_noncovariance() {
        /* Generics are non reifiable types. This is because the generic type parameter is discarded after compilation.
        so the type information is erased. This can lead to heap corruption at runtime, so the compiler has to protect you at compile time only.
        so you can't do List<Number> o = new List<Integer>();
         */
        List<Integer> myInts = new ArrayList<>();
        myInts.add(1);
        myInts.add(2);
//        List<Number> myNums = myInts; // compile time error. Remember this was allowed in case of arrays

        // But what if really I want to get a List<Number> as argument in someFunction, and call someFunction with List<Integer>, List<Float>, List<Double> etc.
        // This is achieved using <? extends Number>. This is how we achieve covariance with generics
        List<? extends Number> intList = new ArrayList<Integer>();
        List<? extends Number> longList = new ArrayList<Long>();
        List<? extends Number> doubleList = new ArrayList<Double>();

        // clearly you can access intList, longList, doubleList as READ-ONLY only. Because at runtime, due to type erasure, JVM doesn't know what was the actual type of the ArrayList
//        intList.add(10); // compiler error

        // so how do you now write to the list? For that we use another keyword super.
        List<? super Number> numList = new ArrayList<Number>(); // but now you cannot read as everything in numList can only be safely treated as Object only.
        // But I can store Number or any of its child types.
        numList.add(10);
        numList.add(5.5);
        numList.add(10L);
        numList.add(30.f);
        numList.add(Long.valueOf(10));
    }
}

/* Please read MoreGenerics.java next */
/* Please read AnonymousInnerClassExample.java next */