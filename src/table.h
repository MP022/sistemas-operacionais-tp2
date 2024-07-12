#ifndef TABLE_H
#define TABLE_H

#include "frame.h"
#include "page.h"
#include "util.h"


typedef struct Table
{
    Page **pages;
    int size;
    int page_faults;
    char *policy;
    unsigned shift;
    unsigned pages_read;
    unsigned pages_write;
} Table;

void init_table(Table *table, unsigned num_pages, unsigned page_size, char * policy);

void process_address(Table *table, Frame **frames, unsigned addr, char *operation);

int read(Table * table,Frame ** frames, unsigned addr, unsigned page);
int write(Table * table, Frame ** frames, unsigned addr, unsigned page);
#endif