You already know about the syntax of Extended ASM.
Let us discuss some bit more about it.

Example 1
=========
Lets write a simple asm

void foo(uint32_t dwSomeValue )
{
    int dwres;
  
    //Some asm where output operand is dwres
    asm ("bsfl %1\n\t"
            : "=r" (dwres) : "r" (dwSomeValue) : "cc");

    assert (dwres > 3);
}

cc is a clober here which means that the assembler modifies the "flags" register. So assembler should not assume that it contains a particular value.

//Here clearly, compiler can see that dwres variable is an output operand. So there is no need to say "asm volatile", as volatile disables a chance for the compiler to optimize.
Here we need the compiler to apply any optimization it may deam fit.

Example 2
=========
void foo(uint32_t dwSomeValue )
{
    int dwres;
  
    for(int i = 0; i < 5; ++i)
    {
        //Some asm where output operand is dwres
        asm ("bsfl %1\n\t"
                : "=r" (dwres) : "r" (dwSomeValue) : "cc");
        cout << dwres << << i << dwSomeValue;
    }
}
//Here the compiler can see that dwres is not modified within the loop. So it can easily optimize it outside of the loop. If you had used volatile, this optimization would not have worked.


Example 3
========

    uint64_t msr;
     
     asm volatile ( "rdtsc\n\t"    // Returns the time in EDX:EAX.
             "shl $32, %%rdx\n\t"  // Shift the upper bits left.
             "or %%rdx, %0"        // 'Or' in the lower bits.
             : "=a" (msr)
             :
             : "rdx");
     
     printf("msr: %llx\n", msr);
     
     // Do other work...
     
     // Reprint the timestamp
     asm volatile ( "rdtsc\n\t"    // Returns the time in EDX:EAX.
             "shl $32, %%rdx\n\t"  // Shift the upper bits left.
             "or %%rdx, %0"        // 'Or' in the lower bits.
             : "=a" (msr)
             :
             : "rdx");
     
     printf("msr: %llx\n", msr);

//Here if yo wont have used the volatile qualifier, compiler would have thought that the first asm and second asm are absolutely same. Why not optimize out the second. However, in that case
the same TSC value would have been available.

Example 4
========
Sometimes the compiler can also move your "asm volatile" code before or after the neighbouring code. Eg:

asm volatile("mtfsf 255,%0\n\t" : : "f" (fpenv));  //mtfsf modifies the register which tells how to round floating point numbers. This would effect the next instruction "sum=x+y".
sum = x + y; 

However, compiler can move the "sum=x+y" before asm instruction. In such cases, you can artifically create an output parameter which is used in the subsequent code.
asm volatile("mtfsf 255,%1\n\t" : ="X" (sum): "f" (fpenv));
sum = x + y; 


So remeber to use volatile wisely
