#ifndef PAGE_H
#define PAGE_H

#include "time.h"
#include "frame.h"


typedef struct Page
{
    unsigned valid;
    unsigned id;
    long last_access;
    Frame * frame;
} Page;

#endif