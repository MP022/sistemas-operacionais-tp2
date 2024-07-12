#ifndef PAGE_H
#define PAGE_H

#include <time.h>

typedef struct Page
{
    unsigned valid;
    unsigned id;
    time_t last_access;
    Frame * frame;

} Page;

#endif