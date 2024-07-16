#include "table_inverted.h"
#include <stdlib.h>
#include <stdio.h>


void init_table_inverted(TableInverted *table, long frames_amount, unsigned page_size, char *policy)
{
    table->pages = (Page **)malloc(frames_amount * sizeof(Page *));
    for (int i = 0; i < frames_amount; i++)
    {
        table->pages[i] = (Page *)malloc(sizeof(Page));
        table->pages[i]->id = -1;
        table->pages[i]->valid = 0;
        table->pages[i]->last_access = 0;
    }
    table->page_faults = 0;
    table->shift = 0;
    table->frames_amount = frames_amount;
    table->pages_read = 0;
    table->pages_write = 0;
    table->policy = select_policy(policy);
    
    unsigned shift = 0;
    long sizeShift = page_size;
    while (sizeShift > 1)
    {
        sizeShift = sizeShift >> 1;
        shift++;
    }
    table->shift = shift;

    shift = 0;
    sizeShift = frames_amount * page_size;
    while (sizeShift > 1)
    {
        sizeShift = sizeShift >> 1;
        shift++;
    }
    table->shift_addr = 32 - shift;
}

void process_address_inverted(TableInverted *table, Frame **frames, unsigned addr, char operation)
{
}
