#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

BSTNode *bstInsert(BSTNode *root, Student *student)
{
    if (root == NULL)
    {
        BSTNode *new_node = malloc(sizeof(BSTNode));

        if (new_node == NULL)
        {
            return NULL;
        }

        new_node->student = student;
        new_node->left = NULL;
        new_node->right = NULL;

        return new_node;
    }

    if (strcmp(student->name, root->student->name) <= 0)
    {
        root->left = bstInsert(root->left, student);
    }
    else
    {
        root->right = bstInsert(root->right, student);
    }

    return root;
}

void inorder(BSTNode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printStudent(root->student);
        inorder(root->right);
    }
}

void preorder(BSTNode *root)
{
    if (root != NULL)
    {
        printStudent(root->student);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(BSTNode *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printStudent(root->student);
    }
}

void cleanup(BSTNode *root)
{
    if (root != NULL)
    {
        cleanup(root->left);
        cleanup(root->right);
        free(root);
    }
}