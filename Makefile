COMPILER = gcc
N ?= src/chapter1/exer103-104-105-115.c

run:
	mkdir -p bin
	$(COMPILER) $(N) -o bin/`basename $(N) .c`
	./bin/`basename $(N) .c`

clean:
	rm -r bin