#!/bin/bash

# test_cases.sh
# Casey Hird
# crhird
# ECE 2230 Spring 2019
# MP3

# Script to run test cases


# set these lists with the parameter space's values
tests='100 1000 10000 100000 1000000'
# descending,  ascending, random

# sorting algorithm IDs

# sort output orders

# First run each sort function with a memory check and save valgrind output
# Run test for first 4 functions
for t in $tests
do
	./lab5 -o -w 20 -t $t
done
