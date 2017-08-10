#!/bin/bash


#echo "Rajat different cores"
#taskset -c 0 ./a.out &
#taskset -c 3 ./a.out &

echo "Rajat same cores"
taskset -c 0 ./a.out &
taskset -c 1 ./a.out &


