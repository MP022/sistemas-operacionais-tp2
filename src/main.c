#include <stdio.h>
#include <stdlib.h>

char* algoritmo;
char* diretorio;
int tamBloco;
int tamProce;

void parse_args(int argc,char ** argv){
    if (argc < 4){
        printf("Erro: Menos argumentos passados do que o mínimo desejado");
    }
    
    algoritmo = argv[1];
    diretorio = argv[2];
    tamBloco = strtol(argv[3], NULL, 10);
    tamProce = strtol(argv[4], NULL, 10);
}

int main(int argc, char ** argv){
    parse_args(argc,argv);

    printf("%s\n", algoritmo);
    printf("%s\n", diretorio);
    printf("%d\n", tamBloco);
    printf("%d\n", tamProce);
    return 0;
}