#include "table.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * Inicializa a tabela de páginas.
 * @param table Tabela de páginas.
 * @param num_pages Número de páginas.
 * @param page_size Tamanho da página.
 */
void init_table(Table * table, unsigned num_pages, unsigned page_size)
{
    table->pages = (Page *)malloc(num_pages * sizeof(Page));
    table->frames = (unsigned *)malloc(num_pages * sizeof(unsigned));
}