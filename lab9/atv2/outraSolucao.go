package main

import "fmt"

func outraSolucao() {
    canal = make(chan string);
    mensagensRotina = []string{
        "Oi Main, bom dia, tudo bem?",
        "Certo, entendido.",
        "finalizando",
    };

    mensagensMain = []string{
        "Olá Goroutine, bom dia!",
        "Tudo bem! Vou terminar tá?",
        "finalizando",
    };
   
    for i := 0 ; i < 3 ; i += 1 {
        go outraTarefa(i)
        canal <- mensagensMain[i]
        fmt.Printf("\033[36m%s\033[m\n", <-canal);
    }
}

func outraTarefa(iteracao int) {
    fmt.Printf("\033[33m%s\033[m\n", <-canal);
    canal <- mensagensRotina[iteracao]
}