Tuning Flags
===========
There are many tuning flags available to tune the JVM performance. tools like jcmd and jinfo let you inspect and modify these flags.
Before we understand the meaning of these flags, lets first see what values these flags can take on.

Default values -> tuning flags have some default values. These defaults can be either same across all platforms or we can have platform specific defaults.
When you run "jcmd <processId> VM.flags -all", it tell you whether a flag has platform specific default or not. "pd product" means platform dependent default.
Just "product" means same default value across all platforms.

Ergonomically set values -> these are values the JVM calculates by itself, depending on resource availability and other factors.
Search for "ergonomic" in the output of "jcmd <processId> VM.flags -all"

Indirect value changes -> This happens when you set some command line tuning flag which indirectly modifies values for other tuning flags.

Command line -> straight forward. You set this explicitly on the command line.

Some examples of using jcmd and jinfo
======================================
jcmd <processID> VM.uptime
jcmd <processID> VM.version
jcmd <processID> VM.command_line --> will display the jvm_args specified on the command line + the java_command + java_class_path
jcmd <processID> VM.flags --> Will also display flags that were set by the JVM ergonomically.
jcmd <processID> VM.flags -all --> Will display all flags.
java <options> -XX:+PrintFlagsFinal <command_line> --> Will display all flags

jcmd <processID> VM.system_properties
jinfo -sysprops <processID>

jinfo <processID> --> Will show JVM args passed to command line and the JVM flags which were set ergonomically separately.
Compare the output of "VM Flags:" and "VM Arguments:"

Manageable flags
================
These are flags which allow values to be dynamically modified at runtime. you can use jinfo to view or modify them. Very trivial. Just run
"jinfo -h"

Thread Information in JVM
=========================
Get stack trace of all the threads in your application using any of the two commands.
jcmd <processID> Thread.print
jstack <processID>

GC Analysis
===========
Many tools give some or the other information on GC activity. Example:
jmap -dump:live,format=b,file=heap.bin <processID>
This heap dump can be visualized using jvisualvm or some third party tools like Eclipse Memory Analyzer tool.
jcmd and jstat also provide useful details. Will come to that later
