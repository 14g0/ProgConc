#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

/*----------------------------------------------------------------------------*/

void *generateRandNumberArray(int qtt, char* numberType);

void initThread(pthread_t *threadLocal, void *threadFunction(void *arg), void* args);
pthread_t *initThreadArray(int size_arr);

void *mallocMem(size_t size);

/*----------------------------------------------------------------------------*/

#ifndef _CLOCK_TIMER_H
#define _CLOCK_TIMER_H

#define BILLION 1000000000L

/* The argument now should be a double (not a pointer to a double) */
#define GET_TIME(now) { \
   struct timespec time; \
   clock_gettime(CLOCK_MONOTONIC, &time); \
   now = time.tv_sec + time.tv_nsec/1000000000.0; \
}
#endif