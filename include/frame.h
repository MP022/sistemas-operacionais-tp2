#ifndef FRAME_H
#define FRAME_H

#include <time.h>
#include "page.h"

typedef struct Frame{
    unsigned id;
    unsigned value;
    Page* page;
    unsigned page;
    short reference;
    long allocated_time;
} Frame;

#endif