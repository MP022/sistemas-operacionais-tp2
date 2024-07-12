#include <stdio.h>
#include <stdlib.h>
#include "table.h"

char *replacement_policy;
char *diretorio;
unsigned page_size;
unsigned physical_mem_size;
unsigned numPages;
Table *table;
Frame ** frames;

void read_entry(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Erro: Menos argumentos passados do que o mínimo desejado.\n");
    }

    replacement_policy = argv[1];
    diretorio = argv[2];
    page_size = strtol(argv[3], NULL, 10) * 1024;
    physical_mem_size = strtol(argv[4], NULL, 10) * 1024;
    numPages = physical_mem_size / page_size;
    table = (Table *)malloc(sizeof(Table));
    init_table(table, numPages, page_size, replacement_policy);
    frames = (Frame **)malloc(numPages * sizeof(Frame *));
    for (int i = 0; i < numPages; i++)
    {
        frames[i] = (Frame *)malloc(sizeof(Frame));
        frames[i]->page = -1;
    }
}

int main(int argc, char **argv)
{
    read_entry(argc, argv);
    printf("Executando o simulador...\n");
   

    FILE *arqEntrada;

    arqEntrada = fopen(diretorio, "r");
    if (arqEntrada == NULL)
    {
        printf("Erro: O arquivo de entrada não pode ser aberto.\n");
    }

    unsigned addr = NULL;
    char  rw = NULL;

    int seg_fault = 0;
    while (!feof(arqEntrada))
    {
        fscanf(arqEntrada, "%x %c", &addr, &rw);
        process_address(table, frames, addr, rw);
        addr = NULL;
        rw = NULL;
    }

    fclose(arqEntrada);
    printf("Page faults: %d\n", table->page_faults);
    printf("Arquivo de entrada: %s\n", diretorio);
    printf("Tamanho da memoria: %d KB\n", physical_mem_size);
    printf("Tamanho das páginas: %d KB\n", page_size);
    printf("Tecnica de reposição: %s\n", replacement_policy);
    printf("Páginas lidas: %d\n", table->pages_read);
    printf("Páginas escritas: %d\n", table->pages_write);
    printf("Total de acessos: %d\n", table->pages_write+ table->pages_read);
    return 0;
}