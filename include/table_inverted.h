#ifndef TABLE_INVERTED
#define TABLE_INVERTED

#include "frame.h"
#include "page.h"
#include "util.h"


typedef struct TableInverted
{
    Page **pages;
    int page_faults;
    unsigned shift;
    unsigned pages_read;
    unsigned frames_amount;
    unsigned pages_write;
    ReplacementPolicty policy;
} TableInverted;

void init_table_inverted(TableInverted *table, long num_pages, unsigned page_size, char * policy);

void process_address_inverted(TableInverted *table, Frame **frames, unsigned addr, char operation);

#endif