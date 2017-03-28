Please read README_2.txt first

The best way to run groovy is through the command line. Groovy command line options:
[rajat@localhost GroovyTutorial]$ groovy --help

usage: groovy [options] [args]
options:
  -a,--autosplit <splitPattern>    split lines using splitPattern (default
'\s')
                                   using implicit 'split' variable
  -c,--encoding <charset>          specify the encoding of the files
  -classpath <path>                Specify where to find the class files -
must
                                   be first argument
  -cp,--classpath <path>           Aliases for '-classpath'
  -D,--define <name=value>         define a system property
  -d,--debug                       debug mode will print out full stack traces
     --disableopt <optlist>        disables one or all optimization elements.
                                   optlist can be a comma separated list with
                                   the elements: all (disables all
                                   optimizations), int (disable any int based
                                   optimizations)
  -e <script>                      specify a command line script
  -h,--help                        usage information
  -i <extension>                   modify files in place; create backup if
                                   extension is given (e.g. '.bak')
     --indy                        enables compilation using invokedynamic
  -l <port>                        listen on a port and process inbound lines
                                   (default: 1960)
  -n                               process files line by line using implicit
                                   'line' variable
  -p                               process files line by line and print result
                                   (see also -n)
  -v,--version                     display the Groovy and JVM versions


Next you'll see the usage of some of these important command line parameters.
Please read 2.groovy next

