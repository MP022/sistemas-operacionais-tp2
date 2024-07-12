#include "table.h"
#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "frame.h"
/**
 * Inicializa a tabela de páginas.
 * @param table Tabela de páginas.
 * @param num_pages Número de páginas.
 * @param page_size Tamanho da página.
 */

void init_table(Table * table, unsigned num_pages, unsigned page_size)
{
    table->pages = (Page *)malloc(num_pages * sizeof(Page*));
    for(int i = 0; i < num_pages; i++)
    {
        table->pages[i] = (Page *)malloc(sizeof(Page));
        table->pages[i]->id = i;
        table->pages[i]->last_access = 0;
    }
    table->size = num_pages;
    table->page_faults = 0;
}

int read(Table *table, Frame **frames, unsigned addr, unsigned page)
{
    if (page > table->size)
    {
        table->page_faults++;
        return 0;
    }
    for(int i = 0; i < table->size; i++)
    {
        if(table->pages[i]->id  == page)
        {
            table->pages[i]->last_access = current_time();
            return 1;
        }
    }
    return 0;
}

int write(Table * table, Frame ** frame,unsigned addr, unsigned pageIndex)
{
    if (pageIndex > table->size)
    {
        table->page_faults++;
        return 0;
    }
    // Frame * frame = get_free_frame(frame, table->size);
    
    // if(frame-> page!=NULL){
    //     table->pages[frame->page->id]->frame = NULL;
    //     table->pages[frame->page->id]->valid = 0;
    // }

    // Page *page = table->pages[pageIndex];
    // frame->page = page;
    // page->frame = frame;
    // page->valid = 1;
    
    return 0;
}