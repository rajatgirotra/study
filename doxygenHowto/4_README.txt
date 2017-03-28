Doxygen cannot parse some files like *.sh
But there is a way by which you can include them in your documentation.

First Make sure that FILE_PATTERNS config has *.sh

Then in any dummy file (say a.cpp) define the structural \file command and the \verbinclude command

a.cpp

/*! \file myscript.sh
    Description of the script
    \verbinclude myscript.sh
 */
