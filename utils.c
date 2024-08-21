#include "./progConc.h"

void initThread(pthread_t *threadArray, int threadPosition, void *threadFunction, void* args) {
    if(pthread_create(&threadArray[threadPosition], NULL, threadFunction, args)) {
        puts("\033[31mNão foi possível instaciar uma nova thread [initThreads L3]");
        exit(-13);
    }
}

pthread_t *initThreadArray(int size_arr) {
    pthread_t *threads;

    if((threads = malloc(sizeof(pthread_t) * size_arr)) == NULL) {
        puts("\033[31mNão foi possível inicializar o array de threads [initThreadArray L5]");
        exit(-25);
    }

    return threads;
}