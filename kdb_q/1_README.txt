KDB is the database and Q is the interpreter on top of it.
I downloaded the linux zip file for installation from Q website. I set QHOME environment variable. I also installed linux rlwrap command to launch q through it. using rlwrap allows you to use use arrow keys to go to old q commands across q sessions. It also allows you to do linux like histroy search using "Ctrl + r". "Ctrl + l" also clears the q screen (kind of clear for linux).

Basics
======
Launch q as "rlwrap -r q" # assuming q is in your environment.
Exit by typing \\
comments are written using \

System command
==============

q has a system command which allows you to play with q environment. Most of the system command accept optional arguments. When no arguments are provided, the default value for that option is displayed. Some of the example of q commands are. 

\l <script.q> / to load a q script or directory

\a / list tables in the current namespace. See namespaces below
\ ns / list tables in the ns namespace

\cd /some/path / change to directory /some/path. 
\cd / print the current directory

\d .ns.name / change to namespace .ns.name

\d / print the current namespace

\b ns / list views in namespace
\b / list views in the current namespace

\B / list pending views in current namespace

\p  / listening port

You can also use system command like this:

system [cmd]eg:
system "l /path/to/someScript.q"


Namespaces
==========
In q you can define variables. by what happens when you load from so many different sources which all use a common variable. There will be nameclashes. to avoid this you can create namespaces. namespaces are automatically created when you decalare a variable in a namespace. The default namespace is the root namespace identified by a dot ".". In any namespace you can execute the command: key` to view the namespaces there. Under the hood namespaces are implemented as q dictionaries. Infact you can also change your context to any available namespace by using the \d system command. When you change to any context, you can still access global variables in other namespace using relative paths. Example:

q).jab.util.counter:0 / will automatically create namespace .jab.util with variable counter = 0
q)\d .jab
q.jab)show  .util.counter

A problem arises here. 

q)state:`NY / state variable in root context
q).jab.f1:{[] state} / q binds a global variable used inside a function to a global variable in the current context. so state is already bound to state:`NY
q)\d .jab
q.jab)state:0N / a new state variable in .jab namespace
q.jab)f2:{[] state} / state is bound to 0N in this namespace
q.jab)\d .
q).jab.f1[] / prints `NY
`NY
q).jab.f2[] / prints 0N
0N
q).jab.f1
{[] state} / but we see no difference in definition
q).jab.f2
{[] state}

This means a user of the function must know in which namespace did the author of the function define that function?
But there is more to it. q doesn't allow you to change context to more than one level down. So: \d `.level1.level2 will not work.
So how does namespacing work to more than 1 level down? It does. Just remember the following rules of Thumb:
1. Use namespaces at any arbitrary depth.
2. whenever you define any function, any global variables it uses should be from the same context.
3. Best practice is to always use fully qualified name so that there is no ambiguity.
4. Always refer to global entities using fully qualified names.

Views
=====
A view is a calculation that is re-evaluated on demand. A view can be thought of a variable whose value depends on other variables and the value itself is lazily computed on demand.
A view is created using the syntax. The following defines a view called myview which depends on vars a and b.

q)myview::a+b
q)a:1
q)b:2
q)myview
3
q)\b
q)a:5
q)\b
q)\B
