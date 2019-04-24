#!/bin/bash

# test_cases.sh
# Casey Hird
# crhird
# ECE 2230 Spring 2019
# MP3

# Script to run test cases


# set these lists with the parameter space's values
shapes='o r p'
levels='5 10 15 20'
policies='bst avl'

valgrind --leak-check=yes --log-file='valgrind_output0.txt' ./lab5 -u 0
valgrind --leak-check=yes --log-file='valgrind_output1.txt' ./lab5 -u 1
valgrind --leak-check=yes --log-file='valgrind_output2.txt' ./lab5 -u 2
valgrind --leak-check=yes --log-file='valgrind_output3.txt' ./lab5 -u 3
valgrind --leak-check=yes --log-file='valgrind_output4.txt' ./lab5 -u 4
valgrind --leak-check=yes --log-file='valgrind_output5.txt' ./lab5 -u 5
valgrind --leak-check=yes --log-file='valgrind_output6.txt' ./lab5 -u 6
valgrind --leak-check=yes --log-file='valgrind_output7.txt' ./lab5 -u 7
valgrind --leak-check=yes --log-file='valgrind_output8.txt' ./lab5 -u 8

# Tests with 0 accesses that print out the resulting tree
./lab5 -o -w 5 -t 0 -v
./lab5 -r -w 5 -t 0 -v -s 1
./lab5 -p -w 5 -t 0 -v -s 2

# Test with 1000000 accesses
for s in $shapes
do
	for l in $levels
	do
		for p in $policies
		do
			./lab5 -$s -w $l -t 1000000 -f $p
		done
	done
done
