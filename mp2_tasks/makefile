
# The makefile for MP2.
# Type:
#   make         -- to build program lab2
#   make testlist -- to compile testing program
#   make clean   -- to delete object files, executable, and core
#   make design  -- check for simple design errors (incomplete)
#   make list.o  -- to compile only list.o (or: use lab2.o, task_support.o)
#
# You should not need to change this file.  
#
# Format for each entry
#    target : dependency list of targets or files
#    <tab> command 1
#    <tab> command 2
#    ...
#    <tab> last command
#    <blank line>   -- the list of commands must end with a blank line


CC     = gcc
CFLAGS = -Wall -g

lab2 : list.o task_support.o lab2.o
	$(CC) $(CFLAGS) list.o task_support.o lab2.o -o lab2

list.o : datatypes.h list.h
	$(CC) $(CFLAGS) -c list.c

task_support.o : task_support.h datatypes.h list.h
	$(CC) $(CFLAGS) -c task_support.c

lab2.o : datatypes.h list.h task_support.h
	$(CC) $(CFLAGS) -c lab2.c

testlist : list.o task_support.o testlist.o
	$(CC) $(CFLAGS) list.o task_support.o testlist.o -o testlist

testlist.o : datatypes.h list.h task_support.h
	$(CC) $(CFLAGS) -c testlist.c

.PHONY : design
design :
	@grep -e "-> *head" lab2.c task_support.c ||:
	@grep -e "-> *tail" lab2.c task_support.c ||:
	@grep -e "-> *current_list_size" lab2.c task_support.c ||:
	@grep -e "-> *list_sorted_state" lab2.c task_support.c ||:
	@grep -e "-> *next" lab2.c task_support.c ||:
	@grep -e "-> *prev" lab2.c task_support.c ||:
	@grep -e "-> *data_ptr" lab2.c task_support.c ||:
	@grep "comp_proc" lab2.c task_support.c ||:
	@grep "data_clean" lab2.c task_support.c ||:
	@grep "list_node_t" lab2.c task_support.c ||:
	@grep "task_id" list.c ||:
	@grep "priority" list.c ||:
	@grep -e "-> *state" list.c ||:
	@grep "wallclocktime" list.c ||:
	@grep "nargs" list.c ||:
	@grep "args" list.c ||:
	@grep -e "-> *output" list.c ||:
	@grep "task_" list.c ||:

.PHONY : clean
clean :
	rm -f list.o task_support.o lab2.o lab2 testlist.o testlist
