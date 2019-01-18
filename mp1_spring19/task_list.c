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
    
    struct task_list_t* list = NULL;
    
    // alloc memory

    return list;
}

void task_list_destruct(struct task_list_t *list_ptr)
{
    assert(list_ptr != NULL && "TASK LIST NULL IN DESTRUCT");

    // free memory
}

int task_list_number_entries(struct task_list_t *list_ptr)
{
    assert(list_ptr != NULL);
    return -1;
}

int task_list_add(struct task_list_t *list_ptr, struct task_t *rec_ptr)
{
    assert(list_ptr != NULL);
    int lastIdx = -1; 
    return -1;
}

struct task_t *task_list_access(struct task_list_t *list_ptr, int index)
{
    assert(list_ptr != NULL && "TASK LIST NULL IN ACCESS\n");
    return NULL;
}

struct task_t *task_list_remove(struct task_list_t *list_ptr, int index)
{
    assert(list_ptr != NULL && "LIST NULL IN REMOVE\n");
    struct task_t* task = NULL;
    return task;
}





int task_list_lookup_first_priority(struct task_list_t *list_ptr, int priority)
{
    assert(list_ptr != NULL);
    return -1;
}

int task_list_lookup_id(struct task_list_t *list_ptr, int task_id)
{
    assert(list_ptr != NULL);
    return -1;
}


struct task_t *task_list_access_priority(struct task_list_t *list_ptr, int priority)
{
    assert(list_ptr != NULL && "TASK LIST NULL IN ACCESS\n");
    return NULL;
}

struct task_t *task_list_remove_priority(struct task_list_t *list_ptr, int priority)
{
    assert(list_ptr != NULL && "LIST NULL IN REMOVE\n");
    struct task_t* task = NULL;
    
    return task;
}

struct task_t *task_list_access_id(struct task_list_t *list_ptr, int id)
{
    assert(list_ptr != NULL && "TASK LIST NULL IN ACCESS\n");
    return NULL;
}

struct task_t *task_list_remove_id(struct task_list_t *list_ptr, int id)
{
    assert(list_ptr != NULL && "LIST NULL IN REMOVE\n");
    struct task_t* task = NULL;
    return task;
}


int task_list_determine_runable(struct task_list_t *list_ptr, int nargs, int*args)
{
    return -1;
}

void task_list_set_state(struct task_list_t *list_ptr, int id, enum state state)
{

}

struct task_list_t* task_list_remove_finished(struct task_list_t *list_ptr)
{
    struct task_list_t* rm = NULL;
    

   return rm; 
}

struct task_t* task_list_schedule(struct task_list_t *list_ptr, int priority, int id)
{
    struct task_t* task = NULL;
    return task;
}
