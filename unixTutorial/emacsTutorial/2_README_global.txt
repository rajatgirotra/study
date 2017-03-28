Global is just like Ctage. It creates an index database which is used to cross reference your source code.
I have installed it in my CentOS 7 using root.

By default, global recognizes *.h files as a C project. To use *.h in  a CPP project
export this environment variable
GTAGSFORCECPP=

At the root directory of your source tree, run the gtags command
This will generate three files:

1) GTAGS : The tags database
2) GRTAGS : The reference 
3) GPATH : path name database

After that you can use the global command from any sub directory in your project.

$ global func1 --> ie find where function func1 is defined
DIR1/fileB.c --> possible output


$ global -r func2 --> -r means lookup where func2 is referenced() ie called.
../DIR1/fileA.c  --> possible output

global func[1..3] --> can use with regular expressions.

global -x func2 --> -x means show details of the function ie function definition, filename and line number etc.

global -a func2 --> -a means give absolute filename where function is defined.

global -xg '#ifdef' --> will locate symbols which have the specified pattern

global -c kmem --> -c means search for all symbols that start with kmem
Lookup global --help for more options

The way people use it is to first put all set of files to be tagged in a file. using the file command
and redirecting output to a file. Then generate tags on those files.

gtags -f /tmp/list

Sometimes the source tree directory is read only. In those cases you cannot create the tags database in that folder. You have two options
1) mkdir /var/dbpath
   cd /cdrom/src
   gtags /var/dbpath  # make tags database in /var/dbpath
   export GTAGSROOT=/cdrom/src
   export GTAGSDBPATH=/var/dbpath

2) By default, the global command looks in the /usr/obj/<current directory> for the tags file, you can also do:
    cd /cdrom/src
    mkdir -p /usr/obj/cdrom/src/
    gtags /usr/obj/cdrom/src

This path "/usr/obj/" can be changed by setting the environment variable MAKEOBJDIREPREFIX

Obviously, your project will depend on system and 3rd party library files. But gtags cannot by default look at symbols in those library files.
Again two ways are possible:

1) run gtags in each of those system/3rd part library and then export this env variable. GTAGSLIBPATH
   cd /usr/src/lib
   gtags
   cd /usr/src/sys
   gtags
   export GTAGSLIBPATH=/usr/src/lib:/usr/src/sys

2) The other better way is to create soft links to those library directories in your home folder. and you are done
    ln -s /usr/src/lib .
    ln -s /usr/src/sys .
    gtags
    
Emacs support:
Step 1): You'll need to use the gtags.el package. Load the gtags.el and execute gtags-mode function in it.
Step 2): add a hook to enable the gtags-mode when in C++ mode.

Next refer: GNU Global emacs editor commands
