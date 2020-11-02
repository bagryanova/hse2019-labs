.PHONY: all clean
CFLAGS= -O2 -Wall -Werror -std=c++11 -Iinclude
all: hw_02 test_hw_02

hw_02: obj/main.o obj/Board.o obj/StdioBoardView.o | obj
	g++ $(CFLAGS) obj/main.o obj/Board.o obj/StdioBoardView.o -o hw_02

test_hw_02: obj/mainTest.o obj/BoardTest.o obj/Test.o obj/Board.o | obj
	g++ $(CFLAGS) obj/mainTest.o obj/BoardTest.o obj/Test.o obj/Board.o -o test_hw_02

obj:
	mkdir obj

obj/main.o: src/main.cpp | obj
	g++ $(CFLAGS) -c src/main.cpp -o obj/main.o

obj/mainTest.o: test/mainTest.cpp | obj
	g++ $(CFLAGS) -c test/mainTest.cpp -o obj/mainTest.o

obj/Board.o:  src/Board.cpp include/Board.hpp | obj
	g++ $(CFLAGS) -c src/Board.cpp -o obj/Board.o

obj/StdioBoardView.o:  src/StdioBoardView.cpp include/StdioBoardView.hpp | obj
	g++ $(CFLAGS) -c src/StdioBoardView.cpp -o obj/StdioBoardView.o

obj/BoardTest.o:  test/BoardTest.cpp include/BoardTest.hpp | obj
	g++ $(CFLAGS) -c test/BoardTest.cpp -o obj/BoardTest.o

obj/Test.o:  test/Test.cpp include/Test.hpp | obj
	g++ $(CFLAGS) -c test/Test.cpp -o obj/Test.o

clean:
	rm -rf obj hw_02 test_hw_02