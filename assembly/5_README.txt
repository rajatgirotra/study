Output Operands Format
=====================

The format of output operand is 

[ [asmSymbolicName] ] constraint (cvariableName)

asmSymbolicName is optional. Can be any variable name. like myVar; then instead of referring them in asm like %0, %1, you can use this name in square brackets. like %[myVar]

contraint is an expression which tells how you want to retrieve the output. Eg:
contraint can start with
"=" simply meaning that the output is to be stored in a variable.
'+' means that the output is to be stored in a variable; but you count this operand twice (once each for input and output). An asm can have max 30 operands.
'&' - I do not understand this but may be later its on the gcc extended asm page.

after a modifier above, you tell where the computed output value should be. ie where should asm store the output value in a processor register "r" or in memory "m".
Then it will copy from register or memory to the specified output variable.
If you specify both, compiler will optimize and choose the best. So i think it makes sense to always include both.

The you follow with the output parameter name.

Eg's

uint32_t Mask = 1234;
uint32_t Index;

asm ("mov %[aMask],%[aIndex]\n\t"
       : [aIndex] "=rm" (Index)"
       : [aMask] "r" (Mask)
       : "cc" );

Some target platforms like x86 also provide a way to fetch specific values from the flags register. I'll ignore how to do that for now.
But just remember that some systems have specical register called flags register to the store the result of an operation or comparison.
Like Zero bit set,
    Value Zero or not
    Carry Bit Set etc etc.


