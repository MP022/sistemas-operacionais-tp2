#ifndef UTIL_H
#define UTIL_H

#include <time.h>
#include "table.h"
time_t current_time();




unsigned page_from_addr(unsigned addr, unsigned s);

Frame * get_free_frame(Frame ** frames,Page** pages, unsigned num_frames);
#endif