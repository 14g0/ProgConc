/*
    Autor: Iago Cesar T. de Souza
    DRE: 122087998

    Comando de compilação: gcc -o conc lab2conc.c ../utils.c -ansi -pedantic -Wall
*/

#include "../progConc.h"

/*----------------------------------------------------------------------------*/

void *calculateProdVet(void *arg);

/*----------------------------------------------------------------------------*/

typedef struct prodVetArgs {
    int start, qtd, threadId;
    void *vetor1, *vetor2;
} prodVetArgs;

typedef struct threadRetVal {
    int threadId;
    long double returnValue;
} threadRetVal;

/*----------------------------------------------------------------------------*/

int main(int argc, char **argv) {
    int cont, T, N, div, mod;
    long double prodVetSeq, prodVetConc = 0, variacao;
    float *vetor1, *vetor2;
    prodVetArgs *threadArg;
    threadRetVal *retVal;
    pthread_t *threads;
    FILE *arquivo;

    if(argc != 3) {
        puts("\033[33mQuantidade de argumentos inválida [main L8]\033[m");
        exit(-1);
    }
    if((arquivo = fopen(argv[2], "rb")) == NULL) {
        puts("\033[33mNão foi possível abrir o arquivo para escrita [main L12]\033[m");
        exit(-2);
    }

    T = atoi(argv[1]);
    fread(&N, sizeof(int), 1, arquivo);

    vetor1 = mallocMem(N*sizeof(float));
    fread(vetor1, sizeof(float), N, arquivo);

    vetor2 = mallocMem(N*sizeof(float));
    fread(vetor2, sizeof(float), N, arquivo);
    
    fread(&prodVetSeq, sizeof(long double), 1, arquivo);

    if(T > N) T = N;
    div = N / T;
    mod = N % T;
    N = 0;

    threads = initThreadArray(T);
    for(cont = 0 ; cont < T ; cont += 1) {
        if((threadArg = malloc(sizeof(prodVetArgs))) == NULL) {
            puts("\033[31mNão foi possível alocar um novo argumento para a thread [mallocArgsUnaryInc]\033[m");
            exit(-3);
        }

        threadArg->start = N;
        threadArg->threadId = cont;
        threadArg->qtd = div + (cont < mod);
        threadArg->vetor1 = vetor1;
        threadArg->vetor2 = vetor2;
        N += threadArg->qtd;

        initThread(&threads[cont], calculateProdVet, threadArg);
    }

    for(cont = 0 ; cont < T ; cont += 1) {
        if(pthread_join(threads[cont], (void **) &retVal)) {
            printf("--ERRO: pthread_join() da thread %d\n", retVal->threadId); 
        }

        prodVetConc += retVal->returnValue;
        free(retVal);
    }

    variacao = (prodVetSeq - prodVetConc) / prodVetSeq;
    printf("\033[32mERRO RELATIVO:\033[m %Lf\n", variacao > 0? variacao : -1*variacao);

    return 1;
}

void *calculateProdVet(void *arg) {
    prodVetArgs *threadArg = (prodVetArgs *)arg;
    int cont, start = threadArg->start;
    float *vetor1, *vetor2;
    threadRetVal *retVal = mallocMem(sizeof(threadRetVal));

    retVal->threadId = threadArg->threadId;
    retVal->returnValue = 0;
    vetor1 = threadArg->vetor1;
    vetor2 = threadArg->vetor2;

    for(cont = 0 ; cont < threadArg->qtd ; cont += 1) {
        retVal->returnValue += vetor1[cont + start] * vetor2[cont + start];
    }

    free(arg);
    pthread_exit(retVal);

    return NULL;
}