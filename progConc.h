#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void initThreads(pthread_t **threadArray, int threadNumber, void *threadFunction, void* args);
pthread_t *initThreadArray(int size_arr);