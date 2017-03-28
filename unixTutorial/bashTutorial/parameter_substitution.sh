#!/bin/bash

# there are a number of ways in which parameters can be evaluated. Lets start

# ${parameter-default_value} - Will return default_value if $parameter is not set.
# ${parameter:-default_value} - Will return default_value if $parameter is not set or set to null
# example:
unset username
username=${username-$(whoami)}
echo $username  # will print rajatgirotra as username is not set

username=
username=${username:-$(whoami)}
echo $username  # will print rajatgirotra as username set to null

echo

# ${parameter=default_value} - Will set parameter to default_value and return default_value if $parameter is not set.
# ${parameter:=default_value} - Will set parameter to default_value and return default_value if $parameter is not set or set to null
# example:
unset username
: ${username=$(whoami)}  # without the colon ${username=$(whoami)} will return rajatgirotra which the shell will interpret as a command. So this is one more use of the magical ":" keyword
echo $username  # will print rajatgirotra as username is not set

username=
: ${username:=$(whoami)}
echo $username  # will print rajatgirotra as username set to null

echo

# ${parameter+default_value} - Opp of ${parameter-default_value}, if parameter is set (to some value or null) then use default_value, else use null.
# ${parameter:+default_value} - Opposite of ${parameter-default_value}, if parameter is set or null then use default_value, else use null.
# example:
username=
username=${username+xyz}
echo $username  # will print xyz as username is set

username=
username=${username:+xyz}
echo $username  # will print xyz as username is unset

username=rajatgirotra
username=${username:+xyz}
echo $username  # will print xyz as username is unset

echo

# ${parameter?error_msg} - if parameter is unset, print err_msg and abort
# ${parameter:?error_msg} - if parameter is unset or set to null, print err_msg and abort
# example:
#unset username
username=rajatgirotra
: ${username?}

# username=
username=rajatgirotra
: ${username:?}

: ${HOSTNAME?} ${SHELL?} ${USER?} ${HOME?}
echo "${HOSTNAME} ${SHELL} ${USER} ${HOME}"
