/* mem.c
 * Casey Hird
 * crhird
 * ECE 2230 Spring 2019
 * MP4
 *
 * Propose: A template for MP4
 *
 * Assumptions:
 *
 * Bugs:
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>

#include "mem.h"

/* chunk_t definition (do not modify).
 * sizeof(chunk_t) must equal SIZEOF_CHUNK_T in mem.h.
 */
typedef struct chunk_tag {
    struct chunk_tag *next;  /* pointer to the next free block */
    long size;               /* size of memory block in units of
                                sizeof(chunk_t) */
} chunk_t;

typedef struct heap_stats {
    int numItems;    /* number of chunks in the free list    */
    int min;         /* size of the smallest chunk, in bytes */
    int max;         /* size of the largest chunk, in bytes  */
    int average;     /* average size of the chunks, in bytes */
    int totalBytes;  /* total size of all chunks, in bytes   */

    /* the following two fields are updated in morecore() */
    int numSbrkCalls;  /* number of successful calls to sbrk()  */
    int numPages;      /* number of pages allocated with sbrk() */
} heap_stats_t;

/* global variables exported via mem.h */
int SearchPolicy = FIRST_FIT;
int SearchLoc = HEAD_FIRST;
int Coalescing = FALSE;

/* global variables restricted to mem.c only */
static chunk_t Dummy = {
    &Dummy,  /* next */
    0        /* size */
};
static chunk_t * Rover = &Dummy;
static heap_stats_t stats;  /* initialized by the O/S to all 0s */


/* prototypes for functions private to mem.c */
void mem_validate(void);
chunk_t *morecore(int);

/* function to request 1 or more pages from the operating system.
 *
 * new_bytes must be the number of bytes that are being requested from
 *           the OS with the sbrk command.  It must be an integer
 *           multiple of the PAGESIZE
 *
 * returns a pointer to the new memory location.  If the request for
 * new memory fails this function simply returns NULL, and assumes some
 * calling function will handle the error condition.  Since the error
 * condition is catastrophic, nothing can be done but to terminate
 * the program.
 */
chunk_t *morecore(int new_bytes)
{
    char *cp;
    chunk_t *new_p;

    /* assert preconditions */
    assert(new_bytes % PAGESIZE == 0 && new_bytes > 0);
    assert(PAGESIZE % sizeof(chunk_t) == 0);

    /* allocate memory using sbrk() */
    cp = sbrk(new_bytes);
    if (cp == (char *) -1)  /* no space available */
        return NULL;
    new_p = (chunk_t *) cp;

    /* update statistics */
    stats.numSbrkCalls++;
    stats.numPages = new_bytes/PAGESIZE;

    return new_p;
}

/* TODO update this documentation according to the programming guide */
void Mem_free(void *return_ptr)
{
    /* TODO obviously the next line is WRONG!!!!  You must fix it. */
    free(return_ptr);
}

/* TODO update this documentation */
void *Mem_alloc(int nbytes) {
    /* assert preconditions */
    assert(nbytes > 0);
    // Determine how many chunk sized units are needed
    nunits = (nbytes / SIZEOF_CHUNK_T) + SIZEOF_CHUNK_T;
    if (nbytes % nbytes != 0)
    {
      nunits += SIZEOF_CHUNK_T;
    }
    // Save search start location
    chunk_t *start;
    if (SearchLoc == HEAD_FIRST)
    {
      Rover = &Dummy;
      start = Rover;
    }
    else if (SearchLoc == ROVER_FIRST)
    {
      start = Rover;
    }
    else
    {
      printf("Invalid search position.\n");
      exit(1);
    }
    // Search for a big enough block according to search policy
    chunk_t *removal_spot;
    long removal_size = Rover->size;
    // First fit
    if (SearchPolicy == FIRST_FIT)
    {
      do {
        // Keep the first chunk that is big enough
        if (Rover->size >= nunits-1)
        {
          removal_size = Rover->size;
          removal_spot = Rover;
        }
        Rover = Rover->next;
      } while (removal_spot == NULL && Rover != start);
    }
    // Best fit
    else if (SearchPolicy == BEST_FIT)
    {
      removal_spot = Rover;
      do {
        if (Rover->size >= nunits-1 && Rover-size < removal_size)
        {
          removal_size = Rover->size;
          removal_spot = Rover;
        }
      } while(removal_size != nunits-1 && Rover != start);
      // If best fit is still too small, set removal_spot to NULL
      if (removal_size < nunits-1)
      {
        removal_spot = NULL;
      }
    }
    // Worst fit
    else if (SearchPolicy == WORST_FIT)
    {
      int max_size = removal_size;
      removal_spot = Rover;
      // Find the biggest free chunk
      do {
        // If a bigger chunk is found, save that size and position
        if (Rover->size > max_size)
        {
          removal_size = Rover->size;
          removal_spot = Rover;
        }
        Rover = Rover->next;
      } while (Rover != start);
      // If max size is still too small, set removal_spot to NULL
      if (removal_size < nunits-1)
      {
        removal_spot = NULL;
      }
    }
    // Error
    else
    {
      printf("Not a valid search policy.\n");
      exit(1);
    }
    // If a large enough chunk was not found, add memory to the
    // free list using morecore
    if (removal_spot == NULL)
    {
      removal_size = nunits;
      // FIXME DOES IT MATTER WHERE MEMORY IS ADDED???????????????????????????????
      // Increase nunits to be a multiple of PAGESIZE
      if (removal_size % PAGESIZE != 0)
      {
        removal_size += PAGESIZE - (removal_size % PAGESIZE);
      }
      removal_spot = Rover->next;
      Rover->next = morecore(removal_size);
      Rover = Rover->next;
      removal_size--;
      Rover->size = removal_size;
      Rover->next = removal_spot;
      removal_spot = Rover;
      Rover = Rover->next;
    }
    // User Rover to find chunk before removal_spot
    while (Rover->next != removal_spot)
    {
      Rover = Rover->next;
    }
    // Adjust header block for chunk that will remain
    if (removal_size > nunits-1)
    {
      // Skip over chunk being removed
      Rover->next = removal_spot + nunits;
      Rover = Rover->next;
      // Connect new header to the free list
      Rover-next = removal_spot->next;
      Rover->size = removal_size - (nunits-1);
      // Remove old header dangling pointer
      removal_spot->next = NULL;
    }
    // Skip that if chunk was a perfect fit
    else{
      Rover->next = removal_spot->next;
      removal_spot->next = NULL;
    }
    // Return pointer to free Memory
    return removal_spot++;
}

/* prints stats about the current free list
 *
 * -- number of items in the linked list including dummy item
 * -- min, max, and average size of each item (in bytes)
 * -- total memory in list (in bytes)
 * -- number of calls to sbrk and number of pages requested
 *
 * A message is printed if all the memory is in the free list
 */
void Mem_stats(void)
{
    /* TODO calculate the latest stats and put them in the stats struct */

    /* ======= DO NOT MODIFY FROM HERE TO END OF Mem_stats() ======= */
    printf("\n\t\tMP4 Heap Memory Statistics\n"
            "----------------------------------------------------\n\n"
            "\tNumber of blocks in free list: %d\n"
            "\tMin: %d\n"
            "\tMax: %d\n"
            "\tAverage: %d\n"
            "\tTotal bytes in free list: %d\n"
            "\tNumber of sbrk calls: %d\n"
            "\tNumber of requested pages: %d\n"
            "\tHeap status:  %s\n",
            stats.numItems, stats.min, stats.max, stats.average, stats.totalBytes,
            stats.numSbrkCalls, stats.numPages,
            stats.totalBytes == stats.numPages*PAGESIZE ? \
            "all memory is in the heap -- no leaks are possible\n"\
            : "heap is in-use -- leaks are possible\n");
}

/* print table of memory in free list
 *
 * The print should include the dummy item in the list
 */
void Mem_print(void)
{
    assert(Rover != NULL && Rover->next != NULL);
    chunk_t *p = Rover;
    chunk_t *start = p; /* save my starting block */
    do {
        printf("p=%p, size=%ld, end=%p, next=%p %s\n",
                p, p->size, p + p->size, p->next, p->size!=0?"":"<-- dummy");
        p = p->next;
    } while (p != start); /* only 1 time through the list */
    mem_validate();
}

/* This is an experimental function to attempt to validate the free
 * list when coalescing is used.  It is not clear that these tests
 * will be appropriate for all designs.  If your design utilizes a different
 * approach, that is fine.  You do not need to use this function and you
 * are not required to write your own validate function.
 */
void mem_validate(void)
{
    assert(Rover != NULL && Rover->next != NULL);
    assert(Rover->size >= 0);
    int wrapped = FALSE;
    int found_dummy = FALSE;
    int found_rover = FALSE;
    chunk_t *p, *largest, *smallest;

    /* for validate begin at Dummy */
    p = &Dummy;
    do {
        if (p->size == 0) {
            assert(found_dummy == FALSE);
            found_dummy = TRUE;
        } else {
            assert(p->size > 0);
        }
        if (p == Rover) {
            assert(found_rover == FALSE);
            found_rover = TRUE;
        }
        p = p->next;
    } while (p != &Dummy);
    assert(found_dummy == TRUE);
    assert(found_rover == TRUE);

    if (Coalescing) {
        do {
            if (p >= p->next) {
                /* this is not good unless at the one wrap */
                if (wrapped == TRUE) {
                    printf("validate: List is out of order, already found wrap\n");
                    printf("first largest %p, smallest %p\n", largest, smallest);
                    printf("second largest %p, smallest %p\n", p, p->next);
                    assert(0);   /* stop and use gdb */
                } else {
                    wrapped = TRUE;
                    largest = p;
                    smallest = p->next;
                }
            } else {
                assert(p + p->size < p->next);
            }
            p = p->next;
        } while (p != &Dummy);
        assert(wrapped == TRUE);
    }
}

/* vi:set ts=8 sts=4 sw=4 et: */