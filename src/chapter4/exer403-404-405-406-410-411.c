#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "input.h"
#include "nstring.h"

#define MAXLINE 100

enum Type {
    NONE, NUMBER,
    VARIABLE, ASSIGNMENT,                    // Variable handling
    PLUS, MINUS, MULTIPLY, DIVIDE, MOD, POW, // Binary operators
    SIN, COS, TAN, EXP, SQRT, FLOOR, CEIL,   // Unary operators
    TOP, DUPE, SWAP, CLEAR, POP, RECENT      // Commands
};

// Processes the next `str[]` to type.
int getop(char str[]);

// Modulus arithmetic for doubles.
double mod(double m, double n);

extern double stack[];
double variables[26] = {0};
double recent = 0.0;
char letter;

int main(void) {
    char line[MAXLINE];
    int t;
    double v1, v2;

    while (getline(line, MAXLINE) > 0) {
        switch (t = getop(line)) {
            case NUMBER:
                push(atof(line));
                break;
            
            case VARIABLE:
                push(variables[letter-'a']);
                break;
            
            case ASSIGNMENT:
                break;
            
            case PLUS:
                push(pop() + pop());

            case MULTIPLY:
                push(pop() * pop());

            case MINUS:
                v2 = pop();
                v1 = pop();
                push(v1 - v2);

            case DIVIDE:
                v2 = pop();
                v1 = pop();
                push(v1 / v2);

            case MOD:
                v2 = pop();
                v1 = pop();
                push(mod(v1, v2));

            case POW:
                v2 = pop();
                v1 = pop();
                push(pow(v1, v2));

            case SIN:
                push(sin(v1));
                break;
    
            case COS:
                push(cos(v1));
                break;

            case TAN:
                push(tan(v1));
                break;

            case EXP:
                push(exp(v1));
                break;

            case SQRT:
                push(sqrt(v1));
                break;

            case FLOOR:
                push(floor(v1));
                break;

            case CEIL:
                push(ceil(v1));
                break;

            case TOP:
                printf("Top: %lf\n", top());
                recent = top();
                break;
            
            case DUPE:
                push(top());
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
                
            case RECENT:
                push(recent);
                break;
            
            case POP:
                pop();
                break;

            default:
                if (line[0] == '\0') {
                    for (int i = 0; i < topp(); i++) {
                        printf("%lf ", stack[i]);
                    }
                    printf("\n");
                } else {
                    printf("Error: (%s) Invalid command.\n", line);
                }
                break;
        }
    }
}

int getop(char str[]) {
    int i = 0;

    while (isspace(str[i]) || str[i] == '+' || str[i] == '-') {
        i++;
    }

    if (atof(str) == 0) {
        if (str[i] == '0' || str[i] == '.') {
            return NUMBER;
        }
    } else {
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
        }
    } else if (streq(str, "sin")) {
        return SIN;
    } else if (streq(str, "cos")) {
        return COS;
    } else if (streq(str, "tan")) {
        return TAN;
    } else if (streq(str, "exp")) {
        return EXP;
    } else if (streq(str, "sqrt")) {
        return SQRT;
    } else if (streq(str, "floor")) {
        return FLOOR;
    } else if (streq(str, "ceil")) {
        return CEIL;
    } else if (streq(str, "top")) {
        return TOP;
    } else if (streq(str, "dupe")) {
        return DUPE;
    } else if (streq(str, "swap")) {
        return SWAP;
    } else if (streq(str, "clear")) {
        return CLEAR;
    } else if (streq(str, "pop")) {
        return POP;
    } else if (strch(str, '=') >= 0) {
        char valuestr[MAXLINE];
        double value;
        int i;

        for (i = 0; isspace(str[i]); i++);

        if (isalpha(str[i])) {
            letter = str[i];
            if (isupper(letter)) {
                letter += ('a'-'A');
            }
        } else {
            return NONE;
        }

        do {
            i++;
            if (!isspace(str[i]) && str[i] != '=') {
                return NONE;
            }
        } while (i < strch(str, '='));

        i++;
        for (int j = 0; str[i] != '\0'; i++, j++) {
            valuestr[j] = str[i];
        }
    
        value = atof(valuestr);
        variables[letter-'a'] = value;
        printf("Variable \"%c\" is now %lf\n", letter, value);
        recent = value;

        return ASSIGNMENT;
    }
    
    return NONE;
}

double mod(double x, double y) {
    double r = (y > 0) ? y : -y;
    int sign = 1;
    int off = 1;
    int i;

    if (x == 0 || y == 0) {
        return x;
    } else if (x < 0) {
        sign = -1;
        off = 0;
    }

    for (i = 0; r*i >= x; i += sign);

    return x-r*(i+off);
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