#include <stdio.h>
#include <ctype.h>
#include "input.h"
#include "nstring.h"
#include "tree.h"

#define MAX_LINE 1000
#define MAX_WORD 500

void getWord(void);
int getMaxCount(TreeNode *treenode);
void treePrint(TreeNode *treenode, int size);

char line[MAX_LINE];
char word[MAX_WORD];

int scan = 0;

void getWord(void) {
    char *wp = word;

    while (isspace(line[scan])) {
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
        if (isalpha(word[0])) {
            strlower(word);
            root = addTree(root, word, 0);
        }
    } while (*word);

    for (int max = getMaxCount(root); max >= 0; max--) {
        treePrint(root, max);
    }

    return 0;
}

void treePrint(TreeNode *treenode, int size) {
    if (!treenode) {
        return;
    }

    treePrint(treenode->left, size);
    if (size == treenode->count) {
        printf("%2i %s\n", treenode->count, treenode->word);
    }
    treePrint(treenode->right, size);
}

int getMaxCount(TreeNode *treenode) {
    int count = 0;

    if (!treenode) {
        return 0;
    }

    count = treenode->count;

    if (count < getMaxCount(treenode->left)) {
        count = treenode->left->count;
    } else if (count < getMaxCount(treenode->right)) {
        count = treenode->right->count;
    }

    return count;
}

/*
604: Write a program that prints the distinct words in its input sorted into decreasing
     order of frequency of occurrence. Precede each word by its count.
*/