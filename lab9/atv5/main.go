package main

import (
    "fmt"
    "math"
    "os"
    "strconv"
    "sync"
)

var qtdPrimos int64 = 0

func main() {
    if len(os.Args) < 2 {
        fmt.Println("\033[31;1mPoucos argumentos na chamada da função\033[m")
        fmt.Println("\033[33;1mgo run main.go <Quantidade para leitura>\033[m")
        return
    }

    N, err := strconv.ParseInt(os.Args[1], 10, 64)
    if err != nil {
        fmt.Println("Erro ao converter o argumento para int64:", err)
        return
    }

    threadArgs := make(chan int64, N)
    var waitGroup sync.WaitGroup
    waitGroup.Add(int(N)) // Atribui N "semáforos" de espera

    // Faz a leitura da entrada padrão com a quatidade definida pelo usuário
    for cont := int64(0) ; cont < N ; cont++ {
        intLido := int64(0)
        fmt.Scan(&intLido)
        threadArgs <- intLido
    }

    // Cria as rotinas para contar os primos
    for i := int64(0) ; i < N ; i++ {
        go func() {
            defer waitGroup.Done() // Remove um semáforo
            if ehPrimo(<-threadArgs) { qtdPrimos++ }
        }()
    }

    waitGroup.Wait() // Código só termina quando todos os semáforos foram consumidos
    close(threadArgs)
    fmt.Printf("\033[31;1mQuantidade de primos:\033[m %d\n", qtdPrimos)
}

func ehPrimo(n int64) bool {
    if n <= 1 {
        return false
    } else if n == 2 {
        return true
    } else if n%2 == 0 {
        return false
    }

    for i := int64(3); i <= int64(math.Sqrt(float64(n)))+1; i += 2 {
        if n%i == 0 {
            return false
        }
    }

    return true
}