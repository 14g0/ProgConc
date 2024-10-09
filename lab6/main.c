#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "list_int.h"
#include "timer.h"

#define QTDE_OPS 1000     /* quantidade de operacoes sobre a lista (insercao, remocao, consulta) */
#define QTDE_INI 100      /* quantidade de insercoes iniciais na lista */
#define MAX_VALUE 100     /* valor maximo a ser inserido */

/*----------------------------------------------------------------------------*/

void *tarefa(void *arg);

void habilitarLeitura(void);
void finalizarLeitura(void);

void habilitarEscrita(void);
void finalizarEscrita(void);

/*----------------------------------------------------------------------------*/

pthread_mutex_t mutex;
pthread_cond_t condLeitura, condEscrita;

struct list_node_s *head_p = NULL;
int nthreads, leitura = 0, escrita = 0, escritaAguardando = 0;

/*----------------------------------------------------------------------------*/

int main(int argc, char *argv[]) {
    pthread_t *threadIdArray;
    double ini, fim, delta;
    long int cont;

    srand(time(NULL));

    if(argc < 2) {
        printf("Digite: %s <numero de threads>\n", argv[0]);
        return 1;
    }
    nthreads = atoi(argv[1]);

    for(cont = 0; cont < QTDE_INI; cont++) Insert(cont % MAX_VALUE, &head_p);

    if((threadIdArray = malloc(sizeof(pthread_t) * nthreads)) == NULL) {
        puts("--ERRO: malloc()");
        return 2;
    }

    GET_TIME(ini);
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condLeitura, NULL);
    pthread_cond_init(&condEscrita, NULL);

    for(cont = 0; cont < nthreads; cont++) {
        if(pthread_create(threadIdArray + cont, NULL, tarefa, (void *)&cont)) {
            puts("--ERRO: pthread_create()\n");
            return 3;
        }
    }

    for(cont = 0; cont < nthreads; cont++) {
        if (pthread_join(*(threadIdArray + cont), NULL)) {
            puts("--ERRO: pthread_join()\n");
            return 4;
        }
    }

    GET_TIME(fim);
    delta = fim - ini;
    printf("Tempo: %f\n", delta);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condLeitura);
    pthread_cond_destroy(&condEscrita);
    free(threadIdArray);
    Free_list(&head_p);

    return 1;
}

/*----------------------------------------------------------------------------*/

void *tarefa(void *arg) {
    long int id = *(long int *)arg, cont;
    int op, in, out, read;
    in = out = read = 0;

    for(cont = id; cont < QTDE_OPS; cont += nthreads) {
        op = rand() % 100;
        if(op < 50) {
            habilitarLeitura(); /* lock de LEITURA */
            Member(cont % MAX_VALUE, head_p);  /* Ignore return value */
            finalizarLeitura();
            read++;
        }
        else if(50 <= op && op < 75) {
            habilitarEscrita(); /* lock de ESCRITA */
            Insert(cont % MAX_VALUE, &head_p); /* Ignore return value */
            finalizarEscrita();
            in++;
        }
        else if(op >= 75) {
            habilitarEscrita(); /* lock de ESCRITA */
            Delete(cont % MAX_VALUE, &head_p); /* Ignore return value */
            finalizarEscrita();
            out++;
        }
    }
    /* registra a qtde de operacoes realizadas por tipo */
    printf("Thread %ld: in=%d out=%d read=%d\n", id, in, out, read);
    pthread_exit(NULL);

    return NULL;
}

void habilitarLeitura(void) {
    pthread_mutex_lock(&mutex);

    while(escrita > 0 || escritaAguardando > 0) {
        puts("\033[33mLeitura bloqueada, aguardando término da escrita ou uma nova escrita que está esperando.\033[m");
        pthread_cond_wait(&condLeitura, &mutex);
    }
    leitura += 1;
    printf("\033[32;1mLeitura habilitada. Leituras ativas: %d\n\033[m", leitura);

    pthread_mutex_unlock(&mutex);
}

void finalizarLeitura(void) {
    pthread_mutex_lock(&mutex);

    leitura -= 1;
    if(leitura == 0) {
        puts("\033[36mTodas as leituras finalizadas, sinalizando possibilidade de escrita.\033[m");
        pthread_cond_signal(&condEscrita);
    } else {
        printf("\033[32;1mLeitura finalizada. Leituras ativas: %d\n\033[m", leitura);
    }

    pthread_mutex_unlock(&mutex);
}

void habilitarEscrita(void) {
    pthread_mutex_lock(&mutex);

    escritaAguardando += 1;
    while((leitura > 0) || (escrita > 0)) {
        puts("\033[31mEscrita bloqueada, aguardando término de leitura ou outra escrita.\033[m");
        pthread_cond_wait(&condEscrita, &mutex);
    }
    escritaAguardando -= 1;
    escrita += 1;
    printf("\033[35;1mEscrita habilitada. Escritas ativas: %d\033[m\n", escrita);

    pthread_mutex_unlock(&mutex);
}

void finalizarEscrita(void) {
    pthread_mutex_lock(&mutex);

    escrita -= 1;
    printf("\033[35;1mEscrita finalizada. Escritas ativas: %d\n\033[m", escrita);
    pthread_cond_signal(&condEscrita);
    pthread_cond_broadcast(&condLeitura);
    puts("\033[36mEscrita finalizada, sinalizando possibilidade de leitura.\033[m");

    pthread_mutex_unlock(&mutex);
}