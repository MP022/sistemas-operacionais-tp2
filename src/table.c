#include "../include/table.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Inicializa a tabela de páginas.
 * @param table Tabela de páginas.
 * @param num_pages Número de páginas.
 * @param page_size Tamanho da página.
 */

void init_table(Table *table, long num_pages, unsigned page_size, unsigned frames_amount, char *policy)
{
    table->pages = (Page *)malloc(num_pages * sizeof(Page *));
    for (int i = 0; i < num_pages; i++)
    {
        table->pages[i] = (Page *)malloc(sizeof(Page));
        table->pages[i]->id = i;
        table->pages[i]->last_access = 0;
        table->pages[i]->reference = 0;
    }
    table->interaction_counter = 0;
    table->size = num_pages;
    table->page_faults = 0;
    table->shift = 0;
    table->frames_amount = frames_amount;
    table->pages_read = 0;
    table->pages_write = 0;
    table->second_chance_list = (List*)malloc(sizeof(List));
    table->policy = select_policy(policy);

    unsigned shift = 0;

    /* Derivar o valor de s: */
    while (page_size > 1)
    {
        page_size = page_size >> 1;
        shift++;
    }
    table->shift = shift;
}

void process_address(Table *table, Frame **frames, unsigned frames_amount, unsigned addr, char *operation)
{
    if (addr == NULL || operation == NULL)
    {
        return;
    }
    unsigned page = addr >> table->shift;

    if (operation == 'W')
    {
        read(table, frames, frames_amount, addr, page);
        table->pages_read++;
    }
    else
    {
        write(table, frames, frames_amount, addr, page);
        table->pages_write++;
    }
}
ReplacementPolicty select_policy(char *policy)
{
    if (string_equals(policy, "lru"))
    {
        return LRU;
    }
    if (string_equals(policy, "fifo"))
        return FIFO;

    printf("Invalid policy passed, %s", policy);
    exit(1);
}
int read(Table *table, Frame **frames, unsigned frames_amount, unsigned addr, unsigned pageIndex)
{

    Page *actual_page = table->pages[pageIndex];
    if (actual_page->valid == 1)
    {
        table->pages[pageIndex]->last_access = current_time(table);
        table->pages[pageIndex]->reference = 1;
        return;
    }
    table->page_faults++;
    return 0;
}

int write(Table *table, Frame **frames, unsigned frames_amount, unsigned addr, unsigned pageIndex)
{

    Page *actual_page = table->pages[pageIndex];
    if (actual_page->valid == 1)
    {
        actual_page->last_access = current_time(table);
        return 1;
    }
    Frame *frame = get_free_frame(frames, table);
    if (frame->page != -1)
    {
        table->pages[frame->page]->frame = NULL;
        table->pages[frame->page]->valid = 0;
    }

    Page *page = table->pages[pageIndex];
    frame->page = pageIndex;
    page->frame = frame;
    frame->allocated_time = current_time(table);
    page->last_access = current_time(table);
    page->valid = 1;
    page->reference = 1;
    return 0;
}

Frame *get_free_frame(Frame **frames, Table *table)
{
    Page **pages = table->pages;

    unsigned num_frames = table->frames_amount;
    Page *least_recently_used = NULL;
    Frame *oldest_allocated = NULL;
    Frame *frame = NULL;
    for (int i = 0; i < num_frames - 1; i++)
    {
        if (frames[i]->page == -1)
        {
            return frames[i];
        }
        Page *page = pages[frames[i]->page];
        if (least_recently_used==NULL|| least_recently_used->last_access > page->last_access)
        {
            least_recently_used = page;
        }
        if (oldest_allocated==NULL|| oldest_allocated->allocated_time > frames[i]->allocated_time)
        {
            oldest_allocated = frames[i];
        }
    }
    switch (table->policy){
    case LRU:
        return least_recently_used->frame;
    case FIFO:
        return oldest_allocated;
    case SECOND_CHANCE:

    default:

        return NULL;
    }
}