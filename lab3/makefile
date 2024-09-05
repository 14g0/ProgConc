arg1 := $(word 1, $(MAKECMDGOALS))
arg2 := $(word 2, $(MAKECMDGOALS))
arg3 := $(word 3, $(MAKECMDGOALS))
arg4 := $(word 4, $(MAKECMDGOALS))

.PHONY: all matriz seq

all: matriz.c seq.c ../utils.c
	gcc -o seq.o seq.c ../utils.c -ansi -pedantic -Wall
	gcc -o matriz.o matriz.c ../utils.c -ansi -pedantic -Wall

matriz:
	./matriz.o $(arg2) $(arg3) $(arg4)

seq:
	./seq.o $(arg2) $(arg3) $(arg4)

%:
	@:

clean:
	rm -r *.o *.bin