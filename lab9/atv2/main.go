package main

import (
	"fmt"
)

var canal chan string;
var mensagensRotina []string;
var mensagensMain []string;

func main() {
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

    go tarefa();

    canal <- mensagensMain[0];
    fmt.Printf("\033[36m%s\033[m\n", <-canal);

    canal <- mensagensMain[1];
    fmt.Printf("\033[36%s\033[m\n", <-canal);

    canal <- mensagensMain[2];
    fmt.Printf("\033[36m%s\033[m\n", <-canal);
}

func tarefa() {
    fmt.Printf("\033[33m%s\033[m\n", <-canal);
    canal <- mensagensRotina[0];

    fmt.Printf("\033[33m%s\033[m\n", <-canal);
    canal <- mensagensRotina[1];

    fmt.Printf("\033[33m%s\033[m\n", <-canal);
    canal <- mensagensRotina[2];
}