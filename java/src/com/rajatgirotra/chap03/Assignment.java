package com.rajatgirotra.chap03;

class MyNumber {
    int i;
}

public class Assignment {
    public static void main(String[] args) {
        MyNumber m1 = new MyNumber();
        MyNumber m2 = new MyNumber();
        m1.i = 100; m2.i = 200;

        System.out.println("before");
        System.out.println("mi.i: " + m1.i + ", m2.i: " + m2.i);
        System.out.println("m1 == m2: " + (m1==m2));

        m1 = m2;

        System.out.println("after");
        System.out.println("mi.i: " + m1.i + ", m2.i: " + m2.i);
        System.out.println("m1 == m2: " + (m1==m2));

    }
}
