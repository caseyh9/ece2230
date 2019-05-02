#!/bin/bash

# test_cases.sh
# Casey Hird
# crhird
# ECE 2230 Spring 2019
# MP4

# Script to run test cases


# Iterate through the following sort orders
sortOrders='best first worst'
# Test these unit test drivers
unitTests='0 1 2 3 4 5 6'
# Use the following random number generator seed
seeds='19283 8234'


# Run each case without coalescing
for u in $unitTests
do
	for s in $sortOrders
	do
		for r in $seeds
		do
			./lab4 -s $r -f $s -u $u
		done
	done
done

# Run each case with coalescing
for u in $unitTests
do
	for s in $sortOrders
	do
		for r in $seeds
		do
			./lab4 -s $r -f $s -c -u $u
		done
	done
done

