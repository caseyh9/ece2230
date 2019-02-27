/* list.c                  <<-- A template to update and
 * Prof. Calhoun           <<-- change
 * jonccal
 * ECE 2230 Spring 2019
 * MP3
 *
 * Propose: A template for list.c. You will make many changes.
 *
 * Assumptions: Many details are incomplete.
 *
 * Bugs: Many details have not been implemented.
 *
 * The interface definition for the two-way linked list ADT is based on one
 * defined by OPNET, Inc. http://www.opnet.com/
 */

#include <stdlib.h>
#include <assert.h>

#include "datatypes.h"   /* defines data_t */
#include "list.h"        /* defines public functions for list ADT */

/* definitions for private constants used in list.c only */

#define LIST_SORTED_ASCENDING   -29634
#define LIST_SORTED_DESCENDING  -61801
#define LIST_UNSORTED           -72467

/* prototypes for private functions used in list.c only */
void list_debug_validate(list_t *L);
void list_bubble_sort(list_t** L, int sort_order);
void list_insertion_sort(list_t** L, int sort_order);
void list_recursive_selection_sort(list_t** L, int sort_order);
void list_selection_sort(list_t** L, int sort_order);
void list_merge_sort(list_t** L, int sort_order);

/* sorting helper functions) */

/* Sorts a list used a specific sorting algorithm and direction.
 *
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from list_construct.
 *
 * sort_type: sorting algorithm used during sorting: 1) Bubble Sort;
 *            2)Insertion Sort; 3) Recursive Selection Sort;
 *            4) Iterative Selection Sort; and 5) Merge Sort
 *
 * sort_order: if 1 then the items are to be sorted in descending order.
 *             if 2 then the items are to be sorted in ascending order.
 *
 * return value: None.
 */
void list_sort(list_t **list_ptr, int sort_type, int sort_order)
{
    /* TODO: Complete the function sorting the list */

   (*list_ptr)->list_sorted_state = LIST_SORTED_ASCENDING;// ? is ASCENDING or DESCENDING;
    list_debug_validate(*list_ptr);
}

/* Sorting the list via the insertion sort algorithm
 *
 * L: pointer to list-of-interest.
 *
 * sort_order: 1 sort list in descending order 2 sort in ascending order
 */
void list_bubble_sort(list_t** L, int sort_order)
{
    /* TODO: see MP3 document for implementation notes */
}

/* Sorting the list via the insertion sort algorithm
 *
 * L: pointer to list-of-interest.
 *
 * sort_order: 1 sort list in descending order 2 sort in ascending order
 */
void list_insertion_sort(list_t** L, int sort_order)
{
    /* TODO: see MP3 document for implementation notes */
}

/* Sorting the list via the recursive selection sort algorithm
 *
 * L: pointer to list-of-interest.
 *
 * sort_order: 1 sort list in descending order 2 sort in ascending order
 */
void list_recursive_selection_sort(list_t** L, int sort_order)
{

    /* TODO: see MP3 document for implementation notes */
}

/* Sorting the list via the selection sort algorithm
 *
 * L: pointer to list-of-interest.
 *
 * sort_order: 1 sort list in descending order 2 sort in ascending order
 */
void list_selection_sort(list_t** L, int sort_order)
{
    /* TODO: see MP3 document for implementation notes */

}

/* Sorting the list via the merge sort algorithm
 *
 * L: pointer to list-of-interest.
 *
 * sort_order: 1 sort list in descending order 2 sort in ascending order
 */
void list_merge_sort(list_t** L, int sort_order)
{
    /* TODO: see MP3 document for implementation notes */

}




/* ----- below are the functions  ----- */

/* Obtains a pointer to an element stored in the specified list, at the
 * specified list position
 *
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from list_construct.
 *
 * pos_index: position of the element to be accessed.  Index starts at 0 at
 *            head of the list, and incremented by one until the tail is
 *            reached.  Can also specify LISTPOS_HEAD and LISTPOS_TAIL
 *
 * return value: pointer to element accessed within the specified list.  A
 * value NULL is returned if the pos_index does not correspond to an element in
 * the list.  For example, if the list is empty, NULL is returned.
 */
data_t * list_access(list_t *list_ptr, int pos_index)
{
    list_node_t *L;

    assert(list_ptr != NULL);

    /* debugging function to verify that the structure of the list is valid */
    list_debug_validate(list_ptr);

    /* TODO: handle four special cases.
     *   1.  The list is empty
     *   2.  Asking for the head
     *   3.  Asking for the tail
     *   4.  Asking for invalid pos
     */
     // Case 1
   	if (list_ptr->head == NULL){
   	 	return NULL;
   	}
   	// Case 4
   	else if (pos_index < 0 || pos_index >= list_ptr->current_list_size){
   		return NULL;
   	}
   	// Case 2
   	else if (pos_index == 0 || pos_index == LISTPOS_HEAD){
   		L = list_ptr->head;
   	}
   	// Case 3
   	else if (pos_index == LISTPOS_TAIL ||
   		pos_index == (list_ptr->current_list_size)-1){

   		L = list_ptr->tail;
   	}
    /* we now know pos_index is for an interal element */
    /* TODO: loop through the list until find correct position index */
    else{
      int i;
      L = list_ptr->head;
      for (i = 0; i < pos_index; i++){
        L = L->next;
      }
    }
    assert(L != NULL);
    return L->data_ptr;
}

/* Allocates a new, empty list
 *
 * By convention, the list is initially assumed to be sorted.  The field sorted
 * can only take values LIST_SORTED_ASCENDING LIST_SORTED_DESCENDING or
 * LIST_UNSORTED
 *
 * Use list_free to remove and deallocate all elements on a list (retaining the
 * list itself).
 *
 * comp_proc = pointer to comparison function
 *
 * Use the standard function free() to deallocate a list which is no longer
 * useful (after freeing its elements).
 */
list_t * list_construct(int (*fcomp)(const data_t *, const data_t *),
        void (*dataclean)(data_t *))
{
    list_t *L;
    L = (list_t *) malloc(sizeof(list_t));
    L->head = NULL;
    L->tail = NULL;
    L->current_list_size = 0;
    L->list_sorted_state = LIST_SORTED_ASCENDING;
    L->comp_proc = fcomp;
    L->data_clean = dataclean;

    /* the last line of this function must call validate */
    list_debug_validate(L);
    return L;
}

/* Finds an element in a list and returns a pointer to it.
 *
 * list_ptr: pointer to list-of-interest.
 *
 * elem_ptr: element against which other elements in the list are compared.
 *           Note: use the comp_proc function pointer found in the list_t
 *           header block.
 *
 * The function returns a pointer to the matching element with lowest index if
 * a match if found.  If a match is not found the return value is NULL.
 *
 * The function also returns the integer position of matching element with the
 *           lowest index.  If a matching element is not found, the position
 *           index that is returned should be -1.
 *
 * pos_index: used as a return value for the position index of matching element
 *
 *
 */
data_t * list_elem_find(list_t *list_ptr, data_t *elem_ptr, int *pos_index)
{
    list_debug_validate(list_ptr);
	data_t* d = NULL;

    /*TODO: */
    /* fix the return value */
	// If list is empty or uninitialized return NULL and -1
	if (list_ptr == NULL || list_ptr->head == NULL){
		*pos_index = -1;
		return NULL;
	}
	// Search for matching element
	else{
		*pos_index = 0;
		list_node_t* N = list_ptr->head;
		while (*pos_index<(list_ptr->current_list_size)
			&& list_ptr->comp_proc(N->data_ptr, elem_ptr) == 0 ){

			N = N->next;
			(*pos_index)++;
		}
		// If we went past the end of the list, need to set pos_index
		if (*pos_index == list_ptr->current_list_size){
			*pos_index = -1;
		}
		// Otherwise, pos_index is at the correct value nad we need to set d
		else{
			d = N->data_ptr;
		}
	}

    return d;
}
/* Deallocates the contents of the specified list, releasing associated memory
 * resources for other purposes.
 *
 * Free all elements in the list, and the header block.  Use the data_clean
 * function point to free the data_t items in the list.
 */
void list_destruct(list_t *list_ptr)
{
    /* the first line must validate the list */
    list_debug_validate(list_ptr);
	assert(list_ptr != NULL);

	// Set up loop variables, one to lead and one to trail
	list_node_t *A, *B;
	// If list is empty, skip
	if (list_ptr->head == NULL && list_ptr->tail == NULL){
		assert(list_ptr->current_list_size == 0);
	}
	// If there is only 1 node
	else if (list_ptr->current_list_size == 1){
		free(list_ptr->head);
	}
	// Otherwise, there are multiple nodes
	else{
		// Initialize loop variables
		A = list_ptr->head;
		B = A->next;
		// For each node, free the data then the node itself
		while (B != NULL){
			list_ptr->data_clean(A->data_ptr);
			free(A);
			A = B;
			B = B->next;
		}
		list_ptr->data_clean(A->data_ptr);
		free(A);
	}
	// Free the last node and the header block
	free(list_ptr);
}
/* Inserts the specified data element into the specified list at the specified
 * position.
 *
 * list_ptr: pointer to list-of-interest.
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * pos_index: numeric position index of the element to be inserted into the
 *            list.  Index starts at 0 at head of the list, and incremented by
 *            one until the tail is reached.  The index can also be equal
 *            to LISTPOS_HEAD or LISTPOS_TAIL (these are special negative
 *            values use to provide a short cut for adding to the head
 *            or tail of the list).
 *
 * If pos_index is greater than the number of elements currently in the list,
 * the element is simply appended to the end of the list (no additional elements
 * are inserted).
 *
 * Note that use of this function results in the list to be marked as unsorted,
 * even if the element has been inserted in the correct position.  That is, on
 * completion of this subroutine the list_ptr->list_sorted_state must be equal
 * to LIST_UNSORTED.
 */
void list_insert(list_t *list_ptr, data_t *elem_ptr, int pos_index)
{
    assert(list_ptr != NULL);

	// Create and allocate memory for new list node
	list_node_t *new_node = (list_node_t*)malloc(sizeof(list_node_t));
	new_node->data_ptr = elem_ptr;
	// If pos_index is an invalid negative value, exit the function
	if (pos_index < 0 && pos_index != LISTPOS_HEAD && pos_index != LISTPOS_TAIL){
		return;
	}
	// Insert into empty list
	else if (list_ptr->head == NULL && list_ptr->tail == NULL){
		new_node->prev = NULL;
		new_node->next = NULL;
		list_ptr->head = new_node;
		list_ptr->tail = new_node;
	}
	// Insert element at head
	else if (pos_index == 0 || pos_index == LISTPOS_HEAD){
		new_node->prev = NULL;
		new_node->next = list_ptr->head;
		list_ptr->head->prev = new_node;
		list_ptr->head = new_node;
	}
	// Insert element at tail
	else if (pos_index >= list_ptr->current_list_size || pos_index == LISTPOS_TAIL){
		new_node->prev = list_ptr->tail;
		new_node->next = NULL;
		list_ptr->tail->next = new_node;
		list_ptr->tail = new_node;
	}
	// Insert element anywhere else in the list
	else{
		list_node_t *front = list_ptr->head;
		list_node_t *back;
		int i;
		// Get the node currently at pos_index
		for (i = 0; i < pos_index; i++){
			front = front->next;
		}
		back = front->prev;
		new_node->prev = back;
		back->next = new_node;
		new_node->next = front;
		front->prev = new_node;
	}
	// Add one to list size
	(list_ptr->current_list_size)++;

    /*TODO*/
    /* the last two lines of this function must be the following */
    if (list_ptr->list_sorted_state != LIST_UNSORTED)
        list_ptr->list_sorted_state = LIST_UNSORTED;
    list_debug_validate(list_ptr);
}

/* Inserts the element into the specified sorted list at the proper position,
 * as defined by the comp_proc function pointer found in the header block.
 *
 * list_ptr: pointer to list-of-interest.
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * If you use list_insert_sorted, the list preserves its sorted nature.
 *
 * If you use list_insert, the list will be considered to be unsorted, even
 * if the element has been inserted in the correct position.
 *
 * If the list is not sorted and you call list_insert_sorted, this subroutine
 * should generate a system error and the program should immediately stop.
 *
 * The comparison procedure must accept two arguments (A and B) which are both
 * pointers to elements of type data_t.  The comparison procedure returns an
 * integer code which indicates the precedence relationship between the two
 * elements.  The integer code takes on the following values:
 *    1: A should be closer to the list head than B
 *   -1: B should be closer to the list head than A
 *    0: A and B are equal in rank
 * This definition results in the list being in ascending order.  To insert
 * in decending order, change the sign of the value that is returned.
 *
 * Note: if the element to be inserted is equal in rank to an element already
 * in the list, the newly inserted element will be placed after all the
 * elements of equal rank that are already in the list.
 */
void list_insert_sorted(list_t *list_ptr, data_t *elem_ptr)
{
    assert(list_ptr != NULL);
    assert(list_ptr->list_sorted_state != LIST_UNSORTED);
	int index;
	int current_state = list_ptr->list_sorted_state;

    /* insert your code here */
    /*TODO*/
	// Place data if list is empty
	if (list_ptr->head == NULL && list_ptr->tail == NULL){
		index = 0;
	}
	// Find the index at which to place the data
	index = 0;
	list_node_t *node = list_ptr->head;
	// Find index for ascending sort
	if (list_ptr->list_sorted_state == LIST_SORTED_ASCENDING){
		while (node != NULL && list_ptr->comp_proc(node->data_ptr,elem_ptr) != -1){
			index++;
			node = node->next;
		}
	}
	// Find index for descending sort
	else if (list_ptr->list_sorted_state == LIST_SORTED_DESCENDING){
		while (node != NULL && list_ptr->comp_proc(node->data_ptr,elem_ptr) != 1){
			index++;
			node = node->next;
		}
	}
	// Use the list_insert() function to insert at the found index
	list_insert(list_ptr, elem_ptr, index);
	// Reset the list state
	list_ptr->list_sorted_state = current_state;
    /* the last line of this function must be the following */
    list_debug_validate(list_ptr);
}

/* Removes an element from the specified list, at the specified list position,
 * and returns a pointer to the element.
 *
 * list_ptr: pointer to list-of-interest.
 *
 * pos_index: position of the element to be removed.  Index starts at 0 at
 *            head of the list, and incremented by one until the tail is
 *            reached.  Can also specify LISTPOS_HEAD and LISTPOS_TAIL
 *
 * Attempting to remove an element at a position index that is not contained in
 * the list will result in no element being removed, and a NULL pointer will be
 * returned.
 */
data_t * list_remove(list_t *list_ptr, int pos_index)
{
    list_debug_validate(list_ptr);
	// NOTE: we could write less code by using the list_access() function to
	// return the desired data, but I decided instead to repeat some of that
	// code here to avoid having to traverse the list a second time for removal.

	list_node_t *lead, *follow, *removed;
	data_t *data;

	// If the list does not exist, the list is empty, or the given index
	// does not exist, return NULL.
	if (list_ptr == NULL || (list_ptr->head == NULL && list_ptr->tail == NULL)
		|| (pos_index < 0 && pos_index != LISTPOS_HEAD && pos_index != LISTPOS_TAIL)
		|| pos_index >= list_ptr->current_list_size){

		return NULL;
	}
	// If there is only 1 node and the head or tail is chosen, remove it
	else if ((pos_index == 0 ||pos_index == LISTPOS_HEAD
	|| pos_index == LISTPOS_TAIL)
		&& list_ptr->current_list_size == 1){

		removed = list_ptr->head;
		data = removed->data_ptr;
		list_ptr->head = NULL;
		list_ptr->tail = NULL;
	}
	// Remove the list head if requested
	else if (pos_index == 0 || pos_index == LISTPOS_HEAD){
		follow = list_ptr->head;
		removed = follow;
		data = follow->data_ptr;
		lead = follow->next;
		lead->prev = NULL;
		list_ptr->head = lead;
	}
	// Remove the list tail if requested
	else if (pos_index == (list_ptr->current_list_size)-1
		|| pos_index == LISTPOS_TAIL){

		lead = list_ptr->tail;
		removed = lead;
		data = lead->data_ptr;
		follow = lead->prev;
		follow->next = NULL;
		list_ptr->tail = follow;
	}
	// Remove any other node requested
	else{
		removed = list_ptr->head;
		// Get to the index given
		int i;
		for (i = 0; i < pos_index; i++){
			removed = removed->next;
		}
		data = removed->data_ptr;
		follow = removed->prev;
		lead = removed->next;
		follow->next = lead;
		lead->prev = follow;
	}
	// Decrement the list size
	(list_ptr->current_list_size)--;
	// Free the removed node memory
	free(removed);
	// Prove that the data has been found if the function reached this point.
    assert(data != NULL);
	return data;
}

/* Reverse the order of the elements in the list.  Also change the
 * list_sorted_state flag.  This function can only be called on a list
 * that is sorted.
 *
 * list_ptr: pointer to list-of-interest.
 */
void list_reverse(list_t *list_ptr)
{
    assert(list_order(list_ptr) != 0);
	// If the list does not exist, is empty, or only has 1 element, we don't
	// need to do anything
	if (list_ptr == NULL || (list_ptr->head == NULL && list_ptr->tail == NULL)
		|| list_ptr->head == list_ptr->tail){
	}
	// If the list has only 1 element, skip this and just change the state
	else if (list_ptr->head != list_ptr->tail){
		// Otherwise, swap the prev and next pointers at each node
		list_node_t *node, *temp;
		node = list_ptr->head;
		// Set the first node as the new tail
		list_ptr->tail = node;
		// Swap prev and next
		while (node != NULL){
			temp = node->prev;
			node->prev = node->next;
			node->next = temp;
			node = node->prev;
		}
		// Set the last node as the new head
		list_ptr->head = temp->prev;
	}
	// Reverse the list_sorted_state
	if (list_ptr->list_sorted_state == LIST_SORTED_ASCENDING){
		list_ptr->list_sorted_state = LIST_SORTED_DESCENDING;
	}
	else if (list_ptr->list_sorted_state == LIST_SORTED_DESCENDING){
		list_ptr->list_sorted_state = LIST_SORTED_ASCENDING;
	}
    // after the list is reversed verify it is valid.
    list_debug_validate(list_ptr);
}

/* Obtains the length of the specified list, that is, the number of elements
 * that the list contains.
 *
 * list_ptr: pointer to list-of-interest.
 *
 * Returns an integer equal to the number of elements stored in the list.  An
 * empty list has a size of zero.
 */
int list_size(list_t *list_ptr)
{
    assert(list_ptr != NULL);
    assert(list_ptr->current_list_size >= 0);
    return list_ptr->current_list_size;
}

/* Obtains the sort status and order of the specified list.
 *
 * list_ptr: pointer to list-of-interest.
 *
 * Returns
 *    1: the list is sorted in ascending order
 *   -1: descending order
 *    0: the list is not sorted but a queue
 */
int list_order(list_t *list_ptr)
{
    assert(list_ptr != NULL);
    if (list_ptr->list_sorted_state == LIST_SORTED_ASCENDING)
        return 1;
    else if (list_ptr->list_sorted_state == LIST_SORTED_DESCENDING)
        return -1;
    else if (list_ptr->list_sorted_state == LIST_UNSORTED)
        return 0;
    else
        exit(5);  // this should not happen
}


/* This function verifies that the pointers for the two-way linked list are
 * valid, and that the list size matches the number of items in the list.
 *
 * If the linked list is sorted it also checks that the elements in the list
 * appear in the proper order.
 *
 * The function produces no output if the two-way linked list is correct.  It
 * causes the program to terminate and print a line beginning with "Assertion
 * failed:" if an error is detected.
 *
 * The checks are not exhaustive, so an error may still exist in the
 * list even if these checks pass.
 *
 * YOU MUST NOT CHANGE THIS FUNCTION.  WE USE IT DURING GRADING TO VERIFY THAT
 * YOUR LIST IS CONSISTENT.
 */
void list_debug_validate(list_t *L)
{
#ifdef VALIDATE
    list_node_t *N;
    int count = 0;
    assert(L != NULL);
    if (L->head == NULL)
        assert(L->tail == NULL && L->current_list_size == 0);
    if (L->tail == NULL)
        assert(L->head == NULL && L->current_list_size == 0);
    if (L->current_list_size == 0)
        assert(L->head == NULL && L->tail == NULL);
    assert(L->list_sorted_state == LIST_SORTED_ASCENDING
            || L->list_sorted_state == LIST_SORTED_DESCENDING
            || L->list_sorted_state == LIST_UNSORTED);

    if (L->current_list_size == 1) {
        assert(L->head == L->tail && L->head != NULL);
        assert(L->head->next == NULL && L->head->prev == NULL);
        assert(L->head->data_ptr != NULL);
    }
    if (L->head == L->tail && L->head != NULL)
        assert(L->current_list_size == 1);
    if (L->current_list_size > 1) {
        assert(L->head != L->tail && L->head != NULL && L->tail != NULL);
        N = L->head;
        assert(N->prev == NULL);
        while (N != NULL) {
            assert(N->data_ptr != NULL);
            if (N->next != NULL)
                assert(N->next->prev == N);
            else
                assert(N == L->tail);
            count++;
            N = N->next;
        }
        assert(count == L->current_list_size);
    }
    if (L->list_sorted_state != LIST_UNSORTED && L->head != NULL) {
        N = L->head;
        int comp_val = -1 * list_order(L);
        while (N->next != NULL) {
            assert((L->comp_proc)(N->data_ptr, N->next->data_ptr) != comp_val);
            N = N->next;
        }
    }
#endif
}
/* commands for vim. ts: tabstop, sts: softtabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
