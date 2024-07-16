#ifndef TABLE_MULTILEVEL3
#define TABLE_MULTILEVEL3

#include "frame.h"
#include "table_multilevel2.h"
#include "util.h"


typedef struct TableMultilevel3
{
    TableMultilevel2 **tables;
    long size;
    int page_faults;
    char *policy;
    unsigned shift_addrs;
    unsigned shift_table;
    unsigned pages_read;
    unsigned pages_write;
} TableMultilevel3;

void init_table_multinivel3(TableMultilevel3 *table, long num_tables, long frames_amount, unsigned page_size, char * policy);

void process_address_multinivel3(TableMultilevel3 *table, Frame **frames, unsigned addr, char operation);

#endif