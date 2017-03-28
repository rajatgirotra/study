
How to document

For any C++ entity, file, class, namespace, member, function etc use can specify two types of descriptions
1) brief description (one liner)
2) detailed description (longer, detailed description)

FOr functions there exist a body description also, which shows all the comments inside the body also in the final
documentation. We'll see that later.

There are many different ways of commenting that doxygen understands but we will only concentrate on main ones.

For detailes description. Best is to use the common JavaDoc style comments, ie /** and */

/**
  * ...text...
  */

or 

/*!
 * .... text....
 */

 For Brief description, remember three ways
 1) Use a brief command, as shown below. which ends at the next paragraph.

 /*! \brief Brief description.
  *         Continued brief description until end of paragraph.
  *
  *   Detailes descrption.
  */

  2) set JAVADOC_AUTOBRIEF=YES, and Javadoc will automatically take the first line as a brief description.

  /** Brief description.
   * Detailed description
   */
 
 3) 
 /// Brief description. Only one line.
 /** Detailed description */


If you want to put documentation after the member declaration, use
int var; /**< Detailed description after the member */
int var; ///< Brief description after the member

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
It can be anywhere if you are using structral commands.



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

