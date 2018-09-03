#include "stdafx.h"
#include <iostream>

/*
LINK_NODE *head = create_list(6);
print_list(head);
LINK_NODE *rhead = reverse_link(head);
print_list(rhead);
*/

typedef struct LINK_NODE
{
    int data;
    LINK_NODE *next;
}LINK_NODE;

LINK_NODE *create_list(int count)
{
    LINK_NODE *head = new LINK_NODE;
    head->data = 1;
    head->next = nullptr;
    LINK_NODE *cur = head;
    for (int i = 2; i <= count; i++)
    {
        LINK_NODE *node = new LINK_NODE;
        node->data = i;
        node->next = nullptr;
        cur->next = node;
        cur = node;
    }

    return head;
}

void print_list(LINK_NODE *head)
{
    LINK_NODE *cur = head;
    while (cur != nullptr)
    {
        std::cout << cur->data << "   ";
        cur = cur->next;
    }

    std::cout << std::endl;
}

LINK_NODE *reverse_link(LINK_NODE *head)
{
    LINK_NODE *newHead;

    if ((head == nullptr) || (head->next == nullptr))
        return head;

    newHead = reverse_link(head->next); /*递归逆转子链表部分*/
    head->next->next = head; /*回朔部分*/
    head->next = nullptr;

    return newHead;
}
