#include "./progConc.h"

void *generateRandNumberArray(int qtt, char* numberType) {
    int cont;
    void *numberArray;

    srand(time(0));

    if(!strcmp(numberType, "float")) {
        if((numberArray = malloc(sizeof(float) * qtt)) == NULL) {
            puts("\033[31mNão foi possível alocar o vetor de float [generateIntArray L8]\033[m");
            exit (-18);
        }

        for(cont = 0 ; cont < qtt ; cont += 1) {
            ((float *)numberArray)[cont] = ((float)rand() / (float)RAND_MAX) * 100000;
        }
    }
    else if(!strcmp(numberType, "int")) {
        if((numberArray = malloc(sizeof(int) * qtt)) == NULL) {
            puts("\033[31mNão foi possível alocar o vetor de int [generateIntArray L18]\033[m");
            exit (-118);
        }

        for(cont = 0 ; cont < qtt ; cont += 1) {
            ((int *)numberArray)[cont] = (rand() / RAND_MAX) * 100000;
        }
    }
    else if(!strcmp(numberType, "double")) {
        if((numberArray = malloc(sizeof(double) * qtt)) == NULL) {
            puts("\033[31mNão foi possível alocar o vetor de double [generateIntArray L28]\033[m");
            exit (-128);
        }

        for(cont = 0 ; cont < qtt ; cont += 1) {
            ((double *)numberArray)[cont] = ((double)rand() / (double)RAND_MAX) * 100000;
        }
    }
    else {
        puts("Tipo de número desconhecido [generateRand]");
        exit(-38);
    }

    return numberArray;
}

/*----------------------------------------------------------------------------*/

void initThread(pthread_t *threadLocal, void *threadFunction(void *arg), void* args) {
    if(pthread_create(threadLocal, NULL, threadFunction, args)) {
        puts("\033[31mNão foi possível instaciar uma nova thread [initThreads L2]\033[m");
        exit(-22);
    }
}

/*----------------------------------------------------------------------------*/

pthread_t *initThreadArray(int size_arr) {
    pthread_t *threads;

    if((threads = malloc(sizeof(pthread_t) * size_arr)) == NULL) {
        puts("\033[31mNão foi possível inicializar o array de threads [initThreadArray L4]\033[m");
        exit(-34);
    }

    return threads;
}

/*----------------------------------------------------------------------------*/

void *mallocMem(size_t size) {
    void *pointer;

    if((pointer = malloc(size)) == NULL) {
        puts("\033[31mNão foi possível alocar o espaço de memória\033[m");
        exit(-45);
    }

    return pointer;
}