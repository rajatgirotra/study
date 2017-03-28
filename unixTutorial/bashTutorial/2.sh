#!/bin/bash
 
# There are many ways in which you can do arithmetic (force arithmetic context) in bash. Lets
# see a few common one
# 1. Let command - It takes multiple arithmetic expressions as arguments.
let a=17+23
echo "a is $a"

let 'a = 17 + 22'
let b='2+3'
echo "a is now $a, and b is $b"

let c=17 d='c+10'
echo "c is $c, and d is $d"

let f=28/6  # fraction is truncated
echo "f is $f"

# 2. The second way is (( ArithmeticExpression )) syntax.
(( x = x + 7 ))  # force x to be used in arithmetic context
(( x += 10 )) 
echo "x is $x"

# You can also do something like:
z="10"
z=$(( z + 10))  # z will be 20, when (( )) is preceeded with a $, a substitution is performed.
echo "z is $z"

let val=10
(( val2 = val < 100 ? 2 : -2 ))
echo "val2 is $val2"

# Can also be used in comparison
z="100"
if ((z >= 100));
then
    echo "Z is greater than equal to 100"
fi

# carefully look at the following two if conditions. The only difference is that of a "$" in if condition
# Without using $, (( z==0 )) is a command, think about this as a command which returns two things. One is the exit status ie $? and one is the value of the expression inside, (( z==0 )) will return the exit status which if can evaluate.
# With $, $((z==0)) returns 0 or 1, based on if expression is true or false. so in this case it returns 1 as z == 0 is true, so the if condition
# becomes if 1; then... This causes bash to fail because "1" is not a command.
z="0"
if ((z == 0))
then
    echo "Z is zero"
fi

z="0"
if $((z == 0))
then
    echo "Z is zero"
fi

echo "0==0 is: $(( 0 == 0 ))"  # 0==0 is: true or false, and prepending $ to it will give 1 or 0 respectively.
echo "but"
(( 10 > 6 )); echo "(( 10 > 6 )) is : $?"  # return code is 0 if command returns true


# Also there are variables in bash which have some default meaning. Eg: RANDOM produces a random number
rand=$(( RANDOM % 10 + 1))  # will return a random number between 1 and 10.
echo "Random number is $rand"


# 3. the third way is to declare it as an integer
unset varInt  # unset any previous definitions of variable varInt
varInt=7+5
echo "varInt is $varInt"
unset varInt
declare -i varInt  # declare varInt as integer. varInt will now work in integer context.
varInt=7+5  # think about this as "let varInt=7+5", it will make it easier to understand
echo "varInt now is $varInt"

# 4. Array indices are by default in integer context
# n=0
# while read line
# do
#     arr[n++]=$line
# done


# 5. There is one common pitfall with arithmetic expressions in Bash: numbers with leading zeroes are treated as octal. For example
month=$(date +%m)
echo "Month is $month"  ## if current was aug/sep/oct/nov/dec, the next would would give an error as 08 is not valid in octal.
next_month=$(( month == 12 ? 1 : month + 1 ))
echo "Next month is $next_month"

# To handle the above case, a workaround is to remove any 0's at the start of the number or let the command
# know that the number is in base 10.
month="08"
[[ $month == 0* ]] && month=${month##0}  # you'll see more of string handling in 3.sh
echo "Month after removing 0's at start is $month"

a=08
let b=a+1  ## will be an error as 009 is not a valid octal
# the way out is to tell "let" that the number is in base 10.
let b=10#$a+1
echo "b is $b"


# Look at the following examples:
echo "100 in base 2 is $(( 2#100 ))"
echo "100 in base 8 is $(( 8#100 ))"
echo "100 in base 10 is $(( 10#100 ))"
echo "100 in base 16 is $(( 16#100 ))"
# basically preceeding "x#" means the number is in base x.

# simple function to convert a number to decimal.
todec() {
    echo "$(( $1#$2 ))"
}

todec 16 ffe
todec 2 1010
x=$(todec 2 1010)
echo "x is $x"
