package com.rajatgirotra.chap02;

public class DefaultInitialization {
    private static int mCounter;

    private int mIntField = 100;
    private boolean mBoolField;
    private String mStrField;

    public static void main(String[] args) {
        DefaultInitialization di = new DefaultInitialization();
        System.out.println("static int field default value: " + DefaultInitialization.mCounter);
        System.out.println("instance int field declared value: " + di.mIntField);
        System.out.println("instance boolean field declared value: " + di.mBoolField);
        System.out.println("instance String field declared value: " + di.mStrField);
    }
}