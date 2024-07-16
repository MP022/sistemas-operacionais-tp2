#include "../include/table_multilevel3.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void init_table_multinivel3(TableMultilevel3 *table, long num_tables, long frames_amount, unsigned page_size, char *policy)
{
    table->tables = (TableMultilevel2 **)malloc(num_tables * sizeof(TableMultilevel2 *));
    for (int j = 0; j < num_tables; j++)
    {
        table->tables[j] = (TableMultilevel2 *)malloc(sizeof(TableMultilevel2));
        init_table_multinivel2(table->tables[j], sqrt(num_tables), frames_amount, page_size, policy);
    }
    table->size = num_tables;
    table->policy = policy;
    table->page_faults = 0;
    table->pages_read = 0;
    table->pages_write = 0;

    unsigned shift = 0;
    long sizeShift = num_tables;
    while (sizeShift > 1)
    {
        sizeShift = sizeShift >> 1;
        shift++;
    }
    table->shift_addrs = shift;

    shift = 0;
    sizeShift = num_tables * page_size;
    while (sizeShift > 1)
    {
        sizeShift = sizeShift >> 1;
        shift++;
    }
    table->shift_table = shift;

}

void process_address_multinivel3(TableMultilevel3 *table, Frame **frames, unsigned addr, char operation)
{
    if (addr == -1 || operation == '\0')
    {
        return;
    }
    unsigned tableIndex = addr >> table->shift_table;
    unsigned newAddr = addr << table->shift_addrs;
    newAddr = newAddr >> table->shift_addrs;

    // printf("%x\n%d: %x %d: %x\n", addr, table->shift_table, tableIndex, table->shift_addrs, newAddr);

    int aux_page_faults = table->tables[tableIndex]->page_faults;
    process_address_multinivel2(table->tables[tableIndex], frames, newAddr, operation);
    if (operation == 'W')
    {
        table->pages_read++;
    }
    else
    {
        table->pages_write++;
    }

    table->page_faults += table->tables[tableIndex]->page_faults - aux_page_faults;
}