#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "nstring.h"

#define MAX_SIZE 100

typedef struct {
    char *name;
    char *def;
} DefPair;

DefPair *def_pairs[MAX_SIZE];   // An array of pointers to `DefPair`s.
int gaps[MAX_SIZE];             // An array of indices to `DefPairs` where there is `NULL`.
int top = 0;                    // Points to the index where the next element will be pushed to in `def_pairs`.
int top_gap = 0;                // Points to the index where the next element will be pushed to in `top_gap`.

// Finds and returns the index of which `DefPair` in `def_pairs` holds the `*name`, if there is one.
int lookup(char *name);

// Installs and returns a new or existing `DefPair` with its `*name` and new `*def`.
DefPair *install(char *name, char *def);

// Uninstall an existing `DefPair` given its `*name`. Returns NULL.
void *undef(char *name);

int main(void) {
    DefPair *def1 = install("HASHSIZE", "101");
    DefPair *def2 = install("String", "char *");
    DefPair *def3 = install("stdout", "2");
    assert(def1);
    assert(def2);
    assert(def3);
    printf("%p %s %s\n", def1, def1->name, def1->def);
    undef("String");
    def2 = install("wait", "what?");
    printf("%p %s %s\n", def2, def2->name, def2->def);
    printf("%p %s %s\n", def3, def3->name, def3->def);

    return 0;
}

int lookup(char *name) {
    for (int i = 0; i < top; i++) {
        if (def_pairs[i] == NULL) {
            continue;
        }
        if (!strcmp(name, def_pairs[i]->name)) {
            return i;
        }
    }
    return -1;
}

DefPair *install(char *name, char *def) {
    int index = lookup(name);
    DefPair *pair = NULL;

    if (index != -1) {
        pair = def_pairs[index];
    }

    // Exits if stack is full and there are no more gaps.
    if (top >= MAX_SIZE && top_gap == 0) {
        return NULL;
    }

    if (pair == NULL) {
        pair = (DefPair *)malloc(sizeof(DefPair));
        pair->name = (char *)malloc((strlen(name)+1)*sizeof(char));

        // Fills in a gap if there is one, else push like a stack.
        if (pair == NULL || pair->name == NULL) {
            free(pair->name);
            free(pair);
            return NULL;
        }

        strcpy(pair->name, name);

        if (top_gap > 0) {
            def_pairs[gaps[top_gap-1]] = pair;
            gaps[--top_gap] = 0;
        } else {
            def_pairs[top++] = pair;
        }
    }

    // Create a new definition if there isn't one or it's a different one than assigned.
    if (pair->def == NULL || strcmp(def, pair->def)) {
        free(pair->def);
        pair->def = (char *)malloc((strlen(def)+1)*sizeof(char));
        if (pair->def == NULL) {
            free(pair->name);
            free(pair);
            return NULL;
        }
        strcpy(pair->def, def);
    }

    return pair;
}

void *undef(char *name) {
    int index = lookup(name);
    DefPair *pair = NULL;

    if (index != -1) {
        pair = def_pairs[index];
    }

    if (pair) {
        free(pair->def);
        free(pair->name);
        free(pair);
    }

    // If the index found is at the top, decrement the top. Otherwise, add a gap.
    if (index == top-1) {
        top--;
    } else {
        gaps[top_gap++] = index;
    }

    return NULL;
}

/*
605: Write a function `undef` that will remove a name and definition from the table
    maintained by `lookup` and `install`.
*/