.PHONY: all clean
CFLAGS= -Wall -Wextra -Iinclude -fsanitize=address -fsanitize=undefined -fsanitize=leak
all: lab_05

lab_05: obj/main.o obj/clist.o obj/point_list.o | obj
	gcc $(CFLAGS) obj/*.o -o lab_05

obj:
	mkdir obj

obj/main.o: src/main.c | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

obj/clist.o:  src/clist.c include/clist.h | obj
	gcc $(CFLAGS) -c src/clist.c -o obj/clist.o

obj/point_list.o:  src/point_list.c include/point_list.h | obj
	gcc $(CFLAGS) -c src/point_list.c -o obj/point_list.o

clean:
	rm -rf obj lab_05