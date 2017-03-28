In the assembly that you write, certain special expressions can be used. Eg:

%% - means you want to put a literal % in the assembler code. So the first % is used to escape the second one.

%= - I dont know this completely. But it generates a unique number for every asm in your code. I dont know yet how it is used. 
     I'll come back to this later

$10, $20 - means value 10, 20

%{
%|
%}  - These are used to literally add { or | or } in the assembler code.

if you dont escape {,|,} then these can be used to separate instructions for different dialects which the architectur supports.
For example, x86 supports att and intel. So If I write instruction like

asm ( "abcd {%offset,%base | %base,%offset} \n\t" ); //then "abcd %offset,%base means first dialect and "abcd %base,%offset" means second dialect.

x86 supports att (AT&T) and Intel. Default is att. You can use the -masm switch to specify the dialect that the assemble code should be produced in.
See intel.s and att.s, which produced using
g++ -S -masm=intel -o intel.s 1.cpp
g++ -S -masm=att -o att.s 1.cpp

Read more about x86, x86_64, ia32, ia64 to understand more.
