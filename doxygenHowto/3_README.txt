
How to document

For any C++ entity, file, class, namespace, member, function etc use can specify two types of descriptions
1) brief description (one liner)
2) detailed description (longer, detailed description)

For functions there exist a body description also, which shows all the comments inside the body also in the final
documentation. We'll see that later.

There are many different ways of commenting that doxygen understands that you can easily get consfused, so just remember the below syntax. 

/**
      brief description

      detailed description.
 */

A line break identifies the boundry between brief and detailed description. If your brief description is also multiline
use the \brief command

 For Brief description, remember three ways
 1) Use a brief command, as shown below. which ends at the next paragraph.

 /** 
   \brief Brief description.
           Continued brief description until end of paragraph.
  
   Detailed descrption.
  */

If you want to put documentation after the member declaration, use
int var; /**< Detailed description after the member */
int var; ///< Brief description after the member (ie one liner)

You can also introduce structural commands in the comment block. A structural command begins with \ or @
Eg:

/**
  * \param a an unsigned integer
  * \param s a const character pointer
  * \return a pointer to a function
  * \sa abc(), ~test() 
  */

Infact you can write structral commands to include documentation for a number of entities like #defines, macros,
typedef, file, global variables etc. Also documentation need not be necessarily at the front or after the entity
It can be anywhere if you are using structral commands. I can place the documentation in a completely separate file
like my_code.doc and doxygen will parse it. The drawback is that you will need to repeat the function declarations/prototypes,
repeat the macros, #defines, typedefs in the my_code.doc file also.

Also note that it is mandatory that you put provide a file level documentation before you can provide documentation for global
functions/variables/typedefs/macros etc.


    \struct to document a C-struct.
    \union to document a union.
    \enum to document an enumeration type.
    \fn to document a function.
    \var to document a variable or typedef or enum value.
    \def to document a #define.
    \typedef to document a type definition.
    \file to document a file.
    \namespace to document a namespace.
    \package to document a Java package.
    \interface to document an IDL interface.

see structcmd.h as an example.

