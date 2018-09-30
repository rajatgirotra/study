package com.rajatgirotra.chap02;

public class CharStack {
    private char[] mStackArray;
    private int mTOS;

    private static int mCounter;

    public CharStack(int capacity) {
        mStackArray = new char[capacity];
        mTOS = -1;
        ++mCounter;
    }

    public void push(char c) {
        mStackArray[++mTOS] = c;
    }

    public char pop() {
        return mStackArray[mTOS--];
    }

    public char peep() {
        return mStackArray[mTOS];
    }

    public boolean isEmpty() {
        return (mTOS < 0);
    }

    public boolean isFull() {
        return (mTOS + 1 == mStackArray.length);
    }

    public static int instanceCount() {
        return mCounter;
    }
}
