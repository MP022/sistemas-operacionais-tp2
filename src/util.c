#include "../include/util.h"
#include "../include/table.h"

time_t current_time()
{
    return time(0);
}

unsigned page_from_addr(unsigned addr, unsigned s)
{
    return ;
}

Frame *get_free_frame(Frame **frames, Page **pages, unsigned num_frames){
    Page *least_recently_used = NULL;


    Frame *frame = NULL;
    for (int i = 0; i < num_frames-1; i++)
    {
        if(frames[i]->page == -1){
            frame = frames[i];
            break;
        }
        Page * page = pages[frames[i]->page];
        if(least_recently_used == NULL){
            least_recently_used = page;
            continue;
        }
        if(page->last_access < least_recently_used->last_access){
            least_recently_used = page;
        }
    }
    if(frame == NULL){
        frame = least_recently_used->frame;
    }
    frame->allocated_time = current_time();
    return frame;
}

Frame * fifo(Frame **frames, Page ** page, unsigned num_frames){

}