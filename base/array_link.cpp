#include "stdafx.h"
#include <iostream>

typedef struct
{
    int data; //数据元素类型，自定义
    int next;
}ARR_LINK_NODE;

const int NODE_COUNT = 128;
ARR_LINK_NODE node[NODE_COUNT]; //存储空间
int freelist = 0;
int head = -1;

void init_array_link()
{
    //将数组元素串联到freelist中
    for (int i = 0; i < (NODE_COUNT - 1); i++)
    {
        node[i].next = i + 1;
    }
    node[NODE_COUNT - 1].next = -1;
    freelist = 0;
}

int insert_element(int data)
{
    if (freelist == -1)  //没有空元素位置了
    {
        return -1;
    }
    int new_elem = freelist;
    freelist = node[freelist].next;   //从freelist中删除第一个节点

    node[new_elem].data = data;
    node[new_elem].next = -1;
    if (head == -1)
    {
        head = new_elem;
    }
    else
    {
        node[new_elem].next = head;
        head = new_elem;
    }
    return new_elem;
}

void remove_element(int data)
{
    int prev = head;
    int cur = head;

    while (cur != -1)
    {
        if (node[cur].data == data)
        {
            if (cur == head)
            {
                head = node[cur].next;
            }
            else
            {
                node[prev].next = node[cur].next;
            }
            node[cur].next = freelist;//回收到freelist节点中
            freelist = cur;
            break;
        }
        prev = cur;
        cur = node[cur].next;
    }
}

void print_link(int head)
{
    int cur = head;

    while (cur != -1)
    {
        std::cout << node[cur].data << "   ";
        cur = node[cur].next;
    }

    std::cout << std::endl;
}

/*
init_array_link();
head = insert_element(5);
insert_element(8);
insert_element(12);
insert_element(21);
insert_element(15);
insert_element(60);
insert_element(55);
insert_element(34);
print_link(head);

remove_element(8);
remove_element(21);
remove_element(34);
print_link(head);
*/