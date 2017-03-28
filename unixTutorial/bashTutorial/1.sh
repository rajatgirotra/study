#!/bin/bash

# [] syntax is preferred over [[ ]] as it provides more features and is a shell
# builtin. [] is an external program called test. However some shells have brought [
# into the shell, but [[ ]] is still preferred.

# Some random examples
filename="foo"
if [[ -f "$filename" ]]
   then
   echo "File exists and is regular file"
fi

[[ -e "$filename" ]] && echo "File $filename exists and is regular file"
[[ -r "$filename" ]] && echo "File $filename exists and is readable"
[[ -w "$filename" ]] && echo "File $filename exists and is writeable"
[[ -x "1.sh" ]] && echo "File 1.sh exists and is executable"
[[ -x "$filename" ]] || echo "File $filename is not executable"
[[ -s "$filename" ]] || echo "File $filename has zero size"
[[ -d "$filename" ]] || echo "$filename is not a directory"
[[ -b "/dev/sdb1" || -c "/dev/sdb1" ]] && echo "/dev/sdb1 is a device file"
# set SUID bit - There are times when unix can allow a user to run a program using the priviledges
# of the user who owns the program. For example, when you run passwd command, the command is run as
# the root user instead of the user invoking it. Look at ls -ltr /usr/bin/passwd. The executable bit
# of the owner is set to "s" instead of "x". You can set the SUID bit only using sudo.
# either do "sudo chmod u+s <program_name> OR
# "sudo chmod 4755 <program_name>
[[ -u "$filename" ]] && echo "$filename has SUID bit set"
# Sticky bit - appears as a "t" in the ls -ltr listing. Sticky bit can be applied to both files and dirs.
# When applied to file. it means that the system should keep the memory image, ie. the text section of the
# executable in memory/swap area, as it will be used again soon. You really dont need to do this anymore.
# as modern systems are really fast.
# When applied to directories it means, the directory is writeable by a user (if he has proper priviledges).
# but he still cant delete files that he does not own. the /tmp and /var/tmp dirs have this bit set.
# can set using "sudo chmod 1775 /var/tmp /tmp"
[[ -k "/tmp" ]] && echo "/tmp has sticky bit set."


[[ -L "soft_foo" ]] && echo "soft_foo is a symbolic link."

# bash resolves symbolic links, so soft_foo and foo will both be foo. So comparison (-nt, -ot) will always be false
[[ "soft_foo" -nt "foo" ]] && echo "soft_foo is newer than foo"
[[ "foo" -ot "soft_foo" ]] && echo "foo is older than soft_foo"

[[ "foo2" -nt "foo" ]] && echo "foo2 is newer than foo"
[[ "soft_foo" -ef "foo" ]] && echo "soft_foo is linked to foo"

var="img.jpg"
#var="image.jpg"
# you can do pattern matching and grouping using [[ ]]
# Also brackets() need not be escaped using \
[[ ($var == img*) && ($var == *.png || $var == *.jpg) ]] && echo "$var is an image file"

# regular expression matching can also be done using =~ operator. The expression on the right of =~
# should be a regualar expression and is matched to the expression on the left
# Note no need to quote the regular expression
dt=`date`
[[ "$dt" =~ ^Thu.*17 ]] && echo "Its Thursday the 17th"

# Another advantage is that you dont need to quote variables even if they contain spaces
file="file name"
[[ -f $file ]] && echo "$file exists and is a regular file"  ## no quotes needed around $file

# As a rule of thumb always use [[ ]] for strings and files.

