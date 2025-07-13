#include <windows.h> // Hooray.
#include "mymalloc.h"

/* This is a different take on implementing `malloc` and `free`, as this is less complicated. */

typedef struct {
    int is_free;
    void *space;
    unsigned int nbytes;
} Block;

Block blocks[MAX_BLOCKS];

// Returns a pointer to `nbytes` bytes of memory on the heap.
void *morecore(unsigned int nbytes) {
    return HeapAlloc(GetProcessHeap(), 0, nbytes);
}

void *malloc(unsigned int nbytes) {
    Block *iblock, *jblock;
    unsigned int clampbytes = (MIN_BYTES > nbytes) ? MIN_BYTES : nbytes;

    if (nbytes <= 0) {
        return NULL;
    }

    for (int i = 0; i < MAX_BLOCKS; i++) {
        iblock = &blocks[i];

        if (iblock->space == NULL) {
            if ((iblock->space = morecore(clampbytes)) == NULL) {
                return NULL;
            }

            iblock->is_free = 1;
            iblock->nbytes = clampbytes;
        }

        if (iblock->is_free && iblock->nbytes >= nbytes) {
            if (iblock->nbytes == nbytes) {
                iblock->is_free = 0;
                return iblock->space;
            }

            // If it's too big, look further to a find a new block to be made.
            for (int j = i; j < MAX_BLOCKS; j++) { 
                jblock = &blocks[j];

                // Find a new block for it the leftover to point to.
                if (jblock->space == NULL) {
                    // Split!
                    int leftover = (iblock->nbytes - nbytes);

                    iblock->is_free = 0;
                    iblock->nbytes -= leftover;

                    jblock->is_free = 1;
                    jblock->nbytes = leftover;
                    jblock->space = iblock->space + iblock->nbytes;

                    return iblock->space;
                }
            }
        }
    }

    return NULL;
}

void *calloc(unsigned int nobj, unsigned int size) {
    unsigned int nbytes = nobj*size;
    char *space = (char *)malloc(nbytes);

    if (space == NULL) {
        return NULL;
    }

    for (int i = 0; i < nbytes; i++) {
        space[i] = 0;
    }

    return space;
}

void free(void *p) {
    Block *left = NULL;
    Block *right = NULL;
    Block *free = NULL;

    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (blocks[i].space == NULL) {
            continue;
        }

        // Get the free block found.
        if (p == blocks[i].space) {
            if (blocks[i].is_free == 1) {
                break;
            }
            blocks[i].is_free = 1;
            free = &blocks[i];
        }

        // Store adjacent free blocks.
        if (blocks[i].is_free) {
            if ((blocks[i].space + blocks[i].nbytes) == p) {
                left = &blocks[i];
            } else if (free && ((blocks[i].space - free->nbytes) == p)) {
                right = &blocks[i];
            }
        }

    }

    if (free == NULL) {
        return;
    }

    // Coalesce with the free right neighbor, if there is one.
    if (right) {
        right->space = NULL;
        right->is_free = 0;
        free->nbytes += right->nbytes;
        right->nbytes = 0;
    }

    // Ditto with the left.
    if (left) {
        free->space = NULL;
        free->is_free = 0;
        left->nbytes += free->nbytes;
        free->nbytes = 0;
    }

    return;
}

void bfree(void *p, unsigned int n) {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (blocks[i].space == NULL) {
            blocks[i].is_free = 1;
            blocks[i].nbytes = n;
            blocks[i].space = p;
            break;
        }
    }
}

// int main(void) {
//     int *n = malloc(10*sizeof(int));
//     char *s = malloc(20*sizeof(char));
//     long *b = malloc(40*sizeof(long));
//     int thing1[10];

//     free(s);
//     free(n);
//     bfree(thing1, 10*sizeof(int));

//     for (int i = 0; i < 20; i++) {
//         printf("%2i %s %3i %p\n", i, (blocks[i].is_free) ? "y" : "n", blocks[i].nbytes,  blocks[i].space);
//     }
// }

/*
806: The standard library function `calloc(n, size)` returns a pointer to `n`
     objects of size `size`, with the storage initialized to zero.
     Write calloc, by calling malloc or by modifying it.
807: `malloc` accepts a size request without checking its plausibility; free
     believes that the block it is asked to free contains a valid size field.
     Improve these routines so they make more pains with error checking.
808: Write a routine `bfree(p, n)` that will free any arbitrary block
     `p` of `n` characters into the free list maintained by malloc and free.
     By using `bfree`, a user can add a static or external array to the free
     list at any time.
*/