#include "BoardTest.hpp"

int Test::failedNum = 0;
int Test::totalNum = 0;

int main() {
	BoardTest bt;
	bt.run_all_tests();
	return !Test::show_final_result();
}