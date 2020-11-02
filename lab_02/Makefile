.PHONY: all clean
CFLAGS=-c -Wall -Wextra -Iinclude
all: lab2

lab2: obj/test.o obj/test_str.o obj/str.o | obj
	gcc obj/test.o obj/test_str.o obj/str.o -o lab2

obj:
	mkdir obj

obj/test.o: src/test.c | obj
	gcc $(CFLAGS) src/test.c -o obj/test.o

obj/test_str.o:  src/test_str.c include/test_str.h | obj
	gcc $(CFLAGS) src/test_str.c -o obj/test_str.o

obj/str.o:  src/str.c include/str.h | obj
	gcc $(CFLAGS) src/str.c -o obj/str.o

clean:
	rm -rf obj lab2