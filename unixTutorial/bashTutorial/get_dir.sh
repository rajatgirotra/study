#!/bin/bash

# Getting the directory where the script is running can be really tricky.
# We'll see incrementally the problems in various approaches and reach a solution.

# 1. Use $0
d="$(cd $(dirname "$0") && pwd)"
echo "script dir using \$0 = $d"
# This fails when you run this script like "source ./utils.sh"
# "dirname source" will return . (ie the current working dir), then "&& pwd" will return the current working dir
# not the script dir.

# 2. Use BASH_SOURCE[0]
d="$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"
echo "script dir using BASH_SOURCE = $d"
# This works consistently everywhere if no symlinks are involved. If your script is a symlink, then it returns the symlink, not the actual script name

# 3. Use BASH_SOURCE[0] with readlink -p
d="$(dirname $(readlink -f ${BASH_SOURCE[0]}))"
echo "script dir using BASH_SOURCE = $d"
