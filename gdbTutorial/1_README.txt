Please read gdb_quick_reference first.
After reading that, you should know the following

1) help command
2) complete command
3) apropos command
4) info command
5) breakpoints, watchpoints, catchpoints, break if, ignore N count, delete and clear breakpoints, setting breakpoints using line number, function name, filename:line_number, address
6) print /FMT variable (where FMT is /a for address, /o for octal, /u for unsiged number, /d for signed, /t for binary, /x for hex, /f for float, /c for char)
7) How to print array using "print arrayName[start_index]@element_count" syntax
8) run <args>, set args, command
9) set pretty print - To enable pretty printing of C structures. Actuall we should put this in our user gdbinit file.


Next let's see gdb startup sequence. Before that understand what is an inferior and Auto-Loading and gdb command line arguments -x, -ix, -ex, -iex

Inferior: Modern GDB implementations can debug more than one programs at the same time. You can use gdb to
1) Start a program and debug it
2) Attach to a running process and debug it
3) Investigate a core file. etc
Each of these is referred by GDB as an inferior.

gdb has four options to specify commands to run at startup
    -x <file> : Means run some commands from file at starup
    -ex <cmd> : Means run the command specified on the command line
    -ix <file>: Means run some commands from file but before loading inferior
    -iex <cmd>: Means run command specified on the command line but before loading inferior.

Always make it a habit to start GDB like
bash$> gdb -se program_name -c core_file --> To debug a core file
bash$> gdb -se program_name -p pid_number --> to attach to a process
bash$> gdb --args program_name <program_args> --> To start a process and debug it also.
-se means Symbols and Executable file is 'program_name', -c and -p stand for core_file and pid_number.

-d <directory> : is an option which specifies the directory which should be looked up by GDB for searching source and script files
-cd <directory>: start gdb for the given directory, instead of from the current directory.
-readnow: read the entire symbol table now. startup will be slower.
--readnever: dont read symbol table at all.
--silent: don't print thr front material which shows the non-warranty etc.



Auto-loading
gdb sometimes reads some files and scripts automatically without being told to do so. This is called autoloading. These can sometimes lead to unexpected results, so GDB provides way to disable/handle Auto-loading.


When we start gdb, it 
1) Brings up the interpreter.
2) Loads any system wide gdbinit file (system wide gdbinit can be specified at the time of installing. Run gdb --help and it will display all gdbinit files it will read)
3) Loads any user specified .gdbinit file. ie one in your home directory
4) Run any command specified using the -ix and -eix options. If you want to disable auto-loading
NOTE THAT -ix -iex COMMANDS RUN AFTER LOADING THE GLOBAL INIT AND YOUR HOME GDB INIT FILES BUT BEFORE LOADING THE GDBINIT IN THE CURRENT DIRECTORY.
ALSO NOTE THAT THE SYNTAX OF THE GDBINIT FILES AND THE COMMAND FILES IS SAME.
5) Process command line options
6) Run commands in the .gdbinit file in the current working directory. Only done if "set auto-load local-gdbinit" is set to "on" in the global/user gdbinit file. You can also
   disable using the -iex option.
7) Loads any scripts specified by the program being debugged, or the core file being debugged or by any shared libraries loaded.
   Can be switched off using -iex "set auto-load python-scripts off" for example. This means that the executable and shared libraries can also have associated scripts to be loaded.
8) Execute any -x, -ex command line options
9) Reads the command history from the history file.

Do gdb --help and read about other options like -nh and -nx etc.
