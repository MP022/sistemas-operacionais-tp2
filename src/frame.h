#ifndef FRAME_H
#define FRAME_H

#include "page.h"
typedef struct Frame{
    Page* page;
    unsigned value;
} Frame;

#endif