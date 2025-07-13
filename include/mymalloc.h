// Used exclusively in exer806-807-808.c

#ifndef MALLOC_H
#define MALLOC_H

#define NULL ((void *)0)
#define MAX_BLOCKS 0xffff
#define MIN_BYTES 0xff
#define DEBUG 1

// Allocates and return `nbytes` of bytes on the heap.
// If allocation failed, return `NULL`.
void *malloc(unsigned int nbytes);

// Allocates and returns an array for `nobj` objects of size `size`.
// If allocation failed, return `NULL`.
void *calloc(unsigned int nobj, unsigned int size);

// Deallocates the memory pointed by `p` if not zero.
void free(void *p);

// Add a block of `n` bytes of characters in `p` to a future allocator.
void bfree(void *p, unsigned int n);

// Allocates and returns `nbytes` to the heap by calling memory to the OS.
// Returns NULL upon error.
void *morecore(unsigned int nbytes);

#endif