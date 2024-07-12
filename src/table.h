#ifndef TABLE_H
#define TABLE_H

#include "page.h"

typedef struct Table
{
    Page *pages;
    unsigned * frames;
} Table;

void init_table(const Table * table, unsigned page_size, unsigned physical_mem_size);


#endif