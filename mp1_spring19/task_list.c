// See ECE 223 programming guide for required comments!
//
// You must have comments at the top of the file.
//
// EVERY function must have comments


#include <stdlib.h>
#include <assert.h>

#include "task_list.h"
#define TRUE 1
#define FALSE 0

struct task_list_t *task_list_construct(int size)
{
    struct task_list_t* list = (struct task_list_t*) malloc(sizeof(struct task_list_t));
    list->task_count = 0;
	list->list_size = size;
	list->task_ptr = (struct task_t**) malloc(size * sizeof(struct task_t*));

    return list;
}

void task_list_destruct(struct task_list_t *list_ptr)
{
    assert(list_ptr != NULL && "TASK LIST NULL IN DESTRUCT");
	// Free the pointer to the array of task pointer in the task list
	free(list_ptr->task_ptr);
	// Free the pointer to the task list
	free(list_ptr);
    // free memory
}

int task_list_number_entries(struct task_list_t *list_ptr)
{
    assert(list_ptr != NULL);
	// Returns the current number of entries in the list
    return list_ptr->task_count;
}

int task_list_add(struct task_list_t *list_ptr, struct task_t *rec_ptr)
{
    assert(list_ptr != NULL);
	int lastIdx = list_ptr->task_count;
	// Check that the list is not full
	if (lastIdx == list_ptr->list_size)
		return -1;
	else
	{
		list_ptr->task_ptr[lastIdx] = rec_ptr;
		(list_ptr->task_count)++;
		return 1;
	}
}

struct task_t *task_list_access(struct task_list_t *list_ptr, int index)
{
    assert(list_ptr != NULL && "TASK LIST NULL IN ACCESS\n");
    struct task_t* a_task;
	if (index >= list_ptr->task_count)
		a_task = NULL;
	else
		a_task = list_ptr->task_ptr[index];
	return a_task;
}

struct task_t *task_list_remove(struct task_list_t *list_ptr, int index)
{
    assert(list_ptr != NULL && "LIST NULL IN REMOVE\n");
    struct task_t* task = NULL;
	if (index >= list_ptr->task_count)
		task = NULL;
	else
	{
		task = list_ptr->task_ptr[index];
		while (index < list_ptr->task_count)
		{
			list_ptr->task_ptr[index] = list_ptr->task_ptr[index+1];
			index++;
		}
		(list_ptr->task_count)--;
	}
    return task;
}



int task_list_lookup_first_priority(struct task_list_t *list_ptr, int priority)
{
    assert(list_ptr != NULL);
	int found = -1;
	int i = 0;
	while (i < list_ptr->task_count)
	{
		if (list_ptr->task_ptr[i]->priority == priority)
			return i;
		else
			i++;
	}
    return found;
}

int task_list_lookup_id(struct task_list_t *list_ptr, int task_id)
{
    assert(list_ptr != NULL);
	int found = -1;
	int i = 0;
	while (i < list_ptr->task_count)
	{
		if (list_ptr->task_ptr[i]->task_id == task_id)
			return i;
		else
			i++;
	}

    return found;
}


struct task_t *task_list_access_priority(struct task_list_t *list_ptr, int priority)
{
    assert(list_ptr != NULL && "TASK LIST NULL IN ACCESS\n");
	int i = 0;
	while (i < list_ptr->task_count)
	{
		if (list_ptr->task_ptr[i]->priority == priority)
			return list_ptr->task_ptr[i];
		else
			i++;
	}
    return NULL;
}

struct task_t *task_list_remove_priority(struct task_list_t *list_ptr, int priority)
{
    assert(list_ptr != NULL && "LIST NULL IN REMOVE\n");
    struct task_t* task = NULL;
	int i = 0;
	while (i < list_ptr->task_count)
	{
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

struct task_t *task_list_access_id(struct task_list_t *list_ptr, int id)
{
    assert(list_ptr != NULL && "TASK LIST NULL IN ACCESS\n");
	int i = 0;
	while (i < list_ptr->task_count)
	{
		if (list_ptr->task_ptr[i]->task_id == id)
			return list_ptr->task_ptr[i];
		else
			i++;
	}
    return NULL;
}

struct task_t *task_list_remove_id(struct task_list_t *list_ptr, int id)
{
    assert(list_ptr != NULL && "LIST NULL IN REMOVE\n");
    struct task_t* task = NULL;
	int i = 0;
	while (i < list_ptr->task_count)
	{
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
				while (list_ptr->task_ptr[i]->args[j] == args[j] && j < nargs)
					j++;
				if (j == nargs)
					return i;
			}
	}
    return -1;
}

void task_list_set_state(struct task_list_t *list_ptr, int id, enum state state)
{
	enum state current_state = -1;
	int i = 0;
	while (current_state == -1)
	{
		if (list_ptr->task_ptr[i]->task_id == id)
			current_state = list_ptr->task_ptr[i]->state;
	}
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

struct task_t* task_list_schedule(struct task_list_t *list_ptr, int priority, int id)
{
    struct task_t* task = NULL;
	int i;
	for (i = 0; i < list_ptr->task_count; i++)
	{
		if (list_ptr->task_ptr[i]->task_id == id)
		{
			if (list_ptr->task_ptr[i]->state != FINISHED && 
			list_ptr->task_ptr[i]->state != RUNNING)
			{
				list_ptr->task_ptr[i]->state = RUNNING;
				return list_ptr->task_ptr[i];
			}
		}
	}
	// If this id is not found
	for (i = 0; i < list_ptr->task_count; i++)
	{
		if (list_ptr->task_ptr[i]->priority == priority)
		{		
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
