waf is a python build tool. Normally when you install python packages, you do pip install. However, waf is installed slightly differently. you can just download waf using curl and put it in your $PATH. If you open the waf file im vim, you will see it is self extractable script. It has some python code in the beginning followed by binary data. Whenever you run waf, all this binary data is extracted in the same folder as the one containing the waf executable. So this directory must be writeable. If for some reason you cannot make the waf directory writeable, then create an environment variable WAFDIR pointing to the directory containing the directory named waflib (extracted by waf). This way waf can be used by different python versions, as each python version creates its own waf folder.

If you run waf --help, you will see there are many options like waf configure, waf build, waf clean, waf install, waf distclean etc etc. waf commands are mapped to python functions. Some of these functions are defined implicitly by waf but you can always define your own waf commands like "waf hello" --> which can be mapped to a python function "def hello()".

all the python functions you define take an argument called context or ctx. There are many different types of context objects like ConfigureContext, BuildContext, InstallContext, OptionsContext etc.

Also there are some special variables which can/must be defined so tha waf can function properly. we'll see as start writing some build files. By default, waf files are are wscript.py,, just like cmake files are CMakeLists.txt

More imporantly, you can also create CMakeLists.txt or MS visual studio solution files using waf extension modules. So you can easily work with Windows Visual Studio or CLion (which depends on CMake).

Lets have some fun now.


