#include <stdio.h>
#include <ctype.h>
#include "input.h"
#include "nstring.h"

#define MAX_KEYS (sizeof key_counts / sizeof key_counts[0])
#define MAX_LINE 1000
#define MAX_WORD 500
#define isvarch(x) (isalnum(x) || x == '_')

struct KeyCounter {
    char *word;
    int count;
};

struct KeyCounter key_counts[] = {
    {"auto", 0}, {"break", 0}, {"case", 0}, {"char", 0}, {"const", 0}, {"continue", 0},
    {"default", 0}, {"do", 0}, {"double", 0}, {"else", 0}, {"enum", 0}, {"extern", 0}, {"float", 0},
    {"for", 0}, {"goto", 0}, {"if", 0}, {"int", 0}, {"long", 0}, {"register", 0},
    {"return", 0}, {"short", 0}, {"signed", 0}, {"sizeof", 0}, {"static", 0},
    {"struct", 0}, {"switch", 0}, {"typedef", 0}, {"union", 0},
    {"unsigned", 0}, {"void", 0}, {"volatile", 0}, {"while", 0},
};

void getWord(void);
int keyContains(char *target, struct KeyCounter key_counts[], int max);

char line[MAX_LINE];
char word[MAX_WORD];

int scan = 0;

int keyContains(char *target, struct KeyCounter key_counts[], int max) {
    for (int i = 0; i < max; i++) {
        if (!strcmp(key_counts[i].word, target)) {
            return i;
        }
    }
    return -1;
}

void getWord(void) {
    int ch, special_ch = 0, custom_ch = 0;
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

int main(void) {
    int found;
    getinput(line, MAX_LINE, EOF);
    printf("%s", line);

    do {
        getWord();
        // printf("[%s]\n", word);
        found = keyContains(word, key_counts, MAX_KEYS);
        if (found >= 0) {
            key_counts[found].count++;
        }
    } while (*word);

    for (int i = 0; i < MAX_KEYS; i++) {
        if (key_counts[i].count > 0) {
            printf("%2i %s\n", key_counts[i].count, key_counts[i].word);
        }
    }

    return 0;
}

/*
601: Our version of `getword` does not properly handle underscores, string constants,
     comments, or preprocessor control lines. Write a better version.
*/