#ifndef FRAME_H
#define FRAME_H

#include <time.h>

typedef struct Frame{
    unsigned value;
    unsigned page;
    time_t allocated_time;
} Frame;

#endif