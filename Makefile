COMPILER = gcc
VERSION ?= c99
OPTIONS  = -std=$(VERSION) -Wall -pedantic
FILE    ?= 

BIN      = bin
INCLUDE  = include
MODULES  = $(shell find src/modules -name "*.c")

build:
	mkdir -p $(BIN)
	$(COMPILER) $(OPTIONS) -I$(INCLUDE) $(FILE) $(MODULES) -o $(BIN)/`basename $(FILE) .c`
	
	# BIN/`basename $(FILE) .c` .exe

clean:
	rm -r $(BIN)