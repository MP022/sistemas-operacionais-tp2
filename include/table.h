#ifndef TABLE_H
#define TABLE_H

#include "frame.h"
#include "page.h"
#include "util.h"

typedef enum ReplacementPolicty
{
    FIFO,
    SECOND_CHANCE,
    LRU,
    RANDOM
} ReplacementPolicty;

typedef struct Table
{
    Page **pages;
    long size;
    int page_faults;
    unsigned shift;
    unsigned pages_read;
    unsigned frames_amount;
    unsigned pages_write;
    ReplacementPolicty policy;
    long interaction_counter;
} Table;

ReplacementPolicty select_policy(char * policy);

void init_table(Table *table, long num_pages, unsigned frames_amount, unsigned page_size, char *policy);

void process_address(Table *table, Frame **frames, unsigned addr, char operation);

int read(Table *table, Frame **frames, unsigned page);
int write(Table *table, Frame **frames, unsigned page);
Frame *get_free_frame(Frame **frames, Table * table);

#endif