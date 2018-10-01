package com.rajatgirotra.chap03;

public class FloatDouble {
    public static void main(String[] args) {
        //float f = 0.5; // decimal numbers are treated as doubles by default. So this line is an error as we are doing
        // a narrowing conversion. Either use type double, or use a trailing "f/F" to indicate that the decimal is a float.

        float f = 0.5f;
        //double f = 0.5;
        System.out.println("f: " + f);
    }
}
