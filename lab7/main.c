#include "../progConc.h"
#include <semaphore.h>

#define MAX_BUFFER_SIZE 23
#define ADD_CHAR '\n'

/*----------------------------------------------------------------------------*/

void *lerArquivo(void *args);
void *processarBuffer(void *args);
void *imprimirBuffer(void *args);

/*----------------------------------------------------------------------------*/

FILE *arquivo;
int charsLidos = 0, thread2Cont = 0;
char charAtual = 0, buffer1[MAX_BUFFER_SIZE], buffer2[MAX_BUFFER_SIZE];
sem_t semaf1, semaf2, semaf3;

/*----------------------------------------------------------------------------*/

int main(int argc, char **argv) {
    int cont;
    pthread_t *threadArray;
    void *(*funcoes[])(void *) = {lerArquivo, processarBuffer, imprimirBuffer};

    /* Realiza as validações para o bom funcionamento do programa ------------*/
    if(argc < 2) {
        puts("\033[31;1mPoucos argumentos na execução do programa.");
        puts("\033[33m./main <Nome do arquivo>\033[m");
        exit(-1);
    }

    if((arquivo = fopen(argv[1], "r")) == NULL) {
        puts("\033[31;1mNão foi possível abrir o arquivo\033[m");
        exit(-2);
    }

    /*Inicializa as variás relativas às threads ------------------------------*/
    threadArray = initThreadArray(3);
    sem_init(&semaf1, 0, 1);
    sem_init(&semaf2, 0, 0);
    sem_init(&semaf3, 0, 0);

    for(cont = 0 ; cont < 3 ; cont+=1) initThread(&threadArray[cont], funcoes[cont], NULL);

    /*Finaliza as variáveis alocadas pelo programa ---------------------------*/
    for(cont = 0 ; cont < 3 ; cont +=1) pthread_join(threadArray[cont], NULL);

    if(fclose(arquivo) != 0) {
        puts("\033[33mErro ao fechar o arquivo.\n\033[31;1mAbortando programa...\033[m");
        exit(-3);
    }
    sem_destroy(&semaf1);
    sem_destroy(&semaf2);
    sem_destroy(&semaf3);

    return 1;
}

/*----------------------------------------------------------------------------*/

void *lerArquivo(void *args) {
    sem_wait(&semaf1);

    while((charAtual = fgetc(arquivo)) != EOF) {
        buffer1[charsLidos] = charAtual;
        charsLidos += 1;

        if((charsLidos == ((2 * thread2Cont) + 1)) || (!(charsLidos % 10) && thread2Cont > 10)) {
            sem_post(&semaf2);
            sem_wait(&semaf1);
            charsLidos = 0;
        }
    }
    
    sem_post(&semaf2);
    return NULL;
}

void *processarBuffer(void *args) {
    sem_wait(&semaf2);

    while(charAtual != EOF) {
        buffer1[charsLidos] = '\0';
        strcpy(buffer2, buffer1);

        buffer2[charsLidos] = ADD_CHAR;
        buffer2[charsLidos + 1] = '\0';

        thread2Cont += 1;

        sem_post(&semaf3);
        sem_wait(&semaf2);
    }

    sem_post(&semaf3);
    return NULL;
}

void *imprimirBuffer(void *args) {
    sem_wait(&semaf3);

    while(charAtual != EOF) {
        printf("%s", buffer2);

        sem_post(&semaf1);
        sem_wait(&semaf3);
    }

    sem_post(&semaf1);
    return NULL;
}