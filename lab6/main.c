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
void lockLeitura(void);
void lockEscrita(void);

/*----------------------------------------------------------------------------*/

pthread_mutex_t mutex;
pthread_cond_t condLeitura, condEscrita;

struct list_node_s *head_p = NULL;
int nthreads;

/*----------------------------------------------------------------------------*/

int main(int argc, char *argv[]) {
    pthread_t *threadIdArray;
    double ini, fim, delta;
    long int cont;

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
        if(pthread_create(threadIdArray + cont, NULL, tarefa, (void *)cont)) {
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
    printf("Tempo: %lf\n", delta);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condLeitura);
    pthread_cond_destroy(&condEscrita);
    free(threadIdArray);
    Free_list(&head_p);

    return 0;
}

/*----------------------------------------------------------------------------*/

void *tarefa(void *arg) {
    long int id = (long int)arg, cont;
    int op;
    int in, out, read;
    in = out = read = 0;

    for(cont = id; cont < QTDE_OPS; cont += nthreads) {
        op = rand() % 100;
        if(op < 50) {
            pthread_rwlock_rdlock(&rwlock); /* lock de LEITURA */
            Member(cont % MAX_VALUE, head_p);  /* Ignore return value */
            pthread_rwlock_unlock(&rwlock);
            read++;
        }
        else if(50 <= op && op < 75) {
            pthread_rwlock_wrlock(&rwlock); /* lock de ESCRITA */
            Insert(cont % MAX_VALUE, &head_p); /* Ignore return value */
            pthread_rwlock_unlock(&rwlock);
            in++;
        }
        else if(op >= 75) {
            pthread_rwlock_wrlock(&rwlock); /* lock de ESCRITA */
            Delete(cont % MAX_VALUE, &head_p); /* Ignore return value */
            pthread_rwlock_unlock(&rwlock);
            out++;
        }
    }
    /* registra a qtde de operacoes realizadas por tipo */
    printf("Thread %ld: in=%d out=%d read=%d\n", id, in, out, read);
    pthread_exit(NULL);
}

void lockLeitura(long int operationNumber) {
    /*
        Se chegar uma nova

        - Existe operação de escrita -> espera acabar para criar uma nova
        - Existe operação de leitura -> executa mesmo assim
    */

    pthread_mutex_lock(&mutex);
    while(escr > 0) {
        pthread_cond_wait(&condLeitura, &mutex);
    }
    leit++;
    pthread_mutex_unlock(&mutex);

    Member(operationNumber % MAX_VALUE, head_p);  /* Ignore return value */

    pthread_mutex_lock(&mutex);

    pthread_mutex_unlock(&mutex);
}

void lockEscrita() {
    /*
        Se chegar uma nova
        
        - Existe operação de leitura -> Tem q esperar acabar
        - Existe operação de escrita -> Espera acabar e executa assim q essa acabar
    */
}