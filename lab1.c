#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/*----------------------------------------------------------------------------*/

typedef struct argsUnaryInc {
    int incStart, incQtd,
        *numberArray;
} argsUnaryInc;

/*----------------------------------------------------------------------------*/

void *unaryIncrement(void *arg);
int *generateIntArray(int qtt);
pthread_t *initThreadArray(int size_arr);

/*----------------------------------------------------------------------------*/

int main(int argc, char** argv) {
    pthread_t *threads;
    argsUnaryInc arg;
    int cont, supVar, N, M, *numberArray, *baseArray;

    if((argc < 2) || (argc > 3)) {
        puts("\033[32mQuantidade de argumentos inválida [main L7]");
        exit(-1);
    }
    M = atoi(argv[1]);
    N = atoi(argv[2]);

    numberArray = generateIntArray(N);
    threads = initThreadArray(M);

    if((baseArray = malloc(sizeof(int) * N)) == NULL) {
        puts("Não foi possível alocar o vetor de comparação [main L17]");
        exit(-1);
    }
    for(cont = 0 ; cont < N ; cont += 1) baseArray[cont] = numberArray[cont];

    supVar = (int) N / M;
    arg.numberArray = numberArray;
    arg.incQtd = supVar;

    for(cont = 0 ; cont < M ; cont += 1) {
        arg.incStart = cont * supVar;
        if(pthread_create(&threads[cont], NULL, unaryIncrement, &arg)) {
            puts("\033[31mNão foi possível instaciar uma nova thread [initThreads L3]");
            exit(-13);
        }
    }

    for (cont = 0; cont < M ; cont += 1) {
        if (pthread_join(threads[cont], NULL)) {
            printf("--ERRO: pthread_join() da thread %d\n", cont); 
        }
    }

    for(cont = 0 ; cont < N ; cont += 1) {
        printf("%02d ", arg.numberArray[cont]);
    }
    puts("");

    for(cont = 0 ; cont < N ; cont += 1) {
        printf("%02d ", baseArray[cont]);
    }
    puts("");
 
    return 1;
}

void *unaryIncrement(void *arg) {
    int cont;
    argsUnaryInc *argument = (argsUnaryInc *)arg;

    printf("%d %d\n", argument->incQtd, argument->incStart);

    for(cont = 0 ; cont < argument->incQtd ; cont += 1) {
        argument->numberArray[cont + argument->incStart] += 1;
    }

    return NULL;
}

int *generateIntArray(int qtt) {
    int cont, *array;
    srand(time(0));

    if((array = malloc(sizeof(int) * qtt)) == NULL) {
        puts("\033[31mNão foi possível alocar o vetor de inteiros [generateIntArray L5]");
        exit (-3);
    }

    for(cont = 0 ; cont < qtt ; cont += 1) array[cont] = rand() % qtt;

    return array;
}

pthread_t *initThreadArray(int size_arr) {
    pthread_t *threads;

    if((threads = malloc(sizeof(pthread_t) * size_arr)) == NULL) {
        puts("\033[31mNão foi possível inicializar o array de threads [initThreadArray L5]");
        exit(-25);
    }

    return threads;
}