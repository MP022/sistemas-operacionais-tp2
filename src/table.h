#ifndef TABLE_H
#define TABLE_H

#include "page.h"

typedef struct Table
{
    Page **pages;
    unsigned * frames;
    int size;
    int page_faults;
} Table;

void init_table(Table * table, unsigned page_size, unsigned physical_mem_size);

int read(Table * table, unsigned addr, unsigned page);
int write(Table * table, unsigned addr, unsigned page);
#endif