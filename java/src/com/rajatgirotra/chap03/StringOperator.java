package com.rajatgirotra.chap03;

public class StringOperator {
    public static void main(String[] args) {
        String s = " abcd ";
        int x = 0, y = 9, z = -1;
        System.out.println(s + x + y + z); // when concatinating with String, the other operand is also promoted to String

        System.out.println(x + s); // doesn't matter which side the operand is.
    }
}
