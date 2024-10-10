# Explicação da lógica
O código foi implementado utilizando 4 funções:

```C
void habilitarLeitura(void);
void finalizarLeitura(void);

void habilitarEscrita(void);
void finalizarEscrita(void);
```

Como as funções bem expressam, as funções de **habilitar** avaliam se a escrita ou leitura podem ocorrer e atualizam as variáveis *"escrita"* e *"leitura"* para que as outras funções possam acessá-las e realizar o controle corretamente. Apesar a implementação feita, apenas as variáveis *"escrita"* e *"leitura"* não são suficiente para que a operação de Escrita seja priorizada de fato, o que levou à criação da variável *"escritaAguardando"*.

Com a variável *"escritaAguardando"* sendo utilizada da maneira exemplificada no trecho abaixo, caso alguma escrita esteja espera, novas leituras serão colocas na barreira para que a operação de escrita seja executada assim que as leituras terminarem.
```C
void habilitarLeitura(void) {
    pthread_mutex_lock(&mutex);

    while(escrita > 0 || escritaAguardando > 0) {
    .
    .
    .
```
---
Além disso, como é possível verificar na função abaixo, a variável *"escritaAguardando"* é decrementada logo quando a operação de escrita é liberada pelo *signal*, o que também evita o acúmulo e permite que seja criada uma fila de escrita.
```C
void habilitarEscrita(void) {
    pthread_mutex_lock(&mutex);
    escritaAguardando += 1;
    .
    .
    .
    escritaAguardando -= 1;
    pthread_mutex_unlock(&mutex);
}
```