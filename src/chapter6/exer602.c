#include <stdio.h>
#include <ctype.h>
#include "input.h"
#include "nstring.h"
#include "tree.h"

#define MAX_LINE 1000
#define MAX_WORD 500
#define MAX_WORDS 500
#define DEFAULT_SIG 6
#define isvarch(x) (isalnum(x) || x == '_')

void getWord(void);
void ungetWord(void);
void putTree(TreeNode *treenode);
void match(char *words[], int significance);
int is_reserved(char *string);

char line[MAX_LINE];
char word[MAX_WORD];
int scan = 0;
int last_scan = 0;

char *words[MAX_WORDS];
int words_i = 0;

// Only gets the very basic integral and one-pointer variable name declarations; no initializations.
// [int|double|char|float|long|double|short] (*)x(, ...)

void ungetWord(void) {
    scan = last_scan;
}

void getWord(void) {
    int ch, special_ch = 0, custom_ch = 0;
    last_scan = scan;
    char *wp = word;

    while (isspace(line[scan]) || line[scan] == '\\') {
        scan++;
    }

    if (line[scan] == '\"' || line[scan] == '\'') {
        ch = line[scan];
        scan++;
        while (!(line[scan] == ch && line[scan-1] != '\\') && scan < MAX_LINE) {
            scan++;
        }
        scan++;
        special_ch = 1;
    } else if (line[scan] == '/' && line[scan+1] == '/') {
        while (line[scan] != '\n' && scan < MAX_LINE) {
            scan++;
        }
        special_ch = 1;
    } else if (line[scan] == '/' && line[scan+1] == '*') {
        scan += 3;
        while (!(line[scan] == '/' && line[scan-1] == '*') && scan < MAX_LINE) {
            scan++;
        }
        scan++;
        special_ch = 1;
    } else if (line[scan] == '#') {
        if (!strncmp("#define", line+scan, 7)) {
            while (line[scan] != '(' && scan < MAX_LINE) {
                scan++;
            }
            while (line[scan] != ')' && scan < MAX_LINE) {
                scan++;
            }
            scan++;
        } else {
            while (line[scan] != '\n' && scan < MAX_LINE) {
                scan++;
            }
        }
        special_ch = 1;
    } else if (!isvarch(line[scan])) {
        special_ch = 1;
        custom_ch = 1;
    }

    if (special_ch) {
        if (scan >= MAX_LINE) {
            wp[0] = '\0';
        } else {
            wp[0] = (custom_ch) ? line[scan] : '~';
            wp[1] = '\0';
            if (custom_ch) {
                scan++;
            }
        }
        return;
    }

    while (isvarch(line[scan])) {
        *wp = line[scan];
        scan++, wp++;
    }
    *wp = '\0';
}

int is_reserved(char *string) {
    static char *words[] = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern", "float",
        "for", "goto", "if", "int", "long", "register",
        "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while", NULL,
    };

    for (int i = 0; words[i]; i++) {
        if (!strcmp(words[i], string)) {
            return 1;
        }
    }
    return 0;
}

// [int|double|char|float|long|short] (*)x(, ...)
int main(int argc, char *argv[]) {
    TreeNode *root = NULL;
    int significance = DEFAULT_SIG;

    if (argc >= 2) {
        if ((significance = atoi(argv[1])) == 0) {
            significance = DEFAULT_SIG;
        }
    }
    printf("%i", significance);

    getinput(line, MAX_LINE, EOF);

    do {
        getWord();
        if (isalpha(word[0]) && !is_reserved(word)) {
            root = addTree(root, word, 0);
        }
    } while (*word);

    putTree(root);
    words[words_i++] = NULL;
    match(words, significance);
}

void putTree(TreeNode *treenode) {
    if (treenode) {
        putTree(treenode->left);
        if (words_i < MAX_WORDS) {
            words[words_i++] = treenode->word;
        }
        putTree(treenode->right);
    }
}

void match(char *words[], int significance) {
    int first = 1;
    int nline = 0;

    for (int i = 1; words[i]; i++) {
        if (!strncmp(words[i], words[i-1], significance)) {
            nline = 0;
            if (first) {
                printf("%s ", words[i-1]);
            }
            printf("%s ", words[i]);
            first = 0;
        } else {
            if (nline == 0 && first == 0) {
                putchar('\n');
                nline = 1;
            }
            first = 1;
        }
    }
}

/*
602: Write a program that reads a C program and prints in alphabetical order each group
     of variable names that are identical in the first 6 characters, but different somewhere thereafter.
     Don't count words within strings and comments. Make 6 a parameter that can be set from the command line.
*/