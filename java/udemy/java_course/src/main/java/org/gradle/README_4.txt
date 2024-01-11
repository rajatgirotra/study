There are two types of tasks in gradle
1) Simple task
2) Enhanced task

A simple task just encloses an action closure. that action closure defines the behavior of your task.
An enhanced task is where the behavior of a task is built into the task itself (i.e. in the api code). This kind of task provides some properties which can be used to configure the task. Most gradle plugins use enhanced tasks. You dont need to implement the task behavior as you do with simple tasks. You simply use the task and configure the task using its properties.

Some important command line options for gradle are:

-b my_build.gradle (this is now deprecated, we will see the alternate later)
-DjvmParam=jvmArg (to pass to the JVM in which gradle is running)
-Pkey=value (specify a property which will be available in your build script)

-i --> log level is info
--stacktrace --> print stacktrace on error
-q --> quiet
--offline --> only look for dependencies in cache, and do not look into remote repositories.
