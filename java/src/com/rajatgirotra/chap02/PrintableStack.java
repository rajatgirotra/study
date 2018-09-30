package com.rajatgirotra.chap02;

public class PrintableStack extends CharStack {
    public PrintableStack(int capacity) {
        super(capacity);
    }

    public void popAndPrintStack() {
        while(!isEmpty()) {
            System.out.print(pop());
        }
        System.out.println();
    }
}
