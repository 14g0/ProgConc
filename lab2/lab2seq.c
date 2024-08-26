/*
    Autor: Iago Cesar T. de Souza
    DRE: 122087998

    Comando de compilação: gcc -o lab2 lab2seq.c ../utils.c -ansi -pedantic -Wall
*/

#include "../progConc.h"

int main(int argc, char **argv) {
    long double crossProduct;
    int cont, N;
    float *vetor1, *vetor2;
    FILE *file;

    if(argc != 2) {
        puts("\033[33mQuantidade de argumentos inválida [main L8]\033[m");
        exit(-1);
    }
    if((file = fopen("output.bin", "wb")) == NULL) {
        puts("\033[33]mNão foi possível abrir o arquivo para escrita [main L12]\033[m");
        exit(-2);
    }

    N = atoi(argv[1]);

    vetor1 = generateRandNumberArray(N, "float");
    vetor2 = generateRandNumberArray(N, "float");

    for(cont = 0 ; cont < N ; cont += 1) crossProduct += vetor1[cont] * vetor2[cont];

    fwrite(&N, sizeof(int), 1, file);
    fwrite(vetor1, sizeof(float), N*sizeof(float), file);
    fwrite(vetor2, sizeof(float), N*sizeof(float), file);
    fwrite(&crossProduct, sizeof(long double), 1, file);

    if(fclose(file)) {
        puts("\033[31mErro ao fechar o arquivo\033[m");
        exit(-3);
    }

    return 1;
}