#include <stdio.h>
#include <stdlib.h>

char* algoritmo;
char* diretorio;
unsigned tamBloco;
unsigned tamProce;

void parse_args(int argc,char ** argv){
    if (argc < 4){
        printf("Erro: Menos argumentos passados do que o mínimo desejado.\n");
    }
    
    algoritmo = argv[1];
    diretorio = argv[2];
    tamBloco = strtol(argv[3], NULL, 10);
    tamProce = strtol(argv[4], NULL, 10);
}

int main(int argc, char ** argv){
    parse_args(argc,argv);
    printf("Executando o simulador...\n");

    unsigned s, tmp;

    /* Derivar o valor de s: */
    tmp = tamBloco;
    s = 0;
    while (tmp>1) {
        tmp = tmp>>1;
        s++;
    }

    int pagLidas = 0, pagEscri = 0, totalAcesso = 0;
    FILE * arqEntrada;

    arqEntrada = fopen(diretorio,"r");
    if (arqEntrada == NULL){
        printf("Erro: O arquivo de entrada não pode ser aberto.\n");
    }
    

    unsigned addr = NULL, page = NULL;
    char rw = NULL;

    while (!feof(arqEntrada))
    {
        fscanf(arqEntrada,"%x %c",&addr,&rw);
        if(addr != NULL && rw != NULL){
            printf("%x %c\n", addr, rw);
            page = addr >> s;
            totalAcesso++;
        }
        addr = NULL;
        rw = NULL;
    }

    fclose(arqEntrada);	

    printf("Arquivo de entrada: %s\n", diretorio);
    printf("Tamanho da memoria: %d KB\n", tamProce);
    printf("Tamanho das páginas: %d KB\n", tamBloco);
    printf("Tecnica de reposição: %s\n", algoritmo);
    printf("Páginas lidas: %d\n", pagLidas);
    printf("Páginas escritas: %d\n", pagEscri);
    printf("Total de acessos: %d\n", totalAcesso);
    return 0;
}