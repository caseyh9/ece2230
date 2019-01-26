/*	task_list.c
	Casey Hird
	ECE 2230
	Spring 2019
	MP1

	Purpose: Provides functions for the lab1 program. These include functions
	for adding to a task list, removing from a list, searching through a
	list, etc.

	Assumptions: We assume that the writer of lab1.c knows how to use the
	functions here correctly. We also assume that the header file task_list.h
	provides all necessary information for these functions.

	Bugs: No known bugs.
*/


#include <stdlib.h>
#include <assert.h>

#include "task_list.h"
#define TRUE 1
#define FALSE 0

/*
	Constructs a task_list_t struct.
	
	Input: size indicates the size of the new task_list_t

	Output: returns a pointer to the newly created task_list_t struct
*/
struct task_list_t *task_list_construct(int size)
{
	// Allocate memory for task_list_t structure
    struct task_list_t* list = (struct task_list_t*) malloc(sizeof(struct task_list_t));
	// Initialize task list values
    list->task_count = 0;
	list->list_size = size;
	list->task_ptr = (struct task_t**) malloc(size * sizeof(struct task_t*));

    return list;
}

/*
	Frees the memory for a task_list_t struct

	Input: list_ptr is a pointer to the task_list_t to be destroyed

	Output: the memory has been freed
*/
void task_list_destruct(struct task_list_t *list_ptr)
{
    assert(list_ptr != NULL && "TASK LIST NULL IN DESTRUCT");
	// Free the pointer to the array of task pointer in the task list
	free(list_ptr->task_ptr);
	// Free the pointer to the task list
	free(list_ptr);
    // free memory
}

/*
	Counts the entries in the task list.

	Input: list_ptr is a pointer to the task list.

	Output: returns the number of tasks currently in the task list.
*/
int task_list_number_entries(struct task_list_t *list_ptr)
{
    assert(list_ptr != NULL);
	// Returns the current number of entries in the list
    return list_ptr->task_count;
}

/*
	Adds a tasks to the end of the task list.

	Input: list_ptr is a pointer to the task list.
	rec_ptr is a pointer to the task to be added.

	Output: returns and integer, 1 if the task is added successfully and
	-1 if the task could not be added because the list is full.
*/
int task_list_add(struct task_list_t *list_ptr, struct task_t *rec_ptr)
{
    assert(list_ptr != NULL);
	int lastIdx = list_ptr->task_count;
	// Check that the list is not full
	if (lastIdx == list_ptr->list_size)
		return -1;
	// Add the task to the end of the list
	else
	{
		list_ptr->task_ptr[lastIdx] = rec_ptr;
		(list_ptr->task_count)++;
		return 1;
	}
}

/*
	Finds the task at a certain index.

	Input: list_ptr is a pointer to the task list.
	index is the index of the task to be found.

	Output: returns a pointer to the task if it is found, and 
	returns NULL is the index is beyond the size of the task list.
*/
struct task_t *task_list_access(struct task_list_t *list_ptr, int index)
{
    assert(list_ptr != NULL && "TASK LIST NULL IN ACCESS\n");
    struct task_t* a_task;
	// Check that the index given does not go beyond the tasks in the list
	if (index >= list_ptr->task_count)
		a_task = NULL;
	// Return a pointer to the task at the given index
	else
		a_task = list_ptr->task_ptr[index];
	return a_task;
}

/*
	Removes a task from the list.

	Input: list_ptr is a pointer to the task list.
	index is the index of the task to be removed.

	Output: returns a pointer to the removed task, or returns NULL if
	the index is past the size of the list.
*/
struct task_t *task_list_remove(struct task_list_t *list_ptr, int index)
{
    assert(list_ptr != NULL && "LIST NULL IN REMOVE\n");
    struct task_t* task = NULL;
	// Check taht the index given does not go beyond the tasks in the list
	if (index >= list_ptr->task_count)
		task = NULL;
	// Remove the task at the given index
	else
	{
		task = list_ptr->task_ptr[index];
		// Shift the remaining tasks to get rid of the gap
		while (index < list_ptr->task_count)
		{
			list_ptr->task_ptr[index] = list_ptr->task_ptr[index+1];
			index++;
		}
		(list_ptr->task_count)--;
	}
    return task;
}

/*
	Finds the first task with a certain priority.

	Input: list_ptr is a pointer to the task list.
	priority is the priority that you are searching for.

	Output: returns the index of the task if found, otherwise
	returns -1.
*/
int task_list_lookup_first_priority(struct task_list_t *list_ptr, int priority)
{
    assert(list_ptr != NULL);
	int found = -1;
	int i = 0;
	// Search for the first task with matching priority
	while (i < list_ptr->task_count)
	{
		// Return the index of the task
		if (list_ptr->task_ptr[i]->priority == priority)
			return i;
		else
			i++;
	}
    return found;
}

/*
	Finds the first task with a certain id.

	Input: list_ptr is a pointer to the task list.
	task_id is the id we are searching for.

	Output: returns the id of the task if found, otherwise
	returns -1.
*/
int task_list_lookup_id(struct task_list_t *list_ptr, int task_id)
{
    assert(list_ptr != NULL);
	int found = -1;
	int i = 0;
	// Search for the first task with matching id
	while (i < list_ptr->task_count)
	{
		// Return the index of the task
		if (list_ptr->task_ptr[i]->task_id == task_id)
			return i;
		else
			i++;
	}

    return found;
}

/*
	Returns the first task with a certain priority.

	Input: list_ptr is a pointer to the task list.
	priority is the priority we are searching for.

	Output: returns a pointer to the task if found,
	otherwise returns NULL.
*/
struct task_t *task_list_access_priority(struct task_list_t *list_ptr, int priority)
{
    assert(list_ptr != NULL && "TASK LIST NULL IN ACCESS\n");
	int i = 0;
	// Find the first task that matches the priority
	while (i < list_ptr->task_count)
	{
		// Return a pointer to the task
		if (list_ptr->task_ptr[i]->priority == priority)
			return list_ptr->task_ptr[i];
		else
			i++;
	}
    return NULL;
}

/*
	Removes the first task with a given priority.

	Input: list_ptr is a pointer to the task list.
	priority is the priority we are searching for.

	Ouptut: returns a pointer to the removed task.
*/
struct task_t *task_list_remove_priority(struct task_list_t *list_ptr, int priority)
{
    assert(list_ptr != NULL && "LIST NULL IN REMOVE\n");
    struct task_t* task = NULL;
	int i = 0;
	// Find the first task that matches the priority
	while (i < list_ptr->task_count)
	{
		// Remove the task
		if (list_ptr->task_ptr[i]->priority == priority)
		{
			task = list_ptr->task_ptr[i];
			(list_ptr->task_count)--;

			while (i < list_ptr->task_count)
			{
				list_ptr->task_ptr[i] = list_ptr->task_ptr[i+1];
				i++;
			}
		}
		else
			i++;
	}
    return task;
}

/*
	Finds the first task with a certain id.

	Input: list_ptr is a pointer to the task list.
	id is the id we are searching for.

	Output: returns a pointer to the task if found,
	otherwise returns NULL.
*/
struct task_t *task_list_access_id(struct task_list_t *list_ptr, int id)
{
    assert(list_ptr != NULL && "TASK LIST NULL IN ACCESS\n");
	int i = 0;
	// Find the first task with the matching id
	while (i < list_ptr->task_count)
	{
		// Return a pointer to the task
		if (list_ptr->task_ptr[i]->task_id == id)
			return list_ptr->task_ptr[i];
		else
			i++;
	}
    return NULL;
}

/*
	Removes the first task with a given id.

	Input: list_ptr is a pointer to the task list.
	id is the id we are searching for.

	Ouptut: returns a pointer to the removed task.
*/
struct task_t *task_list_remove_id(struct task_list_t *list_ptr, int id)
{
    assert(list_ptr != NULL && "LIST NULL IN REMOVE\n");
    struct task_t* task = NULL;
	int i = 0;
	// Find the fist task with the matching id
	while (i < list_ptr->task_count)
	{
		// Remove the task
		if (list_ptr->task_ptr[i]->task_id == id)
		{
			task = list_ptr->task_ptr[i];
			(list_ptr->task_count)--;

			while (i < list_ptr->task_count)
			{
				list_ptr->task_ptr[i] = list_ptr->task_ptr[i+1];
				i++;
			}
		}
		else
			i++;
	}
    return task;
}

/*
	Determine whether a certain task is runnable.

	Input: list_ptr is a pointer to the task list.
	nargs is the number of arguments in the task we are searching for.
	args is a pointer to the array of arguments we are searching for.

	Output: returns the index of the task if it is found,
	otherwise returns -1.
*/
int task_list_determine_runable(struct task_list_t *list_ptr, int nargs, int*args)
{
	int i, j;
	for (i = 0; i < list_ptr->task_count; i++)
	{
		// Check that task is either queued or blocked
		if (list_ptr->task_ptr[i]->state == QUEUED || 
			list_ptr->task_ptr[i]->state == BLOCKED)
			// Check that arguments agree
			if (list_ptr->task_ptr[i]->nargs == nargs)
			{
				j = 0;
				while (j < nargs && list_ptr->task_ptr[i]->args[j] == args[j])
					j++;
				if (j == nargs)
					return i;
			}
	}
    return -1;
}

/*
	Changes the state of a given task.

	Input: list_ptr is a pointer to the task list.
	id is the id of the task we are searching for.
	state is the state to which we are changing the task.

	Output: no value is returned, the state of the given task is changed.
*/
void task_list_set_state(struct task_list_t *list_ptr, int id, enum state state)
{
	enum state current_state = -1;
	int i = 0;
	// Determine the current state of the given task
	while (current_state == -1)
	{
		if (list_ptr->task_ptr[i]->task_id == id)
			current_state = list_ptr->task_ptr[i]->state;
	}
	// Change the state to the given state if valid
	switch (current_state)
	{
		case QUEUED:
			if (state == RUNNING)
				list_ptr->task_ptr[i]->state = state;
			break;
		case RUNNING:
			if (state == RUNNING || state == FINISHED)
				list_ptr->task_ptr[i]->state = state;
			break;
		case BLOCKED:
			if (state == RUNNING)
				list_ptr->task_ptr[i]->state = state;
			break;
		case FINISHED:
			break;
	}
}

/*
	Removes finished tasks from a list.

	Input: list_ptr is a pointer to a task list

	Output: returns a pointer to a new task list that holds all of the 
	finished tasks that have been removed.
*/
struct task_list_t* task_list_remove_finished(struct task_list_t *list_ptr)
{
    struct task_list_t* rm = (struct task_list_t*) malloc(sizeof(struct task_list_t));
	rm->list_size = 0;
	int i;
    // Count the number of finished tasks
	for (i = 0; i < list_ptr->task_count; i++)
		if (list_ptr->task_ptr[i]->state == FINISHED)
			(rm->list_size)++;
	// Initialize new task list
	rm->task_count = 0;
	rm->task_ptr = (struct task_t**) malloc((rm->list_size)*sizeof(struct task_t*));
	
	// Remove finished tasks from old list and add them to new list
	for (i = 0; i < list_ptr->task_count; i++)
	{
		if (list_ptr->task_ptr[i]->state == FINISHED)
		{
			rm->task_ptr[rm->task_count] = task_list_remove(list_ptr, i);
			(rm->task_count)++;
			i--;
		}
	}
	(list_ptr->task_count) -= (rm->list_size);

   return rm; 
}

/*
	Finds the next task to run, first by id, then by priority is none is found.

	Input: list_ptr is a pointer to the list of tasks
	priority is the priority we will search for if no task is found
	with the given id.
	id is the id of the task to be changed.

	Output: returns a pointer to the task if found,
	otherwise returns NULL.
*/
struct task_t* task_list_schedule(struct task_list_t *list_ptr, int priority, int id)
{
    struct task_t* task = NULL;
	int i;
	// Check for task with the given id
	for (i = 0; i < list_ptr->task_count; i++)
	{
		if (list_ptr->task_ptr[i]->task_id == id)
		{
			// If the id is found and not running or finished,
			// change its state to running and return a pointer to the task
			if (list_ptr->task_ptr[i]->state != FINISHED && 
			list_ptr->task_ptr[i]->state != RUNNING)
			{
				list_ptr->task_ptr[i]->state = RUNNING;
				return list_ptr->task_ptr[i];
			}
		}
	}
	// If this id is not found, search for the given priority
	for (i = 0; i < list_ptr->task_count; i++)
	{
		if (list_ptr->task_ptr[i]->priority == priority)
		{		
			// Change the state to running and return a pointer to the task
			if (list_ptr->task_ptr[i]->state != FINISHED && 
			list_ptr->task_ptr[i]->state != RUNNING)
			{
				list_ptr->task_ptr[i]->state = RUNNING;
				return list_ptr->task_ptr[i];
			}
		}
	}

    return task;
}
