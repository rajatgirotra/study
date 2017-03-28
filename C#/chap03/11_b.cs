//Using partial classes in C#

using System;
namespace Wrox.ProCSharp.chap03
{
  partial class MyPartialClass
  {
    public static int MethodTwo()
    {
       Console.WriteLine("This is MethodTwo() of the partial base class.");
       return -2;
    }
   
    public void foo()
    {
       Console.WriteLine("In MyPartialClass::foo() function.");
    }
  }

  class MainEntryPoint
  {
    public static void Main(String[] args)
    {
       MyPartialClass.MethodOne();
       MyPartialClass.MethodTwo();
       MyPartialClass obj = new MyPartialClass();
       obj.foo();
       obj.bar();
 
       return;
    }
  }
}

/*
To compile: do

D:\Study\C#\chap03>csc 11_a.cs 11_b.cs
Microsoft (R) Visual C# 2008 Compiler version 3.5.30729.1
for Microsoft (R) .NET Framework version 3.5
Copyright (C) Microsoft Corporation. All rights reserved.

*/
