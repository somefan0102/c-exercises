#include <stdio.h>
#include "nstring.h"

#define error(option, reason) printf("Error: Invalid operator. (%s)\n", option);\
printf("%s%c\"tail -h\" for more information.\n", reason, (reason[0] == '\0') ? '\0' : '\n');\
exit(1);

#define HELP \
"USAGE: tab (-h | ARGS)...\n\
\n\
expr is a program that lets you do stack based calculations.\n\
\n\
ARGS:\n\
\n\
(number)  Push a number onto stack.\n\
+ | add   Pop two numbers, push sum of them.\n\
- | sub   Pop two numbers, push difference of them.\n\
* | mul   Pop two numbers, push product of them.\n\
/ | div   Pop two numbers, push quotient of them.\n\
\n\
The first number popped is the last operand.\n"

#define MAX_STACK 50

#define push(value) if ((sp-stack) > MAX_STACK-1) { printf("Error: Stack too full.\n"); return 1; } else { *sp++ = (value); }
#define pop(np)     if ((sp-stack) == 0) { printf("Error: Stack too empty.\n"); return 1; } else { *sp = 0; *(np) = *--sp; }

double stack[MAX_STACK];
double *sp = stack;

int main(int argc, char *argv[]) {
    double op1 = 0;
    double op2 = 0;
    double number = 0;

    for (int i = 1; i < argc; i++) {

        if (i == 1 && !strcmp("-h", argv[i])) {
            printf("%s", HELP);
            continue;
        } else {
            if ((number = atof(argv[i])) || (*argv[i] == '.' || *argv[i] == '0') || (strlen(argv[i]) >= 2 && (*argv[i] == '+' || *argv[i] == '-') && (*argv[i+1] == '.' || *argv[i+1] == '0'))) {
                push(number);
            } else if (!strcmp("+", argv[i]) || !strcmp("add", argv[i])) {
                pop(&op2); pop(&op1);
                push(op1 + op2);
            } else if (!strcmp("-", argv[i]) || !strcmp("sub", argv[i])) {
                pop(&op2); pop(&op1);
                push(op1 - op2);
            } else if (!strcmp("*", argv[i]) || !strcmp("mul", argv[i])) {
                pop(&op2); pop(&op1);
                push(op1 * op2);
            } else if (!strcmp("/", argv[i]) || !strcmp("div", argv[i])) {
                pop(&op2); pop(&op1);
                push(op1 / op2);
            } else {
                error(argv[i], "");
            }
        }
    }

    for (int i = 0; (sp-stack) > i; i++) {
        if (stack[i] - (int)stack[i] == 0.0) {
            printf("%i ", (int)stack[i]);
        } else {
            printf("%0.02f ", stack[i]);
        }
        
    }
}

/*
510: Write the program `expr`, which evaluates a reverse Polish expression from the
    command line, where each operator or operand is a separate argument.
*/