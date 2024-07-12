#include "util.h"

time_t current_time()
{
    return time(0);
}

unsigned page_from_addr(unsigned addr, unsigned s)
{
    return addr >> s;
}

Frame *get_free_frame(Frame **frames, unsigned num_frames){
    Frame *least_recently_used = NULL;
    for (int i = 0; i < num_frames; i++)
    {
        // if(frames[i]->page == NULL){
        //     return frames[i];
        // }
        // if(least_recently_used == NULL){
        //     least_recently_used = frames[i];
        //     continue;
        // }
        // if(frames[i]->page->last_access < least_recently_used->page->last_access){
        //     least_recently_used = frames[i];
        // }
    }
    return NULL;
}