#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "nstring.h"

#define MAX_SIZE 100

char *defs[MAX_SIZE];            // An array of definitions, which is just a string.
int gaps[MAX_SIZE];              // An array of indices to `defs` where there is `NULL`.
int top = 0;                     // Points to the index where the next element will be pushed to in `defs`.
int top_gap = 0;                 // Points to the index where the next element will be pushed to in `top_gap`.

// Finds and returns the index of where `defs` holds the `*def`, if there is one.
int lookup(char *def);

// Installs and returns a new or existing definition with its `*def`.
char *install(char *def);

// Uninstall an existing `def`. Returns NULL.
void *undef(char *def);

int main(void) {
    char *def1 = install("HASHSIZE");
    char *def2 = install("String");


    printf("%p %s\n", def1, def1);
    printf("%p %s\n", def2, def2);

    undef(def2);
    def2 = install("HASHSIZ");

    printf("%p %s\n", def1, def1);
    printf("%p %s\n", def2, def2);

    return 0;
}

int lookup(char *def) {
    for (int i = 0; i < top; i++) {
        if (defs[i] == NULL) {
            continue;
        }
        if (!strcmp(def, defs[i])) {
            return i;
        }
    }
    return -1;
}

char *install(char *def) {
    int index = lookup(def);
    char *defp = NULL;

    if (index != -1) {
        defp = defs[index];
    }

    // Exits if stack is full and there are no more gaps.
    if (top >= MAX_SIZE && top_gap == 0) {
        return NULL;
    }

    if (defp == NULL) {
        defp = (char *)malloc((strlen(def)+1)*sizeof(char));

        // Fills in a gap if there is one, else push like a stack.
        if (defp == NULL) {
            return NULL;
        }
        
        strcpy(defp, def);
        if (top_gap > 0) {
            defs[gaps[top_gap-1]] = defp;
            gaps[--top_gap] = 0;
        } else {
            defs[top++] = defp;
        }
    }

    return defp;
}

void *undef(char *def) {
    int index = lookup(def);
    char *defp = NULL;

    if (index != -1) {
        defp = defs[index];
    }

    free(defp);

    // If the index found is at the top, decrement the top. Otherwise, add a gap.
    if (index == top-1) {
        top--;
    } else {
        gaps[top_gap++] = index;
    }

    return NULL;
}

/*
606: Implement a simple version of the `#define` processor (i.e., no arguments)
     suitable for use with C programs, based on the routines of this section.
     You may also find `getch` and `ungetch` helpful.
*/