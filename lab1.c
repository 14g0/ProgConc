#include <./progConc.h>

/*----------------------------------------------------------------------------*/

void *unaryIncrement(argsUnaryInc arg);


/*----------------------------------------------------------------------------*/

typedef struct argsUnaryInc {
    int incStart,
        incQtd;
} argsUnaryInc;

/*----------------------------------------------------------------------------*/

int main(int argc, char** argv) {
    pthread_t *threads;
    int cont,
    *numberArray = {3, 6, 2, 9, 1, 84, 55, 18, 23, 45},
    *correctNumberArray = {4, 7, 3, 10, 2, 85, 56, 19, 24, 46};

    return 1;
}

void *unaryIncrement(argsUnaryInc arg) {
    int cont;

    for(cont = 0 ; cont < arg.incQtd ; cont += 1) {

    }
}
