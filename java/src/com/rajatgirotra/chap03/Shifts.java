package com.rajatgirotra.chap03;

public class Shifts {
    public static void main(String[] args) {
        short s = 5;
        System.out.println("s << 1: " + (s << 1));
        System.out.println("s >> 1: " + (s >> 1));
        System.out.println("s << 2: " + (s << 2));
        System.out.println("s >> 2: " + (s >> 2));

        s = -1;
        s >>>= 1;
        System.out.println("s >>> 1: " + s);
    }
}

/*
Left Shift In C++14,
====================
for unsigned "a", a<<b = a * std::pow(2, b) modulo (MAX possible value for that type + 1)

for signed positive "a", a<<b = a * std::pow(2,b) if the unsigned version of that type can hold it, and then the big positive
number is converted back to signed; otherwise it is undefined.

for signed negative "a", a<<b = IS ALWAYS UNDEFINED; because negative's are represented by 1 in the MSB. So left shifting
can result in 0 or 1 in MSB depending on the number. So there is no deterministic behavior. ie undefined behavior.

Left Shift In Java
==================
Similar to C++




RIGHT SHIFT In C++14,
=====================
for unsigned "a", a>>b = Integer part of (a / std::pow(2, b));

for signed positive "a", a>>b = Integer part of (a / std::pow(2, b));

for signed negative "a", a>>b = IS IMPLEMENTATION DEFINED, but most systems do an arithmetic right shift. ie
for negative numbers, left padding is done with 1's. So that the answer remains negative.

RIGHT SHIFT In Java
===================
Similar to C++


Java defines another >>> operator, which means shift right without sign extension. ie always 0's are padded in the left.
Also called the unsigned right shift. There is one problem with >>> operator when dealing with short or bytes and combined with assignment.
Example:
short s = -1; 0xFFFF;
s >>>= 1;
when applying >>> operators, the value is promoted to int, then the shift is applied and then converted to short or byte again.

so s = 0xFFFF, when promoted to int becomes 0xFFFF FFFF, and when unsigned right shifted by 1, we get 0x7FFFFFFF,
this when converted back to short, the top 16 bits are truncated, so we get 0xFFFF again.

 */