package com.rajatgirotra.chap02;

public class ArgsToMain {
    public static void main(String[] args) {
        if(args.length == 0) {
            System.out.println("No args provided");
        } else {
            System.out.println("Args:");
            for(int i = 0; i < args.length; ++i) {
                System.out.println(args[i]);
            }
        }
    }
}
