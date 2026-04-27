#ifndef BST_H
#define BST_H

#include "student.h"

typedef struct BSTNode {
    Student *student;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode *bstInsert(BSTNode *root, Student *student);
void inorder(BSTNode *root);
void preorder(BSTNode *root);
void postorder(BSTNode *root);
void cleanup(BSTNode *root);

#endif