#include "../progConc.h"
#include <semaphore.h>

/*----------------------------------------------------------------------------*/

typedef struct linkedChar {
    char caractere;
    struct linkedChar *nextLC, *prevLC;
} linkedChar;

/*----------------------------------------------------------------------------*/

linkedChar *newLinkedChar(void);
int addLinkedChar(linkedChar *linkedWord, linkedChar *newLinkedChar);
int removeLinkedChar(linkedChar *linkedWord);

void *lerArquivo(void *arquivo);
void *processarBuffer(void *buffer);
void *imprimirBuffer(void *buffer);

/*----------------------------------------------------------------------------*/

sem_t semaforo1;

/*----------------------------------------------------------------------------*/

int main(int argc, char **argv) {
    int cont;
    FILE *arquivo;
    pthread_t *threadArray;
    linkedChar *buffer1, *buffer2;
    void *(*funcoes[])(void *) = {lerArquivo, processarBuffer, imprimirBuffer};

    if(argc < 2) {
        puts("\033[31;1mPoucos argumentos na execução do programa.");
        puts("\033[33m./main <Nome do arquivo> <Quantidade de blocos para leitura>\033[m");
        exit(-1);
    }

    if((arquivo = fopen(argv[0], "r")) == NULL) {
        puts("\033[31;1mNão foi possível abrir o arquivo\033[m");
        exit(-1);
    }

    

    threadArray = initThreadArray(3);

    for(cont = 0 ; cont < 3 ; cont+=1) {
        initThread(&threadArray[cont], funcoes[cont], );
    }

    return 1;
}

/*----------------------------------------------------------------------------*/

linkedChar *newLinkedChar(void) {
    linkedChar *newLinkedChar = mallocMem(sizeof(linkedChar));
    newLinkedChar->caractere = NULL;
    newLinkedChar->nextLC = NULL;
    newLinkedChar->prevLC = NULL;

    return newLinkedChar;
}

int addLinkedChar(linkedChar *linkedWord, linkedChar *newLinkedChar) {
    linkedChar *linkedChar = linkedWord;

    while(linkedChar->nextLC != NULL) linkedChar = linkedChar->nextLC;

    linkedChar->nextLC = newLinkedChar;
}

/*----------------------------------------------------------------------------*/

void *lerArquivo(void *arquivo) {
    return NULL;
}

void *processarBuffer(void *buffer) {
    return NULL;
}

void *imprimirBuffer(void *buffer) {
    return NULL;
}