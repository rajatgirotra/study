#!/usr/bin/env bash

# string handling

# 1. string length
str=ABCDEFGHIJ
echo "String length is ${#str}"

# 2. Extract a substring out, from C to G
str=ABCDEFGHIJ
x=`expr $str : '..\(.....\)'`
echo "substring is $x"

# 2. Extract string from beginning or end based on pattern.
# format is ${variable%pattern}
filename="some_file_name.txt"
namespace="java.sun.com"
echo "filename without extension is ${filename%txt}"
echo "filename with all dots removed from end is ${namespace%%.*}"  # pattern is .*

location="/etc/http/conf/httpd.conf"
echo "basename is ${location##*/}"
echo "relative filepath is ${location#/etc/}"
