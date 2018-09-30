package com.rajatgirotra.chap02;

public class LocalInitialization {
    public static void main(String[] args) {
        int weight = 10, price;

        if(weight < 10) price = 0;
        if(weight > 10) price = 100;
        if(weight == 10) price = 10;

//        if(true) price = 10;
//        else price = -10;

        System.out.println("price is: " + price);

    }
}

/*
  Why we get compilation error even though the compiler can see that weight==10 will be triggered?
  Java compiler will never evaluate non-constant expression at compile time. They will always be evaluated at run
  time. So we get an error that price may not be initialized.
 */

/*
The Java Language Standard states that unreachable statements should trigger compilation errors.
So why does:
    if(true)
        return;
    int x;
    not cause errors. The answer is that it depends on the compiler. Most optimising compilers will simply compile
    out unreachable code, so it wont be part of the class file itself. So no errors.
 */