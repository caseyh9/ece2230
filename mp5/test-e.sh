#!/bin/bash

# testing for -e avl cases

levels="5 10 15 20"
tests="1000 10000 100000 1000000"

for l in $levels
do
	for t in $tests
	do
		echo "test for $l levels and $t trials"
		./lab5 -e -w $l -t $t -f avl
	done
done
