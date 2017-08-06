Logical Expressions - Which evaluate to either TRUE or FALSE ie (1 or 0)

$<BOOL:? - will evaluate to 1 if ? is TRUE
$<AND:?[,?][,?]> - if all ? is TRUE then True otherwise FALSE
$<OR:?[,?][,?]> - if any ? is TRUE then True otherwise FALSE
$<NOT:?> - Trivial
$<STREQUAL:a,b>
$<EQUAL:a,b> - Numeric comparison
$<CONFIG:cfg> - 1 if CONFIG is cfg
$<PLATFORM_ID:...> 
and many others like COMPILE_LANGUAGE, VERSION, VERSION_GREATER, CXX_COMPILER_ID.
---------------------------------------------------------------------------------------

Informational Expressions
$<TARGET_FILE:tgt> Full path to main file (.exe, .so.1.2, .a) where tgt is the name of a target.
$<TARGET_FILE_NAME:tgt> Name of main file (.exe, .so.1.2, .a).
$<TARGET_FILE_DIR:tgt> Directory of main file (.exe, .so.1.2, .a).
$<TARGET_SONAME_FILE:tgt> File with soname (.so.3) where tgt is the name of a target.
$<TARGET_SONAME_FILE_NAME:tgt> Name of file with soname (.so.3).
$<TARGET_PROPERTY:tgt,prop> Value of the property prop on the target tgt.
$<TARGET_PROPERTY:prop> Value of the property prop on the target on which the generator expression is evaluated.
$<INSTALL_PREFIX> Content of the install prefix when the target is exported via install(EXPORT) and empty otherwise.

And many others.
-------------------------------------------------------------------------------------------
Output expressions

Eg: JOIN

-I$<JOIN:$<TARGET_PROPERTY:INCLUDE_DIRECTORIES>, -I>
generates a string of the entries in the INCLUDE_DIRECTORIES target property with each entry preceeded by -I.

$<ANGLE-R>
A literal >. Used to compare strings which contain a > for example.
$<COMMA>
A literal ,. Used to compare strings which contain a , for example.
$<SEMICOLON>
A literal ;. Used to prevent list expansion on an argument with ;.
$<TARGET_NAME:...>
etc.




