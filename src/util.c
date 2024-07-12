#include "../include/util.h"
#include "../include/table.h"

time_t current_time()
{
    return time(0);
}

unsigned page_from_addr(unsigned addr, unsigned s)
{
    return addr >> s;
}

Frame *get_free_frame(Frame **frames, Page **pages, unsigned num_frames){
    Page *least_recently_used = NULL;

    for (int i = 0; i < num_frames; i++)
    {
        if(frames[i]->page == -1){
            return frames[i];
        }
        Page * page = pages[frames[i]->page];
        if(least_recently_used == NULL){
            least_recently_used = frames[i];
            continue;
        }
        if(page->last_access < least_recently_used->last_access){
            least_recently_used = page;
        }
    }
    return least_recently_used;
}