.PHONY: all clean
CFLAGS= -Wall -Wextra -Iinclude -fsanitize=address -fsanitize=undefined	
all: lab_04

lab_04: obj/main.o obj/mergesort.o | obj
	gcc $(CFLAGS) obj/main.o obj/mergesort.o -o lab_04

obj:
	mkdir obj

obj/main.o: src/main.c | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

obj/mergesort.o:  src/mergesort.c include/mergesort.h | obj
	gcc $(CFLAGS) -c src/mergesort.c -o obj/mergesort.o

clean:
	rm -rf obj lab_04