#include "table.h"
#include <stdlib.h>

void init_table(Table * table, unsigned page_size, unsigned physical_mem_size)
{
    table->pages = (Page *)malloc(physical_mem_size / page_size * sizeof(Page));
    table->frames = (unsigned *)malloc(physical_mem_size / page_size * sizeof(unsigned));
}