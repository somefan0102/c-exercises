#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "input.h"
#include "nstring.h"

#define MAX_LINE 100
#define MAX_ELEMENTS 300

enum CalcCommand {
    NONE, NUMBER,
    VARIABLE, ASSIGNMENT,
    PLUS, MINUS, MULTIPLY, DIVIDE, MOD, POW,
    SIN, COS, TAN, EXP, SQRT, FLOOR, CEIL,
    TOP, DUPE, SWAP, CLEAR, POP, RECENT, OPP,
};

int getop(char str[]);
double opp(double x);
double mod(double m, double n);

void push(double value);
double pop(void);
double topp(void);
void clear(void);

double stack[MAX_ELEMENTS];
double variables[26];
int top = 0;
char letter;
float recent =  0.0;

int main(void) {
    char line[MAX_LINE];
    int command;
    double v1, v2;

    while (getline(line, MAX_LINE) > 0) {
        switch (command = getop(line)) {
            case NUMBER:
                push(atof(line));
                break;

            case VARIABLE:
                push(variables[letter-'a']);
                break;

            case ASSIGNMENT:
                printf("Variable \"%c\" is now %lf\n", letter, variables[letter-'a']);
                recent = variables[letter-'a'];
                break;

            case RECENT:
                push(recent);
                break;
                
            case PLUS:
                push(pop() + pop());
                break;

            case MULTIPLY:
                push(pop() * pop());
                break;

            case MINUS:
                v2 = pop();
                v1 = pop();
                push(v1 - v2);
                break;

            case DIVIDE:
                v2 = pop();
                v1 = pop();
                push(v1 / v2);
                break;

            case MOD:
                v2 = pop();
                v1 = pop();
                push(mod(v1, v2));
                break;

            case POW:
                v2 = pop();
                v1 = pop();
                push(pow(v1, v2));
                break;

            case SIN:
                push(sin(pop()));
                break;
    
            case COS:
                push(cos(pop()));
                break;

            case TAN:
                push(tan(pop()));
                break;

            case EXP:
                push(exp(pop()));
                break;

            case SQRT:
                push(sqrt(pop()));
                break;

            case FLOOR:
                push(floor(pop()));
                break;

            case CEIL:
                push(ceil(pop()));
                break;

            case OPP:
                push(opp(pop()));
                break;

            case TOP:
                printf("Top: %lf\n", topp());
                recent = topp();
                break;
            
            case DUPE:
                push(topp());
                break;

            case SWAP:
                v1 = pop();
                v2 = pop();
                push(v1);
                push(v2);
                break;
            
            case CLEAR:
                clear();
                break;
            
            case POP:
                pop();
                break;

            default:
                if (line[0] == '\0') {
                    for (int i = 0; i < top; i++) {
                        for (int i = 0; i < top; i++) {
                            if (stack[i] - (int)stack[i] == 0.0) {
                                printf("%i ", (int)stack[i]);
                            } else {
                                printf("%0.05f ", stack[i]);
                            }
                        }
                        printf("\n");
                    }
                } else {
                    printf("Error: (%s) Invalid command.\n", line);
                }
                break;
        }


    }

    return 0;
}

int getop(char str[]) {
    int i = 0;
    int found;

    while (isspace(str[i]) || str[i] == '+' || str[i] == '-') {
        i++;
    }

    if ((atof(str) == 0 && (str[i] == '0' || str[i] == '.')) || atof(str) != 0) {
        return NUMBER;
    }

    if (strlen(str) == 1) {
        switch (str[0]) {
            case '+': return PLUS;
            case '-': return MINUS;
            case '*': return MULTIPLY;
            case '/': return DIVIDE;
            case '%': return MOD;
            case '^': return POW;
            case '_': return RECENT;
            default:
                if (isalpha(str[0])) {
                    return VARIABLE;
                }
                break;
        }
    } else if (!strcmp(str, "sin")) {
        return SIN;
    } else if (!strcmp(str, "cos")) {
        return COS;
    } else if (!strcmp(str, "tan")) {
        return TAN;
    } else if (!strcmp(str, "exp")) {
        return EXP;
    } else if (!strcmp(str, "sqrt")) {
        return SQRT;
    } else if (!strcmp(str, "floor")) {
        return FLOOR;
    } else if (!strcmp(str, "ceil")) {
        return CEIL;
    } else if (!strcmp(str, "opp")) {
        return OPP;
    } else if (!strcmp(str, "top")) {
        return TOP;
    } else if (!strcmp(str, "dupe")) {
        return DUPE;
    } else if (!strcmp(str, "swap")) {
        return SWAP;
    } else if (!strcmp(str, "clear")) {
        return CLEAR;
    } else if (!strcmp(str, "pop")) {
        return POP;
    } else if ((found = strfind(str, '=')) >= 0) {
        double value;

        for (i = 0; isspace(str[i]); i++);

        if (isalpha(str[i])) {
            letter = tolower(str[i]);
        } else {
            return NONE;
        }

        i++;
        for (; isspace(str[i]); i++);

        if (str[i] != '=') {
            return NONE;
        }

        value = atof(str+found+1);
        variables[letter-'a'] = value;
        return ASSIGNMENT;
    }

    return NONE;
}

void push(double value) {
    if (top >= MAX_ELEMENTS) {
        printf("Error: Stack full.\n");
    } else {
        stack[top++] = value;
    }
}

double pop(void) {
    double popped;

    if (top <= 0) {
        printf("Error: Stack empty.\n");
        return 0;
    } else {
        popped = stack[--top];
        return popped;
    }
}

double topp(void) {
    return stack[top-1];
}

void clear(void) {
    while (top > 0) {
        stack[--top] = 0.0;
    }
}

double opp(double x) {
    return -x;
}

double mod(double x, double y) {
    int sign_x = (x < 0) ? 0 : 1;
    int sign_y = (y < 0) ? 0 : 1;
    int i = 0;

    if (x == 0 || y == 0) {
        return x;
    }

    if (sign_x && !sign_y) {
        while (x > 0 && i < 100) {
            x += y;
            i++;
        }
    } else if (!sign_x && sign_y) {
        while (x < 0 && i < 100) {
            x += y;
            i++;
        }
    } else {
        x = abs(x);
        y = abs(y);
        while (x >= y && i < 100) {
            x -= y;
            i++;
        }
        if (!sign_x && !sign_y) {
            x *= -1;
        }
    }

    if (i >= 100) {
        printf("Something failed.\n");
        return -999;
    }

    return x;
}

/*
403: Given the basic framework, it's straightforward to extend the calculator.
     Add the modulus (%) operator and provisions for negative numbers.
404: Add the commands to print the top elements of the stack without popping, to duplicate it, and to swap the top two elements.
     Add a command to clear the stack.
405: Add access to library functions like sin, exp, and pow.
406: Add commands for handling variables. (It's easy to provide twenty-six variables with single-letter names.)
     Add a variable for the most recently printed value.
410: An alternate organization uses getline to read an entire input line; this makes
     `getch` and `ungetch` unnecessary. Revise the calculator to use this approach.
411: Modify `getop` so that it doesn't need to use `ungetch`.
*/