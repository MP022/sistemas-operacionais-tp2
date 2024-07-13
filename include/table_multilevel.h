#ifndef TABLE_MULTILEVEL
#define TABLE_MULTILEVEL

#include "frame.h"
#include "page.h"
#include "util.h"


typedef struct TableMultilevel
{
    Table **tables;
    long size;
    int page_faults;
    char *policy;
    unsigned shift_addrs;
    unsigned shift_table;
    unsigned pages_read;
    unsigned pages_write;
} TableMultilevel;

void init_table_multinivel(TableMultilevel *table, long num_tables, long num_pages, unsigned page_size, char * policy);

void process_address_multinivel(TableMultilevel *table, Frame **frames, unsigned frame_amount, unsigned addr, char *operation);

#endif