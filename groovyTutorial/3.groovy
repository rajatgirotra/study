Read 2.groovy first

You can run such a simple groovy script as 2.groovy directly on the command line using the groovy -e switch.

Run on the command line:

groovy -e "println 'Hello World'"; //Note: start with double quotes if you also have single quotes. Also run

groovy -e "println 'Hello ' + args[0]" Rajat   //to see how to pass command line arguments.

One advantage of using groovy -e switch is that you can use groovy easily while chaining commands in linux using the pipe symbol
Eg:

	grep -i gro groovyWords.txt | groovy -e "print System.in.text.toUpperCase()"
	grep -i gro groovyWords.txt | groovy -e 'print System.in.text.toUpperCase()'
	grep -i gro groovyWords.txt | groovy -e 'println System.in.text.toUpperCase()'

See how easily you are mixing single and double quites.

To shorten the above you can also use.
	grep -i gro groovyWords.txt | groovy -n -e "println line.toUpperCase()"

-n means for each line of input: do the following: "println line.toUpperCase()" Here line is a special variable available when using the -n option or the -p option (explained next).

To shorten it even further, use the -p switch :  ie. print the following for each line of input
	grep -i gro groovyWords.txt | groovy -p -e "line.toUpperCase()"

To modify files in place, use the -i option.
Rule of thumb, never use the -i option without and extension. the original file will be stored with the -i extension.
eg:
	find . -name \*.java | xargs groovy -p -i .bak -e '(line =~ "@author  patrick.liardet").replaceAll("@author rajat.girotra")'	

The importance of -p is that it makes available the special line variable available for use.


Along with the line variable a count variable is also available. Both these variables can be used together for various groovy one-liners:

Do the following yourself before looking for answers:
1) Modify a file to print the line number for every line before the line.
2) Print the first fifty lines in a file.




1) groovy -pi .bak -e "count + ': ' + line" FileNamingStyle.java
2) groovy -p -e "if(count < 50) line" FileNamingStyle.java OR
   groovy -p -e "if(count >= 50) System.exit(0); line" FileNamingStyle.java; //This is not working. I dont know why.


Another option is -a which splits the input line into an array called "split"; based on spaces. You can optionally specify your own split pattern like ":" or "|" or anything else.Eg: To view the processes owned by root.

	ps aux | groovy -a -ne "if(split[0] =~ 'root') println split[10..-1]"

Another good command line option is -l <port>. This allows groovy to listen to a port and execute a groovy script for whatever inputs you give it.
Eg:
	groovy -l -p -e "line.reverse()"  //By default, port is 1960. Now after executing this telnet to this port from another shell. and provide any input to see the results.

	telnet 192.168.248.128 1960


