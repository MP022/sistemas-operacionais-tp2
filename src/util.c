#include "../include/util.h"
#include "../include/table.h"

#include <string.h>
time_t current_time()
{
    return time(0);
}

int string_equals(char *a, char * b){
    return strcmp(a,b)!=0;
}