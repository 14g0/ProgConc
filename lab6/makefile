arg1 := $(word 1, $(MAKECMDGOALS))
arg2 := $(word 2, $(MAKECMDGOALS))
arg3 := $(word 3, $(MAKECMDGOALS))
arg4 := $(word 4, $(MAKECMDGOALS))

.PHONY: main

#-------------------------------------------------------------------------------

main: main.c list_int.c list_int.h timer.h linked_list.c
	clear
	gcc -o main.o main.c list_int.c -ansi -pedantic -Wall

#-------------------------------------------------------------------------------

exe:
	./main.o $(arg2)

#-------------------------------------------------------------------------------

%:
	@:

#-------------------------------------------------------------------------------

clear:
	rm -r *.o