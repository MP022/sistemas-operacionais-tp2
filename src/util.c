#include "../include/util.h"
#include "../include/table.h"

#include <string.h>
long current_time(Table *table)
{
    return table->interaction_counter;
}

int string_equals(char *a, char * b){
    return strcmp(a,b)==0;
}