CFLAGS=-c -Wall -Wextra -Iinclude
all: lab1

lab1: bin/main.o bin/util.o bin/algorithm.o bin/io.o | bin
	clang bin/main.o bin/util.o bin/algorithm.o bin/io.o -o lab1

bin:
	mkdir bin

bin/main.o: src/main.c | bin
	clang $(CFLAGS) src/main.c -o bin/main.o

bin/io.o:  src/io.c include/io.h | bin
	clang $(CFLAGS) src/io.c -o bin/io.o

bin/util.o:  src/util.c include/util.h | bin
	clang $(CFLAGS) src/util.c -o bin/util.o

bin/algorithm.o:  src/algorithm.c include/algorithm.h | bin
	clang $(CFLAGS) src/algorithm.c -o bin/algorithm.o

clean:
	rm -rf bin lab1