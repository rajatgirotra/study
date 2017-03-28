gdb provides a rich python API to do a number of tasks.
Lets explore them one by one.

(gdb) help python

(gdb) !which python --> Bu degault gdb uses python which is in $PATH

(gdb) python
>def hello():
>    print("Hello")
>end
(gdb) python hello()
Hello
(gdb)


