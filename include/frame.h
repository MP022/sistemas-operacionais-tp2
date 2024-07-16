#ifndef FRAME_H
#define FRAME_H

#include <time.h>

typedef struct Frame{
    unsigned value;
    unsigned page;
    short reference;
    long allocated_time;
} Frame;

#endif