COMPILER = gcc
VERSION ?= c99
OPTIONS  = -std=$(VERSION) -Wall -pedantic
FILE    ?= 
NAME    ?= `basename $(FILE) .c`

BIN      = bin
INCLUDE  = include
MODULES  = $(shell find src/modules -name "*.c")

build:
	mkdir -p $(BIN)
	$(COMPILER) $(OPTIONS) -I$(INCLUDE) $(FILE) $(MODULES) -o $(BIN)/$(NAME)

buildraw:
	mkdir -p $(BIN)
	$(COMPILER) $(OPTIONS) $(FILE) -o $(BIN)/$(NAME)

clean:
	rm -r $(BIN)