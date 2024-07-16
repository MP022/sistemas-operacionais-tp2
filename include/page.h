#ifndef PAGE_H
#define PAGE_H

#include "time.h"


typedef struct Page
{
    unsigned valid;
    unsigned id;
    unsigned reference;
    long last_access;
    unsigned frame;
} Page;

#endif