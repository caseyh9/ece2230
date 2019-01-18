# The makefile for MP1.
CC     = gcc
CFLAGS = -Wall -g

lab1: task_list.o

lab1.o: task_list.h

task_list.o: task_list.h

.PHONY: test
test: lab1
	./lab1 10 < input1.txt

.PHONY: clean
clean:
	rm -f task_list.o lab1.o lab1
