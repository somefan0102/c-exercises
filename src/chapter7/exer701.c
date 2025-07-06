#include <stdio.h>
#include <ctype.h>
#include "nstring.h"

int main(int argc, char *argv[]) {
    int slash;
    char *name;
    int mode;

    if ((slash = strindex(argv[0], "/")) == -1) {
        if ((slash = strindex(argv[0], "\\")) == -1) {
            slash = 0;
        }
    }
    name = argv[0]+slash+1;

    if (!strncmp("lower", name, 5)) {
        mode = 0;
    } else if (!strncmp("upper", name, 5)) {
        mode = 1;
    } else {
        printf("Error: Unknown program name. Should be \"lower\" or \"upper\".\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        while (*argv[i]) {
            putchar((mode) ? toupper(*argv[i]) : tolower(*argv[i]));
            argv[i]++;
        }
        if (i < argc-1) {
            putchar(' ');
        }
    }

    return 0;
}

/*
701: Write a program that converts upper case to lower or lower case to upper,
     depending on the name it is invoked with, as found in `argv[0]`.
*/