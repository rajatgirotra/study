Scons stands for Software construct. Its another build system like make and cmake.

1) It looks for MD5 checksums of files to determine which are out of date. Optionally can also use timestamps of files
2) Has inbuilt SCANNERS for figuring out the dependeny tree of C/C++ and a host of other languages. New custom scanners can also be added.
3) The SConstruct or SConscript files are written in python, so it is very powerful.

It starts by looking for a file called "SContruct", "Sconstruct" or "sconstruct" (in that order) in the current directory (use -f for any custom config file). This contains the config file (just like makefile for make).
Nested directories must have files called "SConscript".
scons will read all config files before doing anything.

A Construction Environment is the basic means by which a SConscript communicates build information to scons. You can create a Construction Envioronment by using the
"Environment()" function. This function returns an SConsEnvironment object (for you this should be opaque). By default, this object contains a number of method and variables appropriate for your platform. Also this object holds a python dictionary.
You can pass any keyword argument in the function call, or even add more key-values later. These key value pairs are called Construction Variables.
eg:
import os
env = Enviornment(FOO = 'foo')
env['BAR'] = bar

By default, some keys are already available. Like 'ENV' and others you'll learn soon.
Environment (ENV = {'PATH': os.environ['PATH'],
                    'HOME': os.environ['HOME']})

Some Commands
=============

Basic Usage is:

scons [options] [key=val...] [targets...]

1) scons - Invoking scons without any target will create all targets by default.

2) scons foo bar - Will build to targets - foo and bar

3) You can specify a default target by defining a special function called "Default()". Will see that later. Then invoking it
with no arguments will always build the default target.

4) When Default() is defined, but you still want to build all targets, use
scons . (where dot means everything under this directory).

5) When Scons config files specify any target to be built outside of the top level directory, use
scons /

6) If you are inside a nested directory and want to invoke scons, use
scons -u . -> -u means keep looking one level higher for an SContruct file.

7) to clean up a target, use the -c switch
scons -c . --> will cleanup all target files
scons -c foo bar--> will cleanup foo and bar targets
You can also specify a Clean() function to remove additional files which are not removed by scons
You can also specify a NoClean() function to prevent removal of files.

8) scons -j 4 : To run scons parallely.

9) scons debug=1 : You can pass key value pairs on the command line and read in scons using the ARGUMENTS dictionary
if ARGUMENTS.get('debug', 0):
    env = Environment(CCFLAGS = '-g')
else:
    env = Environment()

10) If you are doing multiple scons builds, which may have some common targets, then you can use the cache feature in scons. scons can write target files into a location called as
cache location. Then when a target to be built is found in cache, it is used from cache instead of building again. There are a number of options controlling the cache feature
a) --cache-disable --> Dont use cache. scons will neither write to or read from cache
b) --cache-force --> Write newly created targets to cache, even when they are up to date.
c) --cache-readonly --> Only read from cache but do not write to it.
d) --cache-debug=<filename or -> --> Print debug information about the cachedir in file "filename" or to standard output ("-")

Site Configuration
=================

Before reading SContruct files, scons will look in special system directories for site_scons folder. If any such folder is found, it will:
1) Add the path to that folder in sys.path
2) Execute site_scons/site_init.py (if it exists)
3) Add site_scons/site_tools.py to default tools path.


Some usefule options to scons
============================

-I directory        : Put -I in python sys.path so that this path can be searched for importing modules.
--help              : Print help
-j                  : For running parallely
-keep-going         : Continue after errors as far as possible.
--dry-run           : Dont execute but just output commands.
--no-site-dir       : Dont go and search for any site_scons folders.
-q, --question      : Do nothing, Just return an exit status of zero if the specified targets are already upto date, non-zero otherwise.
                      Can be used in scripts, using reading $? after invoking scons.
-Q                  : Be quiet, dont tell me that you are reading SConscript files, or building any target or leaving or entering directories.
--silent            : Just dont print anything. Means -Q plus dont print even the commands run for building targets.
--version           : print version
--print-directory   : Print everytime you enter or leave a directory
--no-print-directory: Opposite of above.
--warn=<type>       : There are a bunch of different types of warnings available, which you can enable.. See manual for more details
