#include "../progConc.h"
#include <semaphore.h>

/*----------------------------------------------------------------------------*/

void *lerArquivo(void *args);
void *processarBuffer(void *args);
void *imprimirBuffer(void *args);

/*----------------------------------------------------------------------------*/

FILE *arquivo;
int readChars = 0;
char *buffer1 = NULL, *buffer2 = NULL;
sem_t semaf1, semaf2, semaf3;

/*----------------------------------------------------------------------------*/

int main(int argc, char **argv) {
    int cont;
    pthread_t *threadArray;
    void *(*funcoes[])(void *) = {lerArquivo, processarBuffer, imprimirBuffer};

    if(argc < 2) {
        puts("\033[31;1mPoucos argumentos na execução do programa.");
        puts("\033[33m./main <Nome do arquivo>");
        exit(-1);
    }

    if((arquivo = fopen(argv[0], "r")) == NULL) {
        puts("\033[31;1mNão foi possível abrir o arquivo\033[m");
        exit(-2);
    }

    threadArray = initThreadArray(3);

    sem_init(&semaf1, 0, 1);
    sem_init(&semaf2, 0, 0);
    sem_init(&semaf3, 0, 0);


    for(cont = 0 ; cont < 3 ; cont+=1) initThread(&threadArray[cont], funcoes[cont], NULL);

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
    while(fgetc(arquivo)) {

        readChars += 1;
    }

    return NULL;
}

void *processarBuffer(void *args) {
    int cont;

    return NULL;
}

void *imprimirBuffer(void *args) {
    return NULL;
}