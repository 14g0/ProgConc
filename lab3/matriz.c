/*
    gcc -o matriz matriz.c ../utils.c -ansi -pedantic -Wall
*/

#include "../progConc.h"

int main(int argc, char **argv) {
    int cont, cont2, N, M;
    FILE *arquivo;
    float *vetor;

    srand(time(NULL));

    if(argc < 4) {
        /* TODO: ajustar número da linha */
        puts("\033[31mQuantidade de argumentos inválida [main L9]\033[m");
        puts("\033[33mFormato esperado: <Linhas> <Colunas> <Arquivo de saída>\033[m");
        exit(-1);
    }

    if((arquivo = fopen(argv[3], "wb")) == NULL) {
        /* TODO: ajustar número da linha */
        puts("\033[31mNão foi possível criar o arquivo para escrita [main L16]");
        exit(-2);
    }

    N = atoi(argv[1]);
    M = atoi(argv[2]);

    vetor = generateRandNumberArray(N * M, "float");

    fwrite(&N, sizeof(int), 1, arquivo);
    fwrite(&M, sizeof(int), 1, arquivo);
    fwrite(vetor, sizeof(float), N * M, arquivo);

    if(fclose(arquivo)) {
        puts("\033[31mErro ao fechar o arquivo\033[m");
        exit(-3);
    }

    printf("Linhas: %d\nColunas: %d\n", N, M);
    for(cont = 0 ; cont < N ; cont += 1) {
        for(cont2 = 0 ; cont2 < M ; cont2 += 1) {
            printf("%f ", vetor[(cont * M) + cont2]);
        }
        puts("");
    }

    return 0;
}