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
    if (addr == -1 || operation == '\0')
    {
        return;
    }

    unsigned pageId = addr >> table->shift_addr;
    pageId = pageId << table->shift;
    pageId = pageId >> table->shift;

    if (operation == 'W')
    {
        read_inverted(table, frames, pageId);
        table->pages_read++;
    }
    else
    {
        write_inverted(table, frames, pageId);
        table->pages_write++;
    }
}

int read_inverted(TableInverted *table, Frame **frames, unsigned pageId)
{
    Frame *frame = get_page_frame(frames, table, pageId);
    if (table->pages[frame->id]->valid == 1)
    {
        table->pages[frame->id]->last_access = current_time(table);
        frames[frame->id]->reference = 1;
        return 1;
    }
    table->page_faults++;
    return 0;
}

int write_inverted(TableInverted *table, Frame **frames, unsigned pageId)
{
    Frame *frame = get_page_frame(frames, table, pageId);
    if (table->pages[frame->id]->valid == 1)
    {
        frame->page->last_access = current_time(table);
        return 1;
    }
    
    table->page_faults++;
    table->pages[frame->id]->id = pageId;
    frames[frame->id]->page = table->pages[frame->id];
    table->pages[frame->id]->frame = frames[frame->id]->id;
    frames[frame->id]->reference = 1;
    frames[frame->id]->allocated_time = current_time(table);
    table->pages[frame->id]->last_access = current_time(table);
    table->pages[frame->id]->valid = 1;
    return 0;
}

Frame *get_page_frame(Frame **frames, TableInverted *table, unsigned pageId)
{
    unsigned num_frames = table->frames_amount;
    Page *least_recently_used = NULL;
    Frame *oldest_allocated = NULL;
    for (int i = 0; i < num_frames ; i++)
    {
        Page * page = table->pages[i];
        if (page->id == -1)
        {
            return frames[i];
        }
        if (page->id == pageId)
        {
            return frames[i];
        }
        
        if (least_recently_used==NULL|| least_recently_used->last_access > page->last_access)
        {
            least_recently_used = page;
        }
        if (oldest_allocated==NULL|| oldest_allocated->allocated_time > frames[page->frame]->allocated_time)
        {
            oldest_allocated = frames[page->frame];
        }
    }

    switch (table->policy){
    case LRU:
        frames[least_recently_used->frame]->page->valid = 0;
        return frames[least_recently_used->frame];
    case FIFO:
        oldest_allocated->page->valid = 0;
        return oldest_allocated;
    case SECOND_CHANCE:
        for(int i = 0; i < num_frames; i++){
            Frame *frame = frames[i];
            if(frame->reference == 0){
                frame->page->valid = 0;
                return frame;
            }
            frame->reference = 0;
        }
    case RANDOM:
        int i = rand() % num_frames;
        frames[i]->page->valid = 0;
        return frames[i];
    default:

        return NULL;
    }
}
