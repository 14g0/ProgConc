/*
    Autor: Iago Cesar T. de Souza
    DRE: 122087998

    Comando de compilação: gcc -o seq lab2seq.c ../utils.c -ansi -pedantic -Wall
*/

#include "../progConc.h"

int main(int argc, char **argv) {
    float *vetor1, *vetor2;
    long double prodVet;
    FILE *arquivo;
    int cont, N;

    srand(time(NULL));

    if(argc != 2) {
        puts("\033[33mQuantidade de argumentos inválida [main L8]\033[m");
        exit(-1);
    }
    if((arquivo = fopen("output.bin", "wb")) == NULL) {
        puts("\033[33]mNão foi possível abrir o arquivo para escrita [main L12]\033[m");
        exit(-2);
    }

    N = atoi(argv[1]);

    vetor1 = generateRandNumberArray(N, "float");
    vetor2 = generateRandNumberArray(N, "float");

    for(cont = 0 ; cont < N ; cont += 1) printf("%f ", vetor1[cont]);
    puts("");
    for(cont = 0 ; cont < N ; cont += 1) printf("%f ", vetor2[cont]);
    puts("");
    for(cont = 0 ; cont < N ; cont += 1) prodVet += vetor1[cont] * vetor2[cont];

    fwrite(&N, sizeof(int), 1, arquivo);
    fwrite(vetor1, sizeof(float), N, arquivo);
    fwrite(vetor2, sizeof(float), N, arquivo);
    fwrite(&prodVet, sizeof(long double), 1, arquivo);

    if(fclose(arquivo)) {
        puts("\033[31mErro ao fechar o arquivo\033[m");
        exit(-3);
    }

    return 1;
}