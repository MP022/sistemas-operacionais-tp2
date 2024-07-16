#ifndef FRAME_H
#define FRAME_H

#include <time.h>
#include "page.h"

typedef struct Frame{
    unsigned id;
    unsigned value;
    Page* page;
    long allocated_time;
} Frame;

#endif