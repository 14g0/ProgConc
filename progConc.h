#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

/*----------------------------------------------------------------------------*/

typedef struct threadArg {
    int incStart, incQtd;
    void *pointer;
} threadArg;

/*----------------------------------------------------------------------------*/

void *generateRandNumberArray(int qtt, char* numberType);

void initThread(pthread_t *threadLocal, void *threadFunction(void *arg), void* args);
pthread_t *initThreadArray(int size_arr);

void *mallocMem(size_t size);