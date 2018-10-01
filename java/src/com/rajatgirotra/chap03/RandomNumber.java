package com.rajatgirotra.chap03;

import java.util.*;

public class RandomNumber {
    public static void main(String[] args) {
        Random rand = new Random();
        int i = rand.nextInt(300);
        int j = rand.nextInt(100);
        System.out.println("i: " + i);
        System.out.println("j: " + j);
        System.out.println("i+j: " + (i+j));
    }
}
