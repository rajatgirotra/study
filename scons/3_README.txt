Node Objects
============

Scons treats every file or directory internally as a Node Object.
For example:

obj_list = Object('hello.c')
lib_list = Library('hello', ['hello.c', common.c'])
exe_list = Program('foo', Split('a.c, b.c, c.c'))

each return a list of target which are Node objects.

Infact, these functions also take Node objects as parameters. You can create node objects that represent File or Directory of Both.
file = File('hello.cpp) returns  Node object that represents a file on the filsystem
dir = Dir('output') represents a Node object that represents a directory "output" on the filesystem
entry = Entry('xyxy') represents a Node object that can represent a File or Dir. 

The str() method on the Node object returns the string representation of the file or directory.

GetBuildEnv() function - The env object has a method GetBuildEnv which can take a single or a list of Node objects or strings,
and return the string paths that reprsents them. Basically, it calls str() on the Node objects, and performs Construction Variable substitutions
for the string arguments. Example:

env = Environment(VAR='foo')
n = File('foo.c']
x = env.GetBuildEnv([n, '/x/y/z/$VAR'])
gives x = ['foo.c', 'x/y/x/foo']
