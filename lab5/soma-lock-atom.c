/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Comunicação entre threads usando variável compartilhada e exclusao mutua com bloqueio */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long int soma = 0;
int cont = 0;
pthread_mutex_t mutex;
pthread_cond_t ext, execTarefa;

void *ExecutaTarefa(void *arg) {
    int i;
    long int id = (long int)arg;

    printf("Thread : %ld esta executando...\n", id);

    for (i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);
        
        if(!(soma % 10) && (cont < 20)) {
            puts("BLOCK execT");
            pthread_cond_wait(&execTarefa, &mutex);
            pthread_cond_signal(&ext);
            pthread_mutex_lock(&mutex);
        }
        soma++;

        pthread_mutex_unlock(&mutex);
    }
    printf("Thread : %ld terminou!\n", id);
    pthread_exit(NULL);
}

void *extra(void *args) {

    printf("Extra : esta executando...\n");

    for (cont = 0 ; cont < 20 ; cont += 1) {
        pthread_mutex_lock(&mutex);

        puts("entrou");
        printf("soma = %ld \n", soma);

        pthread_cond_broadcast(&execTarefa);
        puts("BLOCK ext");
        pthread_cond_wait(&ext, &mutex);
    }

    printf("Extra : terminou!\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t *tid;
    int nthreads;

    if (argc < 2) {
        printf("Digite: %s <numero de threads>\n", argv[0]);
        return 1;
    }
    nthreads = atoi(argv[1]);

    tid = (pthread_t *)malloc(sizeof(pthread_t) * (nthreads + 1));
    if (tid == NULL) {
        puts("ERRO--malloc");
        return 2;
    }

    pthread_mutex_init(&mutex, NULL);

    for (long int t = 0; t < nthreads; t++) {
        if (pthread_create(&tid[t], NULL, ExecutaTarefa, (void *)t)) {
            printf("--ERRO: pthread_create()\n");
            exit(-1);
        }
    }

    if (pthread_create(&tid[nthreads], NULL, extra, NULL)) {
        printf("--ERRO: pthread_create()\n");
        exit(-1);
    }

    for (int t = 0; t < nthreads + 1; t++) {
        if (pthread_join(tid[t], NULL)) {
            printf("--ERRO: pthread_join() \n");
            exit(-1);
        }
    }

    pthread_mutex_destroy(&mutex);

    printf("Valor de 'soma' = %ld\n", soma);

    return 0;
}
