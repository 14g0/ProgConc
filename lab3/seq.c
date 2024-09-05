/*
    gcc -o seq seq.c ../utils.c -ansi -pedantic -Wall
*/

#include "../progConc.h"

/*----------------------------------------------------------------------------*/

typedef struct matriz {
    int linhas, colunas;
    float *vetor;
} matriz;

/*----------------------------------------------------------------------------*/

void printMatriz(matriz *matriz);
matriz multiplicarMatrizes(matriz mat1, matriz mat2);

/*----------------------------------------------------------------------------*/

int main(int argc, char **argv) {
    double inicio, fim, inicializacao, execucao, finalizacao;
    matriz matriz1, matriz2, matrizSaida;
    FILE *arquivo;

    if(argc < 4) {
        /* TODO: ajustar número da linha */
        puts("\033[31mQuantidade de argumentos inválida [main L]\033[m");
        puts("\033[33mFormato esperado: <Arquivo de entrada> <Arquivo de entrada> <Arquivo de saída>\033[m");
        exit(-1);
    }

    if((arquivo = fopen(argv[1], "rb")) == NULL) {
        /* TODO: ajustar número da linha */
        puts("\033[31mNão foi possível criar o arquivo para escrita [main L16]\033[m");
        exit(-2);
    }
    fread(&matriz1.linhas, sizeof(int), 1, arquivo);
    fread(&matriz1.colunas, sizeof(int), 1, arquivo);
    matriz1.vetor = mallocMem(matriz1.linhas * matriz1.colunas);
    fread(matriz1.vetor, sizeof(float), matriz1.linhas * matriz1.colunas, arquivo);

    if((arquivo = fopen(argv[2], "rb")) == NULL) {
        /* TODO: ajustar número da linha */
        puts("\033[31mNão foi possível criar o arquivo para escrita [main L16]\033[m");
        exit(-2);
    }
    fread(&matriz2.linhas, sizeof(int), 1, arquivo);
    fread(&matriz2.colunas, sizeof(int), 1, arquivo);
    matriz2.vetor = mallocMem(matriz2.linhas * matriz2.colunas);
    fread(matriz2.vetor, sizeof(float), matriz2.linhas * matriz2.colunas, arquivo);

    GET_TIME(inicializacao)

    matrizSaida = multiplicarMatrizes(matriz1, matriz2);

    printMatriz(&matrizSaida);

    if(fclose(arquivo)) {
        puts("\033[31mErro ao fechar o arquivo\033[m");
        exit(-3);
    }

    return 0;
}

/*----------------------------------------------------------------------------*/

void printMatriz(matriz *matriz) {
    int cont, cont2;

    printf("Linhas: %d\nColunas: %d\n", matriz->linhas, matriz->colunas);
    for(cont = 0 ; cont < matriz->linhas ; cont += 1) {
        for(cont2 = 0 ; cont2 < matriz->colunas ; cont2 += 1) {
            printf("%f ", matriz->vetor[(cont * matriz->colunas) + cont2]);
        }
        puts("");
    }
    puts("");
}

matriz multiplicarMatrizes(matriz mat1, matriz mat2) {
    matriz matResultado;
    int cont, cont2, cont3;

    if(mat1.colunas != mat2.linhas) {
        printf("\033[33mNão é possível multiplicar uma matriz %dx%d por uma %dx%d\033[m\n", mat1.linhas, mat1.colunas, mat2.linhas, mat2.colunas);
        exit(-36);
    }
    matResultado.colunas = mat2.colunas;
    matResultado.vetor = malloc(sizeof(float) * mat1.colunas * mat2.linhas);
    matResultado.linhas = mat1.linhas;

    for(cont = 0 ; cont < mat1.linhas ; cont += 1) {
        for(cont2 = 0 ; cont2 < mat2.colunas ; cont2 += 1) {
            matResultado.vetor[cont * mat2.colunas + cont2] = 0;

            for(cont3 = 0 ; cont3 < mat1.colunas ; cont += 1) {

                matResultado.vetor[cont * mat2.colunas + cont2] += mat1.vetor[cont * mat1.colunas + cont3] * mat2.vetor[cont3 * mat2.colunas + cont2];
            }
        }
    }

    return matResultado;
}