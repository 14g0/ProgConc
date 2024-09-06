#include <stdio.h>
#include <stdlib.h>

int main(void) {
    float vetor[] = {2, 3, 5, 10};
    int N = 4, M=1;
    
    FILE *arquivo = fopen("vetor1", "wb");
    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fwrite(&N, sizeof(int), 1, arquivo);
    fwrite(&M, sizeof(int), 1, arquivo);
    fwrite(vetor, sizeof(float), N*M, arquivo);

    fclose(arquivo);

    printf("Vetor gravado com sucesso no arquivo binário.\n");

    return 0;
}