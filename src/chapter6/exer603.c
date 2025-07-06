#include <stdio.h>
#include <ctype.h>
#include "input.h"
#include "nstring.h"
#include "tree.h"

#define MAX_LINE 1000
#define MAX_WORD 500

void getWord(void);
void treePrint(TreeNode *treenode);

char line[MAX_LINE];
char word[MAX_WORD];

int scan = 0;
int nline = 1;

void getWord(void) {
    char *wp = word;

    while (isspace(line[scan])) {
        if (line[scan] == '\n') {
            nline++;
        }
        scan++;
    }

    if (!isalpha(line[scan])) {
        if (scan >= MAX_LINE) {
            wp[0] = '\0';
        } else {
            wp[0] = line[scan];
            wp[1] = '\0';
            scan++;
        }
        return;
    }

    while (isalpha(line[scan])) {
        *wp = line[scan];
        scan++, wp++;
    }
    *wp = '\0';
}

int main(int argc, char *argv[]) {
    TreeNode *root = NULL;
    getinput(line, MAX_LINE, EOF);

    do {
        getWord();
        if (isalpha(word[0]) && strlen(word) > 3) {
            strlower(word);
            root = addTree(root, word, nline);
        }
    } while (*word);

    treePrint(root);

    return 0;
}

void treePrint(TreeNode *treenode) {
    if (treenode) {
        treePrint(treenode->left);
        printf("%2i: ", treenode->count);
        printf("%-40s ", treenode->word);
        printf("@[");
        for (int i = 0; i < treenode->count; i++) {
            printf("%i", treenode->class[i]);
            if (i+1 < treenode->count) {
                putchar(',');
            }
        }
        printf("]\n");

        treePrint(treenode->right);
    }
}

/*
603: Write a cross-referencer that prints a list of all words in a document, and for
     each word, a list of the line numbers on which it occurs.
     Remove noise words like `the`, `and`, and so on.
*/