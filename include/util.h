#ifndef UTIL_H
#define UTIL_H

#include <time.h>
#include "table.h"
time_t current_time();

/**
 * Compare two strings an return if they are equal
 */
int string_equals(char *a, char *b);

unsigned page_from_addr(unsigned addr, unsigned s);

Frame * get_free_frame(Frame ** frames,Page** pages, unsigned num_frames);
#endif