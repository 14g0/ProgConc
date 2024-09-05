# Querido monitor*x* 🧑‍🏫...

### Avisos⚠️
Os programas desenvolvidos nesse repositório utilizam uma biblioteca base, criada
por mim, com algumas funções utilitárias que eu notei que se repetiam muito, que
se encontram no arquivo **./utils.c**, porém as declarações de tipo se encontram em **progConc.h**, que é o arquivo importado como cabeçalho em todos os outros.

</br>

### Compilação
Como eu utilizo a biblioteca que eu criei, deve-se incluir o **.c** dela na compilação, assim o comando fica:

```bash
gcc -o <programa.c> ../utils.c -ansi -pedantic -Wall
```