#ifndef TREE_H
#define TREE_H

#define MAX_CLASSES 200

typedef struct TreeNode TreeNode;

struct TreeNode {
    char *word;
    int count;
    int *class;
    TreeNode *left;
    TreeNode *right;
};

// Adds a new node with `word` and `class` and returns it.
TreeNode *addTree(TreeNode *treenode, char *word, int class);

// Allocates and returns space for a tree node.
TreeNode *talloc(void);

// Trees a tree node.
void tfree(TreeNode *treenode);

#endif