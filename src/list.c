#include "list.h";
#include <stdlib.h>

void init_list(List *list){
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void insert_node(List * list,Page *page){
    PageNode * node = (Page *)malloc(sizeof(PageNode));
    node->page = page;
    list->size++;
    if(list->head == NULL){
        list->head = node;
        list->tail = node;
        return;
    }

    list->tail->next = node;
    list->tail = node;
}

PageNode * remove_unreferenced(List *list){
    PageNode * current = list->head;

    while(current->next!=NULL){
        if(current->page->reference ==1){
            current->page->reference = 0;
        }
        current = current->next;
    }
    if(current!=NULL){
        return current;
    }
};