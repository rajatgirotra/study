#!/bin/bash

# RANDOM - gives a random integer number.
echo "Some random number = $((RANDOM))"

# BASH_SOURCE
# This is a LIFO stack of script files which are called from other script files.
# index 0 will be the current file, index 1 will the file from which this current script is called and so on.
# so basically, BASH_SOURCE[i] is called from BASH_SOURCE[i+1]
echo "from ${BASH_SOURCE[0]} : BASH_SOURCE = ${BASH_SOURCE[*]}"
# calling aaa.sh (need to use source or .)
. ./aaa.sh
echo "back in ${BASH_SOURCE[0]} : BASH_SOURCE = ${BASH_SOURCE[*]}"



# UID
# will contain the real user id of the current user. (ie the user id which owns the running program)
# You can create a simple script like this
# ROOT_UID=0
# E_NOTROOT=87
# [[ $UID -ne $ROOT_UID ]] && {echo "Can only run as root"; exit $E_NOTROOT; }
# echo "Hello World"
# Then set SUID bit using chmod u+s <scriptName.sh>
# then run as normal user and as root user and see the difference.


# PWD and OLDPWD - Self explanatory

