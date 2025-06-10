#include <stdio.h>
#include <stack.h>

#define STACKLIMIT 50

double stack[STACKLIMIT];
static int stackp = 0;

void push(double value) {
    if (stackp >= STACKLIMIT) {
        printf("Error: Stack full.\n");
    } else {
        stack[stackp++] = value;
    }
}

double pop(void) {
    double popped;

    if (stackp <= 0) {
        printf("Error: Stack empty.\n");
        return 0;
    } else {
        popped = stack[--stackp];
        stack[stackp] = 0;
        return popped;
    }
}

double top(void) {
    return stack[stackp-1];
}

int topp(void) {
    return stackp;
}

void clear(void) {
    for (int i = 0; i <= STACKLIMIT; i++) {
        stack[i] = 0.0;
    }
    stackp = 0;
}