#include "../include/table.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Inicializa a tabela de páginas.
 * @param table Tabela de páginas.
 * @param num_pages Número de páginas.
 * @param page_size Tamanho da página.
 */

void init_table(Table *table, unsigned num_pages, unsigned page_size, char *policy)
{
    table->pages = (Page *)malloc(num_pages * sizeof(Page *));
    for (int i = 0; i < num_pages; i++)
    {
        table->pages[i] = (Page *)malloc(sizeof(Page));
        table->pages[i]->id = i;
        table->pages[i]->last_access = 0;
    }
    table->size = num_pages;
    table->policy = policy;
    table->page_faults = 0;
    table->shift = 0;
    table->pages_read = 0;
    table->pages_write = 0;

    unsigned shift = 0;

    /* Derivar o valor de s: */
    while (page_size > 1)
    {
        page_size = page_size >> 1;
        shift++;
    }
    table->shift = shift;
}

void process_address(Table *table, Frame **frames, unsigned addr, char *operation)
{
    if (addr == NULL || operation == NULL)
    {
        return;
    }
    unsigned page = page_from_addr(addr, table->shift);
    if (operation == 'W')
    {
        read(table, frames, addr, page);
        table->pages_read++;
    }
    else
    {
        write(table, frames, addr, page);
        table->pages_write++;
    }
}

int read(Table *table, Frame **frames, unsigned addr, unsigned pageIndex)
{
    if (pageIndex >= table->size)
    {
        // table->page_faults++;
        return 0;
    }
    Page *actual_page = table->pages[pageIndex];
    if(actual_page-> valid == 1){
        table->pages[pageIndex]->last_access = current_time();
        table->pages_read++;
        return;
    }
    table->page_faults++;
    return 0;
}

int write(Table *table, Frame **frames, unsigned addr, unsigned pageIndex)
{
    if (pageIndex >= table->size)
    {
        // table->page_faults++;
        return 0;
    }
    Page *actual_page = table->pages[pageIndex];
    if (actual_page->valid == 1)
    {
        actual_page->last_access = current_time();
        return 1;
    }
    Frame *frame = get_free_frame(frames, table->pages, table->size);
    if (frame->page != -1)
    {
        table->pages[frame->page]->frame = NULL;
        table->pages[frame->page]->valid = 0;
    }

    Page *page = table->pages[pageIndex];
    frame->page = pageIndex;
    page->frame = frame;
    page->last_access = current_time();
    page->valid = 1;

    return 0;
}