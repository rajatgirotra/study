With gcc there are two ways of writing assembly.

1) basic asm
2) extended asm

Basic Asm is used when you want to write assembly at the top-level (file-level) scope. Let say you want to define the complete function including its signature and body 
in assembly or you want to put some assembly level directives in your code. Then you can use basic asm.
    Syntax is pretty simple
asm [volatile] (assembly instructions)  
asm is actually a gcc extension, if you use any --ansi or --std=c++11 etc flags, then you must use __asm__ volatile
The "volatile" qualifier is also redundant as everything in basic asm is automatically volatile.
The assembly instructions are nothing but a quoted string literal. You can place multiple assembly instructoins in one string;
but separated by the characters which are most commonly used is assebly code ("\n\t").
However, basic asm is not preferred at all. Reasons

1) Extended asm is said to produce more smaller, safer and performant code.
2) Accessing C data (like variables etc) in basic asm is very difficult.
3] System such as x86 support multiple assembly dialects, all basic asm will use the dialect specified by the -masm command line option.
   Basic asm provides no mechanism to provide different assmembler strings for different dialects.

   SO JUST DONT WRITE BASIC ASM FOR NOW.


2) Extended asm is used when you want to write assembly inside a function. Extended ASM provides a convenient way to read and write C/C++ variables
and also jump from assembly to C labels. Syntax

__asm__ volatile (AssemblyTemplate : OutputOperands : InputOperand : Clobbers)

__asm__ volatile goto (AssemblyTemplate : OutputOperands : InputOperand : Clobbers : GoToLabels)

volatile here means that the entity that is volatile (assembly code) here might have side-effects that the compiler is not aware off. So it tells the compiler to disable certain optimizations.
goto tells the compiler that the asm statement may perform a jump to one of the labels listed in the GotoLabels.

AssemblyTemplate is a string containing text or expressions that refer to input/output operands and goto labels.
OutputOperands is csv list of variables that are modified by the assembly instruction
InputOperands is csv list of expressions read by the instructions
GoToLabels is a list of C labels where the assembly might jump to.

Lets start with some examples, We'll only discuss Extended Asm

Things to Remember for Both Basic and Extended Asm

1] A sequence of consecutive assembly instructions might not remain consecutive after compilation. Because the optimizer can move asm statements relative to other code.
If you want some statements to remain consecutive, then put them in a single multi-instruction asm statement.
2] GCC wont know anything about  asm, so it will just copy it as is in the assembly output file. whether it is valid or invalid.

