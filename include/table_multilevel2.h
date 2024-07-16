#ifndef TABLE_MULTILEVEL2
#define TABLE_MULTILEVEL2

#include "frame.h"
#include "page.h"
#include "util.h"


typedef struct TableMultilevel2
{
    Table **tables;
    long size;
    int page_faults;
    char *policy;
    unsigned shift_addrs;
    unsigned shift_table;
    unsigned pages_read;
    unsigned pages_write;
} TableMultilevel2;

void init_table_multinivel2(TableMultilevel2 *table, long num_tables, long num_pages, unsigned page_size, char * policy);

void process_address_multinivel2(TableMultilevel2 *table, Frame **frames, unsigned addr, char operation);

#endif