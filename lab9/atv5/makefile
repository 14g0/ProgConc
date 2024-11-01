arg1 := $(word 1, $(MAKECMDGOALS))
arg2 := $(word 2, $(MAKECMDGOALS))
arg3 := $(word 3, $(MAKECMDGOALS))
arg4 := $(word 4, $(MAKECMDGOALS))

.PHONY: main

#-------------------------------------------------------------------------------

main: main.go
	go run main.go $(arg2)

#-------------------------------------------------------------------------------

%:
	@:
