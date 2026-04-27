#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *insert(Node *head, int value);
Node *reverse(Node *head);
Node *duplicate_list(Node *head);
void add_lists(Node *list1, Node *list2);

// provided for you
void free_list(Node *head);
void print_list(Node *head);

#endif