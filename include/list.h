#ifndef LIST_H
#define LIST_H

#include "page.h"
typedef struct PageNode{
    Page * page;
    PageNode * next;
}PageNode;

typedef struct List{
    PageNode * head;
    PageNode * tail;
    int size;
} List;

void init_list(List * list);
void insert_node(List * list, Page * page);

PageNode * remove_unreferenced(List*list);
#endif