#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/table.h"
#include "../include/table_multilevel2.h"

char *replacement_policy;
char *diretorio;
unsigned page_size;
unsigned physical_mem_size;
unsigned numFrames;
Table *table;
TableMultilevel2 *tableMultilevel2;
Frame ** frames;
Frame ** framesMultilevel2;
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
    tableMultilevel2 = (TableMultilevel2 *)malloc(sizeof(TableMultilevel2));
    init_table(table, numPages, page_size, numFrames, replacement_policy);
    init_table_multinivel2(tableMultilevel2, sqrtl(numPages), numFrames, page_size, replacement_policy);
    frames = (Frame **)malloc(numFrames * sizeof(Frame *));
    framesMultilevel2 = (Frame **)malloc(numFrames * sizeof(Frame *));
    
    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = (Frame *)malloc(sizeof(Frame));
        frames[i]->page = NULL;
        frames[i]->id = i;
        frames[i]->reference = 0;

        framesMultilevel2[i] = (Frame *)malloc(sizeof(Frame));
        framesMultilevel2[i]->page = NULL;
        framesMultilevel2[i]->id = i;
        framesMultilevel2[i]->reference = 0;
    }
    if(table->policy == RANDOM){
        srand(time(NULL));
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

    unsigned addr = -1;
    char rw = '\0';

    while (!feof(arqEntrada))
    {
        fscanf(arqEntrada, "%x %c", &addr, &rw);
        process_address(table, frames, addr, rw);
        process_address_multinivel2(tableMultilevel2, framesMultilevel2, addr, rw);
        table->interaction_counter++;
        addr = -1;
        rw = '\0';
    }

    fclose(arqEntrada);

    printf("Dados da execução\n");
    printf("Arquivo de entrada: %s\n", diretorio);
    printf("Tamanho da memoria: %d B\n", physical_mem_size);
    printf("Tamanho das páginas: %d B\n", page_size);
    printf("Tecnica de reposição: %s\n", replacement_policy);

    printf("\nRelatório: Tabela Densa\n");
    printf("Quantidade de páginas: %ld\n", table->size);
    printf("Page faults: %d\n", table->page_faults);
    printf("Páginas lidas: %d\n", table->pages_read);
    printf("Páginas escritas: %d\n", table->pages_write);
    printf("Total de acessos: %d\n", table->pages_write + table->pages_read);

    printf("\nRelatório: Tabela Hierárquica de 2 níveis\n");
    printf("Quantidade de páginas: %ld\n", tableMultilevel2->size);
    printf("Page faults: %d\n", tableMultilevel2->page_faults);
    printf("Páginas lidas: %d\n", tableMultilevel2->pages_read);
    printf("Páginas escritas: %d\n", tableMultilevel2->pages_write);
    printf("Total de acessos: %d\n", tableMultilevel2->pages_write + tableMultilevel2->pages_read);
    return 0;
}