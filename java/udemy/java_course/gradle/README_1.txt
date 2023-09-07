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
tasks which you can still run. Inside your project base dir, run "gradlew tasks" to see which tasks gradle gives you out of the box.

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