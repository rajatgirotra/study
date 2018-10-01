package com.rajatgirotra.chap03;

public class ValueOf {
    public static void main(String[] args) {
        Integer i1 = Integer.valueOf(100);
        Integer i2 = Integer.valueOf(100);
        System.out.println("i1==i2: " + (i1==i2));
    }
}
