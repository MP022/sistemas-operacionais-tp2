#include "../include/table_multilevel.h"
#include <stdlib.h>
#include <stdio.h>


/**
* Inicializa a tabela de páginas.
* @param table Tabela de páginas.
* @param num_tables Número de tabelas.
* @param num_pages Número de páginas.
* @param page_size Tamanho da página.
*/
void init_table_multinivel(TableMultilevel *table, long num_tables, long num_pages, unsigned page_size, char *policy)
{
    table->tables = (Table *)malloc(num_tables * sizeof(Table *));
    for (int j = 0; j < num_tables; j++)
    {
        table->tables[j] = (Table *)malloc(sizeof(Table));
        init_table(table->tables[j], num_pages, page_size, policy);
    }
    table->size = num_tables;
    table->policy = policy;
    table->page_faults = 0;
    table->shift_addrs = 0;
    table->shift_table = 0;
    table->pages_read = 0;
    table->pages_write = 0;

    unsigned shift = 0;
    long sizeShift = num_pages + page_size;
    while (sizeShift > 1)
    {
        sizeShift = sizeShift >> 1;
        shift++;
    }
    table->shift_table = shift;

    shift = 0;
    while (num_pages > 1)
    {
        num_pages = num_pages >> 1;
        shift++;
    }
    table->shift_addrs = shift;

}

void process_address_multinivel(TableMultilevel *tables, Frame **frames, unsigned frame_amount, unsigned addr, char *operation)
{
    if (addr == NULL || operation == NULL)
    {
        return;
    }
    unsigned table = addr >> tables->shift_table;

    int aux_page_faults = tables->tables[table]->page_faults;
    process_address(tables->tables[table], frames, frame_amount, table, operation);
    
    if (operation == 'W')
    {
        tables->pages_read++;
    }
    else
    {
        tables->pages_write++;
    }

    tables->page_faults += aux_page_faults - tables->tables[table]->page_faults;
}