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
    unsigned shift_addr;
    unsigned pages_read;
    unsigned frames_amount;
    unsigned pages_write;
    ReplacementPolicty policy;
    long interaction_counter;
} TableInverted;

void init_table_inverted(TableInverted *table, long frames_amount, unsigned page_size, char * policy);

void process_address_inverted(TableInverted *table, Frame **frames, unsigned addr, char operation);

int read_inverted(TableInverted *table, Frame **frames, unsigned page);
int write_inverted(TableInverted *table, Frame **frames, unsigned page);
Frame *get_page_frame(Frame **frames, TableInverted * table, unsigned pageIndex);

#endif