.PHONY: all clean
CFLAGS= -Wall -Wextra -Iinclude
all: hw_01

hw_01: obj/main.o obj/bmp.o | obj
	gcc $(CFLAGS) obj/main.o obj/bmp.o -o hw_01

obj:
	mkdir obj

obj/main.o: src/main.c include/bmp.h | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

obj/bmp.o:  src/bmp.c include/bmp.h | obj
	gcc $(CFLAGS) -c src/bmp.c -o obj/bmp.o

clean:
	rm -rf obj hw_01
