#ifndef FRAME_H
#define FRAME_H

#include <time.h>

typedef struct Frame{
    unsigned value;
    unsigned page;
    long allocated_time;
} Frame;

#endif