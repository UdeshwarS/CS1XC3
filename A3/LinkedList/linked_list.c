#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

void print_list(Node *head)
{
    Node *curr = head;
    while (curr != NULL)
    {
        printf("%d", curr->value);
        if (curr->next != NULL)
        {
            printf(" -> ");
        }
        curr = curr->next;
    }
    printf(" -> NULL\n");
}

void free_list(Node *head)
{
    Node *curr = head;
    while (curr != NULL)
    {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
}

Node *insert(Node *head, int value)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        return head;
    }

    new_node->value = value;
    new_node->next = head;

    return new_node;
}

Node *reverse(Node *head)
{
    Node *prev = NULL;
    Node *curr = head;
    Node *next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

Node *duplicate_list(Node *head)
{
    Node *copy_head = NULL;
    Node *copy_tail = NULL;
    Node *curr = head;

    while (curr != NULL)
    {
        Node *new_node = malloc(sizeof(Node));

        if (new_node == NULL)
        {
            free_list(copy_head);
            return NULL;
        }

        new_node->value = curr->value;
        new_node->next = NULL;

        if (copy_head == NULL)
        {
            copy_head = new_node;
            copy_tail = new_node;
        }
        else
        {
            copy_tail->next = new_node;
            copy_tail = new_node;
        }

        curr = curr->next;
    }

    return copy_head;
}

void add_lists(Node *list1, Node *list2)
{
    Node *p1 = list1;
    Node *p2 = list2;

    while (p1 != NULL && p2 != NULL)
    {
        p1->value = p1->value + p2->value;
        p1 = p1->next;
        p2 = p2->next;
    }
}