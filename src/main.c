#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/table.h"
#include "../include/table_multilevel.h"

char *replacement_policy;
char *diretorio;
unsigned page_size;
unsigned physical_mem_size;
unsigned numFrames;
Table *table;
TableMultilevel *tableMultilevel;
Frame ** frames;
Frame ** framesMultilevel;
unsigned long BITS_32 = 4294967296;
void read_entry(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Erro: Menos argumentos passados do que o mínimo desejado.\n");
    }

    replacement_policy = argv[1];
    diretorio = argv[2];
    page_size = strtol(argv[3], NULL, 10) * 1024;
    physical_mem_size = strtol(argv[4], NULL, 10) *1024;
    numFrames = physical_mem_size / page_size;

    long numPages = BITS_32 / page_size;
    table = (Table *)malloc(sizeof(Table));
    tableMultilevel = (TableMultilevel *)malloc(sizeof(TableMultilevel));
    printf("Bit %ld Num pages: %ld\n", BITS_32, numPages);
    init_table(table, numPages, page_size, replacement_policy);
    init_table_multinivel(tableMultilevel, sqrtl(numPages), sqrtl(numPages), page_size, replacement_policy);
    frames = (Frame **)malloc(numFrames * sizeof(Frame *));
    framesMultilevel = (Frame **)malloc(numFrames * sizeof(Frame *));
    
    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = (Frame *)malloc(sizeof(Frame));
        frames[i]->page = -1;
        framesMultilevel[i] = (Frame *)malloc(sizeof(Frame));
        framesMultilevel[i]->page = -1;
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

    unsigned addr;
    char  rw;

    int seg_fault = 0;
    while (!feof(arqEntrada))
    {
        fscanf(arqEntrada, "%x %c", &addr, &rw);
        process_address(table, frames, numFrames, addr, rw);
        process_address_multinivel(tableMultilevel, framesMultilevel, numFrames, addr, rw);
        process_address(table, frames, numFrames, addr, rw);    
        addr = NULL;
        rw = NULL;
    }

    fclose(arqEntrada);
    printf("Quantidade de páginas: %d\n", table->size);
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