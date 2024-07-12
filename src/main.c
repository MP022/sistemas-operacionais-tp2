#include <stdio.h>
#include <stdlib.h>
#include "table.h"

char *algoritmo;
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

    algoritmo = argv[1];
    diretorio = argv[2];
    page_size = strtol(argv[3], NULL, 10) * 1024;
    physical_mem_size = strtol(argv[4], NULL, 10) * 1024;
    numPages = physical_mem_size / page_size;
    table = (Table *)malloc(sizeof(Table));
    init_table(table, numPages, page_size);
    frames = (Frame **)malloc(numPages * sizeof(Frame *));
}

int main(int argc, char **argv)
{
    read_entry(argc, argv);
    printf("Executando o simulador...\n");
    unsigned s, tmp;

    /* Derivar o valor de s: */
    tmp = page_size;
    s = 0;
    while (tmp > 1)
    {
        tmp = tmp >> 1;
        s++;
    }

    int pagLidas = 0, pagEscri = 0, totalAcesso = 0;
    FILE *arqEntrada;

    arqEntrada = fopen(diretorio, "r");
    if (arqEntrada == NULL)
    {
        printf("Erro: O arquivo de entrada não pode ser aberto.\n");
    }

    unsigned addr = NULL,page = NULL;
    char  rw = NULL;

    int seg_fault = 0;
    while (!feof(arqEntrada))
    {
        fscanf(arqEntrada, "%x %c", &addr, &rw);
        if (addr != NULL && rw != NULL)
        {
            totalAcesso++;
            page = page_from_addr(addr,s);
            if (rw == 'W')
            {
                read(table,frames, addr, page);
                pagLidas++;
            }
            else
            {
                write(table,frames, addr, page);
                pagEscri++;
            }
        }
        addr = NULL;
        rw = NULL;
    }

    fclose(arqEntrada);

    printf("Arquivo de entrada: %s\n", diretorio);
    printf("Tamanho da memoria: %d KB\n", physical_mem_size);
    printf("Tamanho das páginas: %d KB\n", page_size);
    printf("Tecnica de reposição: %s\n", algoritmo);
    printf("Páginas lidas: %d\n", pagLidas);
    printf("Páginas escritas: %d\n", pagEscri);
    printf("Total de acessos: %d\n", totalAcesso);
    return 0;
}