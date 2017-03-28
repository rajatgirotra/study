/*
First file 
*/

Groovy is a dynamic programming language which is targeted for the Java Virtual Machine. It builds upon the strengths
of Java but adds powerful features of its own. 

Installing Grrovy is straight forward. Just download the binary distribution
and set GROOVY_HOME and set PATH=$GROOVY_HOME/bin:$PATH in linux. and simiar settings on Windows (environment variables).

Running Groovy
1] run groovyConsole command. this basically starts an interactive groovy console, where you can type groovy commands
and press Ctrl+R to execute those commands.

2] run groovysh command. This basically sets up the environment for Groovy. I havent used it much.

3] There is a helper class called GroovyShell which has a main(String[]) method for running any Groovy script. You can run 
any groovy script as follows java groovy.lang.GroovyShell foo/MyScript.groovy [arguments]
You can then run the above Groovy main() in your IDE to run or debug any Groovy script.  
4] Running Groovy scripts from the command line There are shell scripts called 'groovy' or 'groovy.bat' depending on your
platform which is part of the Groovy runtime. Once the runtime is installed you can just run groovy like any other script...
	groovy foo/MyScript.groovy [arguments]
	
5] You can also write unix scripts in Groovy and run them just like you run shell scripts in unix. Eg:
	#!/usr/bin/env groovy
	println("Hello world")
	for (a in this.args) {
	println("Argument: " + a)
	}
	
	chmod +x helloWorld
	./helloWorld
Make sure groovy is in $PATH.

/*
Please read helloWorld next
*/
