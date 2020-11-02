.PHONY: all clean
CFLAGS= -Wall -Wextra -Iinclude -fsanitize=address -fsanitize=undefined
all: lab3

lab3: obj/main.o obj/clist.o | obj
	gcc $(CFLAGS) obj/main.o obj/clist.o -o lab3

obj:
	mkdir obj

obj/main.o: src/main.c | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

obj/clist.o:  src/clist.c include/clist.h | obj
	gcc $(CFLAGS) -c src/clist.c -o obj/clist.o

clean:
	rm -rf obj lab3