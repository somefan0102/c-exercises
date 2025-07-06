#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "nstring.h"
#include "tree.h"

TreeNode *talloc(void) {
    TreeNode *room = (TreeNode *)malloc(sizeof(TreeNode));
    assert(room);
    return room;
}

void tfree(TreeNode *treenode) {
    if (treenode->left) {
        tfree(treenode->left);
    } else if (treenode->right) {
        tfree(treenode->right);
    }
    free(treenode->word);
    free(treenode->class);
    free(treenode);
}

TreeNode *addTree(TreeNode *treenode, char *word, int class) {
    int match;

    if (treenode == NULL) {
        treenode = talloc();
        treenode->word = (char *)malloc(strlen(word)+1*sizeof(char));
        strcpy(treenode->word, word);
        treenode->class = (int *)malloc(MAX_CLASSES*sizeof(int));
        treenode->count = 1;
        treenode->class[treenode->count-1] = class;
        treenode->class[treenode->count] = '\0';
        treenode->left = NULL;
        treenode->right = NULL;
        return treenode;
    } else if ((match = strcmp(word, treenode->word)) > 0) {
        treenode->right = addTree(treenode->right, word, class);
    } else if (match < 0) {
        treenode->left = addTree(treenode->left, word, class);
    } else {
        treenode->count++;
        if (treenode->count-1 < MAX_CLASSES) {
            treenode->class[treenode->count-1] = class;
            treenode->class[treenode->count] = '\0';
        }
    }

    return treenode;
}