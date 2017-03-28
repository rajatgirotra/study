
What is SIMD?
============

SIMD stands for Single Instruction Multiple Data.

A Cpu instruction is said to be SIMD instruction when the same operation is applied on multiple data AT THE SAME TIME.
It describes a computer architecture that deals with multiple data streams simultaneously by a single instruction.

Intel, AMD and other processors provide various extensions to the standard instruction set
that can be used for high performace computing applications such as gaming,
mathematics and physics computations, financial computation, vector operations etc. For example,
SSE (Streaming SIMD Extensions) was introduced in Penitum III CPU in 1999. Ever since the instruction set was improved by adding more and more sophisticated operations and we have SSE2, SSE3 and SSE4 now.

SIMD instruction set is not limited to Intel. AMD also provides its support for SIMD operations.
How is this support provided? Basically, a CPU will need to do two things:

1) Provide an instruction set
   For example, we have SSE, SSE2, SSE3, SSE4, AVX (Advanced Vector Extensions), AVX2 instruction sets.

2) Provide hardware (microarchitecture support) for these instruction sets.
   For example, for SSE, SSE2, SSE3 and SSE4, intel provides CPU registers which are names XMM0 thru XMM7
   for 32 bit processors and xmm0 thru xmm15 for 64 bit processors.
   These are 8 registers of 128 bits each. So you have a total of 8 16 byte registers for 32 bit and
   16 16 byte registers for 64 bit which can be operated on parallely.
   Similary, to support AVX instruction set, intel has increased the registers from 128 bits to 256 bits.
   and names them YMM0 thru YMM7 or YMM15. So you have 8 32 byte registers (or 16 32 byte for 64 bit) that can be operated on parallely.

How to find out which instruction sets are supported by your CPU: do
less /proc/cpuinfo and read the flags

INTRINSICS
==========

What are they?

Intrinsics are nothing but functions which are known to the compiler that directly map to a sequence
of one or more assembly language operations. Basically they give you an interface to use processor-specific
enhancements. So you do not use the SSE, SSE2 etc instruction set directly. You always use intrinsic functions
All major compilers support these functions. Obviously they are standard C++ functions.
Header files to access SSE intrinsics

#include <mmintrin.h> //MMX
#include <xmmintrin.h> //SSE
#include <emmintrin.h> //SSE2
#include <pmmintrin.h> //SSE3
#include <tmmintrin.h> //SSSE3
#include <smmintrin.h> //SSE4
#include <avxintrin.h> //AVX
#include <avx2intrin.h> //AVX2
Also, you will need to use the appropriate compile time option/flag like -msse/-mmmx/-msse2 etc.


Using SIMD
===========

You can use SIMD instructions in three ways:
1) Inline assembly: Directly write asm code which deals with the xmm0-7 registers. This way you can optimize your code
to the highest level, but writing assembly is very combursome and error-prone

2) Intrinsics: Using C/C++ intrinsics functions. Easy to program but you may not get the highest level of optimization

3) Using vector class (not std::vector): Even easier to program than intrinsics but again even lesser optimized output.

So I would say for now study intrinsics and worry about assembly/vector later.


C++ SISD Vs SIMD
================

Generally all C++ code is SISD (Single Instruction Single Data).
However, if you turn on compiler optimization flags when compiling, there are cases
when your compiler may automatically use SIMD instructions to optimize your code. So that C++
code is as fast as SIMD based code. However, such optimizations are not always possible.

ALIGNMENT
==========

Data to be moved in and out of XMM registers must be 16 byte aligned. Otherwise if the data is not aligned, then
more costly unaligned memory movement will be needed.
Intel optimization manual says: "Data must be 16-byte aligned when loading to and storing from the 128-bit XMM registers used by SSE/SSE2/SSE3/SSSE3. This must be done to avoid severe performance penalties."