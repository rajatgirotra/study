Let's discuss about some concepts in GDB

auto-loading
-----------
When gdb starts, it can auto-load (ie automatically read) command files from various locations automatically. auto-loading feature is used to control loading of these files. Example:

set auto-load local-gdbinit on
set auto-load local-gdbinit off

is used to turn on/off the auto-loading of local-gdbinit

show auto-load local-gdbinit --> will show whether the setting is off or on
info auto-load local-gdbinit --> will show whether the local-gdbinit file is loaded or not.

Similarly we can set auto-load for various files. Example:
set auto-load libthread-db --> for automatically loading thread debugging library.

show auto-load --> will show all auto-load on/off settings

show auto-load gdb-scripts --> if set to on, gdb will look for a file: objfile-gdb.gdb and load commands in it.
info auto-load gdb-scripts --> will show all scripts which gdb auto-loaded.

show auto-load python-scripts --> same as above but will load objfile-gdb.py

show auto-load guile-scripts --> guile is some other format alternate to python.

Actually you can also specify the python scripts and guile script names inside the .debug_gdb_scripts section in the binary of shared library. and they will be loaded by gdb by itself. We wont be using it for now. Or check if gcc provides some straight forward compile option to put this section in.

show auto-load safe-path
set auto-load safe-path
info auto-load safe-path
add-auto-load-safe-path
These are used to manipulate the list of directories which are safe for auto-loading. If a directory is not marked as safe for auto-loading, gdb will ignore and give a warning. So even if "show auto-load local-gdbinit" is on, if the directory is not on the safe-path, the command file is not read. Entries in this settings are separated by colon(:) The entry can also be a specific file you trust or a shell wildcard pattern

if you start gdb with
--without-auto-load-safe-path --> this security protection is completely disabled.
set auto-load safe-path / --> also has similar effect

the default for auto-load safe-path is $debugdir:$datadir/auto-load, which can be overriden using the 
--with-auto-load-safe-path command line option

show/set/info aut0-load scripts-directory  --> directories where gdb will search for command files at startup. Note that these directories should also be in the auto-load safe-path. Default value is: '$debugdir:$datadir/auto-load'

$datadir is 'show data-directory' --> the location where gdb reads auxiliary data files
$debugdir --> 'show debug-file-directory' --> location where gdb searches for files with debug information


Directories
-----------
script or source directories ---> specified using -d option to gdb or later using "set dir" command.
data directory --> gdb sometimes read an auxiliary data file at startup. I'll check later what these auxiliary data files contain. But you can set the location of the auxiliary data directory using the "-D" option to gdb or later using
"set data-directory <directory>"
"show data-directory" will show the data directory.
