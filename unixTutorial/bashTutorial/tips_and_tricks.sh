#!/bin/bash

# truncating file
cat /dev/null > "someFileName"  # will truncate file to zero length or create an empty file
: > "somefilename" # exactly as above. the ":" is a magical keyword which can be used in many places.

# exit
# using exit without any return code will exit with the return status of the previous command.

# Verify integer argument using case
case "$1" in
    "") lines=50;;  # default value if arg not set
    *[!0-9]*) echo "Usage: $(basename $0) <some integer>"; exit -1;;
    *) lines=$1;
esac
echo $lines

# comma operator - the comma operator links together a series of arithmetic operations but only returns the value of the last node.
let "t2 = (( a = 9, 15/3, 2**3 ))"
echo "t2 is $t2, a is $a"

# Finding files
ls /{,usr}/bin/mk*  # will find in //bin/ and /usr/bin both

# trap
trap "echo Booh!; exit -1;" SIGINT SIGTERM

# : - Colon, the null command. ":" is a null command ie a no-op for bash scripts
:
echo $? # will print 0 ie an exit status of true
# while :  # "while :" means "while true" meaning an endless loop
# do
#     echo 'Endless loop'
#     sleep 1
# done

if :
then
    echo "Will always execute"
else
    :
fi

: ${1?"Usage: $0 ARGUMENT"} # another use, if $1 is not set, print message and abort with exit status 1

not_empty() {
    :  # a no-op which is a placeholder in an otherwise empty function.
}

# Brace expansion
echo x{a,b,c}z  #will print xaz, xbz, xcz
echo \"{These,words,are,quoted}\"
cat {file1,file2,file3} > completed_file
cp foo.{txt,backup}  # will copy foo.txt to foo.backup

# Extended brace expansion
echo {a..z} {A..Z} {0..9}
# creating an array using extended base notation
charset=({a..z} {A..Z} {0..9})
echo ${charset[@]}

# Anonymous functions - Code inside curly braces creates an unnamed function. However, variables used in unnamed functions ARE ALSO VISIBLE OUTSIDE
a=123
{ a=321; }  # also note that {} doesnt start a subshell. However () does
{ local b; b=100; }  # will be an error "local can only be used in a function
echo "a is $a"  # 321
echo "b is $b"
