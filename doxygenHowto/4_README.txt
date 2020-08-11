Doxygen cannot parse some files like *.sh
But there is a way by which you can include them in your documentation.

First Make sure that FILE_PATTERNS config has *.sh

Then in that file, add a \verbinclude structural command like example below.

/*! \file myscript.sh
    Description of the script
    \verbinclude myscript.sh
 */
