#ifndef UTIL_H
#define UTIL_H

#include <time.h>
time_t current_time(){
    return time(0);
}

unsigned page_from_addr(unsigned addr, unsigned s){
    return addr >> s;
}
#endif