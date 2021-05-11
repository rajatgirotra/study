About linux executable files layout.

linux exeutables, shared libraries have a common format called ELF. ELF files have various sections and objdump is a utility that allows you to see all these various sections and also understand which section has which useful information.

lets begin:

File Headers section 
--------------------
objdump --file-headers ./a.out

architecture: i386:x86-64, flags 0x0000013b:
HAS_RELOC, EXEC_P, HAS_DEBUG, HAS_SYMS, HAS_LOCALS, D_PAGED
start address 0x0000000100401000

gives information on 
1) architecture (32 bit or 64 bit), whether it is an executable or not (EXEC_P)
2) if it is has debug symbols, shown by HAS_DEBUG flag (you can use strip those using strip --strip-debug)
3) if your object file has linking symbols, shown be HAS_SYMS flag (you can strip those using strip --strip-all)

What are linking symbols:
There are a set of symbols which are included by default when you compile. These are the linking symbols and live in the ELF (executable linkable format) symbol table. This contains a lot less info than the debug symbols, but contain the most important stuff, such as the addresses of the things (function, global variables etc) in your executable (or library or object file). Without this information gdb won't even know where main is, so (gdb) break main would fail.

If you don't have the debugging symbols ( -g ) then you will still be able to (gdb) break main but you gdb will not have any concept of the lines of code in your source file. When you try to step through the code you will only advance 1 machine instruction at a time, rather than a line at a time.


Private Headers section
-----------------------
objdump --private-headers ./a.out

this displays program headers and dynamic section. dynamic section is very important as it tells you
1) the shared libraries needed by this object file.
2) any RPATH set in the object file
3) dependency on the GLIBCXX_3.4 etc needed from shared libraries like libstdc++.so.6 etc.


Section headers
---------------

objdump --section-headers ./a.out

this lists all the sections in the object file like
.text
.rodata
.bss
.ctors
.dtors
.debug_* sections

etc.

All headers
-----------

objdump --all-headers ./a.out

will display information on all the headers above plus the symbol table details. (ie. the linking and debugging symbols information)

Symbols
-------

objdump --syms ./a.out

will output only symbols (linking and debugging symbols)

Meaning of symbol table entries:
--------------------------------
symbol entries look like these:

00000000 l    d  .bss   00000000 .bss
00000000 g       .text  00000000 fred

first col:   the symbols value (also called the symbols address)
second col:  flag bits (set of characters and spaces)
third col:   section in which the symbol is defined. *ABS* if the section is absolute (ie not connected with any section), or *UND* if the section is referenced in the file being
             dumped, but not defined there.
fourth col:  symbols size of alignment
fifth col:   symbols name

flag bits (second col) are divided into 7 groups:

1) l, g, u, ! -> l means local symbol, g means global symbol, u means unique symbol, ! means both local not global (cannot be the case, it means there is a bug in your program),
                  (space) means neither local nor global

2) w or space -> w means weak symbol and space means a strong symbol

3) C or space --> symbol is a constructor or normal symbol (C means constructor and space means normal)

4) W or space -> warning symbol or normal symbol (W means warning and space means normal). A warning symbol’s name is a message to be displayed if the symbol following the
                 warning symbol is ever referenced
				 
5) I and i    -> 

6) d or D or space -> d means debugging symbol, D means dynamic symbol and space means normal symbol

7) F f O or space -> F means function, f means file, O means object and space means normal symbol
example of f i.e. file symbol would be /usr/lib/../lib64/crti.o