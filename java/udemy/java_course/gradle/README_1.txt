Gradle is also a build tool like maven. Installing is trivial. Just like maven. Its written in Java and needs atleast Java 8. Just download the zip file,
extract it put the bin/ folder in $PATH

gradle -version

Creating a new project with gradle
==================================
create a folder gradle-tutorial
run "gradle init" to create gradle skeleton files.
the main files are:
1) build.gradle --> gradle build script in Groovy language. defines all the plugins/tasks/dependencies etc for our project
2) settings.gradle --> settings file also in Groovy language
3) gradlew and gradlew.bat --> These are unix and windows gradlew wrapper scripts. should always use these wrapper script inside your project.
4) a .gradle folder which is the gradle cache

So every project will have a build.gradle file
in gradle, we defines tasks. Each task is like a goal in maven which can be run independently. Even with an empty build.gradle file, there are some
tasks which you can still run. Inside your project base dir, run "gradlew tasks" to see on a higher level which tasks gradle gives you out of the box.
Run "gradlew tasks --all" to view a full list of tasks.

You can always add plugins (core gradle plugins or 3rd party plugins). these plugins will add more tasks for your project. You can configure these
tasks in the build.gradle file.

Groovy
======
Groovy is dynamically typed, scripting language. Some examples:

def myVar = 'Executing as a script'  # no semi-colon required
println myVar

def multiply(first, second) {
    println first * second
}
multiple 2, 3 # brackets not required when passing arguments to function as long as there is 1 parameter. If no parameter, then we need ().

def myClosure = {
    println 'Executing closure'
}
myClosure() --> Looks identical to function, but these are closures. Closures are just blocks of code that can be passed around and be called later using paranthesis.
Another example of closure is:

def anotherClosure = { a, b -> a + b} // a closure which accepte two arguments a and b & return a + b as result.

dependencies graph
==================
gradle also builds its dependencies graph. i.e. an order in which various tasks need to run.
Also a lot of tasks are just aggregate tasks. i.e. they do not run any logic by themselves. They just aggregate one or more tasks that actually
perform some logic, like compile, invoke test, package jar etc.

Why gradlew
===========
gradlew means gradle wrapper. they are a wrapper script which you can checkin along with source code in github. They should be used all the time,
instead of using gradle. When you checkout some JVM repo from github, which has gradle build system, you can still build the project without a gradle
installation. That's because the gradle wrapper scripts have all the logic built-in to do a successful build.