#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/*----------------------------------------------------------------------------*/

typedef struct argsUnaryInc {
    int incStart, incQtd;
} argsUnaryInc;

/*----------------------------------------------------------------------------*/

void *unaryIncrement(void *arg);
int *generateIntArray(int qtt);
pthread_t *initThreadArray(int size_arr);

/*----------------------------------------------------------------------------*/

int *numberArray;

int main(int argc, char** argv) {
    pthread_t *threads;
    argsUnaryInc *arg;
    int cont, div, mod, N, M, *baseArray;

    if(argc != 3) {
        puts("\033[33mQuantidade de argumentos inválida [main L7]\033[m");
        exit(-1);
    }

    M = atoi(argv[1]);
    N = atoi(argv[2]);
    if(M > N) M = N;
    div = N / M;
    mod = N % M;

    numberArray = generateIntArray(N);
    threads = initThreadArray(M);

    if((baseArray = malloc(sizeof(int) * N)) == NULL) {
        puts("\033[31mNão foi possível alocar o vetor de comparação [main L17]\033[m");
        exit(-1);
    }
    for(cont = 0 ; cont < N ; cont += 1) baseArray[cont] = numberArray[cont];
    N = 0;

    for(cont = 0 ; cont < M ; cont += 1) {
        if((arg = malloc(sizeof(argsUnaryInc))) == NULL) {
            puts("\033[31mNão foi possível alocar um novo argumento para a thread [mallocArgsUnaryInc]\033[m");
            exit(-3);
        }

        arg->incStart = N;
        arg->incQtd = div + (cont < mod);
        N += arg->incQtd;

        if(pthread_create(&threads[cont], NULL, unaryIncrement, arg)) {
            puts("\033[31mNão foi possível instaciar uma nova thread [initThreads L3]\033[m");
            exit(-13);
        }
        if(pthread_join(threads[cont], NULL)) {
            printf("--ERRO: pthread_join() da thread %d\n", cont); 
        }
    }

    for(cont = 0 ; cont < N ; cont += 1) {
        if(numberArray[cont] != baseArray[cont] + 1) {
            printf("NA: %d, BA: %d\n", numberArray[cont], baseArray[cont]);
            puts("\033[31mUm valor não está correto, o programa deu errado\033[m");
            return -1;
        }
    }
    puts("\033[32mArrays verificados, deu tudo certo :)\033[m");
    return 1;
}

void *unaryIncrement(void *arg) {
    int cont;
    argsUnaryInc *argument = (argsUnaryInc *)arg;

    for(cont = 0 ; cont < argument->incQtd ; cont += 1) {
        numberArray[cont + argument->incStart] += 1;
    }

    free(arg);

    return NULL;
}

int *generateIntArray(int qtt) {
    int cont, *array;
    srand(time(0));

    if((array = malloc(sizeof(int) * qtt)) == NULL) {
        puts("\033[31mNão foi possível alocar o vetor de inteiros [generateIntArray L5]\033[m");
        exit (-3);
    }

    for(cont = 0 ; cont < qtt ; cont += 1) array[cont] = rand() % qtt;

    return array;
}

pthread_t *initThreadArray(int size_arr) {
    pthread_t *threads;

    if((threads = malloc(sizeof(pthread_t) * size_arr)) == NULL) {
        puts("\033[31mNão foi possível inicializar o array de threads [initThreadArray L5]\033[m");
        exit(-25);
    }

    return threads;
}